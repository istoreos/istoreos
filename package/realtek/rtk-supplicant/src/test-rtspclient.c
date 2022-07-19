#include <gst/gst.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Structure to contain all our information, so we can pass it to callbacks */
typedef struct _CustomData {
	GMainLoop *loop;
	GstElement *pipeline;
	GstElement *source;
	GstElement *videodepay_h264;
	GstElement *videodepay_h265;
	GstElement *videodepay_mjpeg;
#ifdef REC_AUDIO
	GstElement *audiodepay;
#endif
	GstElement *queue_disp;
	GstElement *queue_rec;
	/*
	   GstPad *depay_video_pad;
	   GstPadTemplate *mux_sink_pad_template;
	   GstPad *mux_audio_pad, *mux_video_pad;
	   */
	GstElement *mux_disp;
	GstElement *mux_rec;
	GstElement *tee;
	GstElement *sink_file;
	GstElement *sink_rtk;
} CustomData;

/* Handler for the pad-added signal */
static void pad_added_handler (GstElement *src, GstPad *pad, CustomData *data);
/* Forward definition of the message processing function */
static gboolean handle_message (GstBus * bus, GstMessage * msg, CustomData * data);

int main(int argc, char *argv[]) {
	CustomData data1;
	GstBus *bus1;
	GstStateChangeReturn ret1;

	/* Initialize GStreamer */
	gst_init (&argc, &argv);

	/* Create the elements */
	data1.source = gst_element_factory_make ("rtspsrc", "source");
	data1.videodepay_h264 = gst_element_factory_make ("rtph264depay", "videodepay_h264");
	data1.videodepay_h265 = gst_element_factory_make ("rtph265depay", "videodepay_h265");
	data1.videodepay_mjpeg = gst_element_factory_make ("rtpjpegdepay", "videodepay_mjpeg");
	data1.tee = gst_element_factory_make ("tee", "tee");
	data1.queue_disp = gst_element_factory_make ("queue2", "queue_disp");
	data1.mux_disp = gst_element_factory_make ("mpegtsmux", "mux_disp");
	data1.sink_rtk = gst_element_factory_make ("rtksink", "rtksink");
	if (argv[3]) {
#ifdef REC_AUDIO
		/*Need to be re-defined according to the audio format, but now only AAC OK !*/
		data1.audiodepay = gst_element_factory_make ("rtpmp4gdepay", "audiodepay");
#endif
		data1.queue_rec = gst_element_factory_make ("queue2", "queue_rec");
		data1.mux_rec = gst_element_factory_make ("mpegtsmux", "mux_rec");
		data1.sink_file = gst_element_factory_make ("filesink", "filesink");
	} else {
#ifdef REC_AUDIO
		/*Need to be re-defined according to the audio format, but now only AAC OK !*/
		g_printerr ("The function of Recording was not opened.\n");
		return -1;
#endif
	}

	/* Create the empty pipeline */
	data1.pipeline = gst_pipeline_new ("test-pipeline");
	if (argv[3]) {
#ifdef REC_AUDIO
		if (!data1.pipeline || !data1.source || !data1.videodepay_h264|| !data1.videodepay_h265 || !data1.videodepay_mjpeg|| !data1.audiodepay || !data1.queue_disp || !data1.queue_rec || !data1.mux_disp || !data1.mux_rec || !data1.tee || !data1.sink_file || !data1.sink_rtk) {
			g_printerr ("Not all elements could be created.\n");
			return -1;
		}
#else
		if (!data1.pipeline || !data1.source || !data1.videodepay_h264|| !data1.videodepay_h265 || !data1.videodepay_mjpeg || !data1.queue_disp || !data1.queue_rec || !data1.mux_disp || !data1.mux_rec || !data1.tee || !data1.sink_file || !data1.sink_rtk) {
			g_printerr ("Not all elements could be created.\n");
			return -1;
		}
#endif
	} else {
		if (!data1.pipeline || !data1.source || !data1.videodepay_h264|| !data1.videodepay_h265 || !data1.videodepay_mjpeg || !data1.queue_disp || !data1.mux_disp || !data1.tee || !data1.sink_rtk) {
			g_printerr ("Not all elements could be created.\n");
			return -1;
		}
	}
	/* Build the pipeline. Note that we are NOT linking the source at this
	 * point. We will do it later. */
	if (argv[3]) {
#ifdef REC_AUDIO
		gst_bin_add_many (GST_BIN (data1.pipeline), data1.source, data1.videodepay_h264, data1.videodepay_h265, data1.videodepay_mjpeg, data1.audiodepay, data1.tee, data1.queue_disp, data1.queue_rec, data1.mux_rec, data1.sink_file, data1.mux_disp, data1.sink_rtk, NULL);
#else
		gst_bin_add_many (GST_BIN (data1.pipeline), data1.source, data1.videodepay_h264, data1.videodepay_h265, data1.videodepay_mjpeg, data1.tee, data1.queue_disp, data1.queue_rec, data1.mux_rec, data1.sink_file, data1.mux_disp, data1.sink_rtk, NULL);
#endif
		if (
#ifdef REC_AUDIO
				!gst_element_link_many (data1.audiodepay, data1.mux_rec, NULL) ||
#endif
				!gst_element_link_many (data1.tee, data1.queue_disp, data1.mux_disp, data1.sink_rtk, NULL) ||
				!gst_element_link_many (data1.tee, data1.queue_rec, data1.mux_rec, data1.sink_file, NULL)) {
			g_printerr ("Elements could not be linked.\n");
			gst_object_unref (data1.pipeline);
			return -1;
		}
	} else {
		gst_bin_add_many (GST_BIN (data1.pipeline), data1.source, data1.videodepay_h264, data1.videodepay_h265, data1.videodepay_mjpeg, data1.tee, data1.queue_disp, data1.mux_disp, data1.sink_rtk, NULL);
		if (!gst_element_link_many (data1.tee, data1.queue_disp, data1.mux_disp, data1.sink_rtk, NULL)) {
			g_printerr ("Elements could not be linked.\n");
			gst_object_unref (data1.pipeline);
			return -1;
		}
	}

	/* Set the Properties in Elements */
	g_object_set (data1.source, "location", argv[1], NULL);
	g_object_set (data1.source, "latency", 1000, NULL);

	int channel_id_num;
	channel_id_num = atoi(argv[2]);
	g_object_set (data1.sink_rtk, "ch", channel_id_num, NULL);
	if (argv[3])
		g_object_set (data1.sink_file, "location", argv[3], NULL);

	/* Manually link the Mux, which has "Request" pads *///Edited by Wenlin ,Do not Need
	/*
	   data1.mux_sink_pad_template = gst_element_class_get_pad_template (GST_ELEMENT_GET_CLASS (data1.mux), "sink_%d");
	   data1.mux_video_pad = gst_element_request_pad (data1.mux, data1.mux_sink_pad_template, NULL, NULL);
	   g_print ("Obtained request pad %s for video branch.\n", gst_pad_get_name (data1.mux_video_pad));
	   data1.depay_video_pad = gst_element_get_static_pad (data1.depay, "src");
	   if (gst_pad_link (data1.depay_video_pad, data1.mux_video_pad) != GST_PAD_LINK_OK) {
	   g_printerr ("Mux could not be linked.\n");
	   gst_object_unref (data1.pipeline);
	   return -1;
	   }
	   gst_object_unref (data1.depay_video_pad);

*/
	/* Connect to the pad-added signal */
	g_signal_connect (data1.source, "pad-added", G_CALLBACK (pad_added_handler), &data1);

	/* Start playing */
	ret1 = gst_element_set_state (data1.pipeline, GST_STATE_PLAYING);
	if (ret1 == GST_STATE_CHANGE_FAILURE) {
		g_printerr ("Unable to set the pipeline to the playing state.\n");
		gst_object_unref (data1.pipeline);
		return -1;
	}

	/* Add watch for messages */
	bus1 = gst_element_get_bus (data1.pipeline);
	gst_bus_add_watch (bus1, (GstBusFunc) handle_message, &data1);
	gst_object_unref (bus1);

	/* Create a mainloop */
	data1.loop = g_main_loop_new (NULL, FALSE);

	/* This mainloop is stopped when we receive an error or EOS */
	g_main_loop_run (data1.loop);

	/* Free resources */
	gst_element_set_state (data1.pipeline, GST_STATE_NULL);
	gst_object_unref (data1.pipeline);
	g_main_loop_unref (data1.loop);

	return 0;
}

