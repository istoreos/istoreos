CFLAGS += `pkg-config --cflags --libs gstreamer-1.0`
GST_APP_CFLAGS = `pkg-config --cflags --libs gstreamer-1.0 gstreamer-app-1.0`
RTK_MEDIA_CFLAGS += `pkg-config --cflags --libs rtkcontrol`

all:
	$(CC) -Wall -Werror -o testapp-filewrite-ch testapp-filewrite-ch.c testapp-utils.c $(RTK_MEDIA_CFLAGS)
	$(CC) -Wall -Werror -o testapp-filewrite-disp testapp-filewrite-disp.c testapp-utils.c $(RTK_MEDIA_CFLAGS)
	$(CC) -Wall -Werror -o testapp-filewrite-wnd testapp-filewrite-wnd.c testapp-utils.c $(RTK_MEDIA_CFLAGS)
	$(CC) -Wall -Werror -o testapp-rtspclient-disp testapp-rtspclient-disp.c testapp-utils.c $(RTK_MEDIA_CFLAGS)
	$(CC) -Wall -Werror -o testapp-debug testapp-debug.c $(RTK_MEDIA_CFLAGS)
	$(CC) $(CFLAGS) -Wall -Werror -L$(GENERIC_LINUX_PATH)/lib -o test-rtspclient test-rtspclient.c testapp-utils.c $(RTK_MEDIA_CFLAGS)
	$(CC) -Wall -Werror -o testapp-thumbnail testapp-thumbnail.c -lrtkstream $(GST_APP_CFLAGS)
	$(CC) fb_test.c -o fb_test
	$(CC) -Wall -Werror -o testapp-slim-rtkrtsp-fetchframe testapp-slim-rtkrtsp-fetchframe.c $(RTK_MEDIA_CFLAGS) -lrtkrtsp $(GST_APP_CFLAGS) -lion
	$(CC) -Wall -Werror -o testapp-adec testapp-adec.c -lrtkadec $(GST_APP_CFLAGS)
	$(CC) -Wall -Werror -o testapp-aenc testapp-aenc.c -lrtkaenc $(GST_APP_CFLAGS)
	$(CC) -Wall -Werror -o testapp-aenc2dec testapp-aenc2dec.c -lrtkadec -lrtkaenc $(GST_APP_CFLAGS)