static gboolean handle_message (GstBus * bus, GstMessage * msg, CustomData * data) {
	GError *err;
	gchar *debug_info;

	switch (GST_MESSAGE_TYPE (msg)) {
		case GST_MESSAGE_ERROR:
			gst_message_parse_error (msg, &err, &debug_info);
			g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
			g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
			g_clear_error (&err);
			g_free (debug_info);
			g_main_loop_quit (data->loop);
			break;
		case GST_MESSAGE_EOS:
			g_print ("End-Of-Stream reached.\n");
			g_main_loop_quit (data->loop);
			break;
		case GST_MESSAGE_STATE_CHANGED: {
											/* We are only interested in state-changed messages from the pipeline */
											GstState old_state, new_state, pending_state;
											gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
											if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data->pipeline)) {
												g_print ("Pipeline state changed from %s to %s:\n",
														gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
											}
										} break;
		default:
										/* We should not reach here */
										g_printerr ("Unexpected %s message received.\n", GST_MESSAGE_TYPE_NAME (msg));
										break;
	}
	return TRUE;
}

/* This function will be called by the pad-added signal */
static void pad_added_handler (GstElement *src, GstPad *new_pad, CustomData *data) {
	g_print("New pad in rtspsrc added!\n");
	gchar *dynamic_pad_name;

	dynamic_pad_name = gst_pad_get_name (new_pad);

	if(gst_element_link_pads(data->source, dynamic_pad_name, data->videodepay_mjpeg, "sink")){
		g_print("Pad for video mjpeg linked\n");
		g_free (dynamic_pad_name);
		gst_element_link (data->videodepay_mjpeg, data->tee) ;
		return;
	}else if (gst_element_link_pads(data->source, dynamic_pad_name, data->videodepay_h264, "sink")){
		g_print("Pad for video h264 linked\n");
		g_free (dynamic_pad_name);
		gst_element_link (data->videodepay_h264, data->tee) ;
		return;
	}else if (gst_element_link_pads(data->source, dynamic_pad_name, data->videodepay_h265, "sink")){
		g_print("Pad for video h265 linked\n");
		g_free (dynamic_pad_name);
		gst_element_link (data->videodepay_h265, data->tee) ;
		return;
	}
#ifdef REC_AUDIO
	else if(gst_element_link_pads(data->source, dynamic_pad_name, data->audiodepay, "sink")){
		g_print("Pad for audio linked\n");
		g_free (dynamic_pad_name);
		return;
	}
#endif
	g_free (dynamic_pad_name);

}
