/*
 * testapp-thumbnail.c: example for using stream_get_thumbnail to get thumbnail from input stream
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "rtkstream.h"

#define JPEG_BUFFER_SIZE	1024000 // 1 MB

#define JPEG_THUMBNAIL_ORIG	"thumb_orig.jpeg"
#define JPEG_FILENAME_ORIG	"file_orig.jpeg"
#define JPEG_THUMBNAIL_RESIZED	"thumb_resized.jpeg"
#define JPEG_FILENAME_RESIZED	"file_resized.jpeg"

#define JPEG_WIDTH_RESIZED	480
#define JPEG_HEIGHT_RESIZED	320

int
main (int argc, char *argv[])
{
  thumbnail_stream_t *stream;
  thumbnail_jpeg_t *jpeg;
  unsigned char sps[512], pps[512];
  unsigned char bs[5120000];    // 5 MB
  int fd;
  int ret;
  char *buf_file;
  FILE *fp = NULL;

  /* Allocate memory for structures */
  stream = malloc (sizeof (thumbnail_stream_t));
  memset (stream, 0, sizeof (thumbnail_stream_t));
  jpeg = malloc (sizeof (thumbnail_jpeg_t));
  memset (jpeg, 0, sizeof (thumbnail_jpeg_t));

  if (argc < 2) {
    printf ("Usage: %s <bitstream> [<SPS> <PPS>]\n", argv[0]);
    return EXIT_FAILURE;
  }

  /* Get bitstream */
  if (argc > 1) {
    memset (bs, 0, sizeof (bs));
    fd = open (argv[1], O_RDONLY);
    if (fd > 0) {
      stream->bitstream_len = read (fd, bs, sizeof (bs));
      stream->bitstream = bs;
    }
    close (fd);
    printf ("Read stream size: %d\n", stream->bitstream_len);
  }

  /* Get SPS */
  if (argc > 2) {
    memset (sps, 0, sizeof (sps));
    fd = open (argv[2], O_RDONLY);
    if (fd > 0) {
      stream->sps_len = read (fd, sps, sizeof (sps));
      stream->sps_buf = sps;
    }
    close (fd);
    printf ("Read SPS size: %d\n", stream->sps_len);
  }

  /* Get PPS */
  if (argc > 3) {
    memset (pps, 0, sizeof (pps));
    fd = open (argv[3], O_RDONLY);
    if (fd > 0) {
      stream->pps_len = read (fd, pps, sizeof (pps));
      stream->pps_buf = pps;
    }
    close (fd);
    printf ("Read PPS size: %d\n", stream->pps_len);
  }

  /* Allocate buffer for JPEG thumbnail */
  jpeg->jpeg_buf = malloc (JPEG_BUFFER_SIZE);
  memset (jpeg->jpeg_buf, 0, JPEG_BUFFER_SIZE);
  jpeg->jpeg_len = malloc (sizeof (*(jpeg->jpeg_len)));
  *(jpeg->jpeg_len) = 0;

  /* Keep video size */
  jpeg->width = -1;
  jpeg->height = -1;
  jpeg->filename = JPEG_FILENAME_ORIG;

  /* Invoke stream_get_thumbnail API */
  ret = rtk_stream_get_thumbnail (stream, jpeg);
  printf ("stream_get_thumbnail: return %d\n", ret);

  /* Write buffer to file */
  if (ret == 0) {
    buf_file = JPEG_THUMBNAIL_ORIG;
    if (jpeg->jpeg_buf) {
      fp = fopen (buf_file, "wb");
      fwrite (jpeg->jpeg_buf, *jpeg->jpeg_len, 1, fp);
      fclose (fp);
    }
    printf ("\tjpeg_len: %u\n", *(jpeg->jpeg_len));
    printf ("\tjpeg_buf: %s\n", buf_file);
    printf ("\tjpeg_filename: %s\n", jpeg->filename);
  }

  /* Clear JPEG thumbnail */
  memset (jpeg->jpeg_buf, 0, JPEG_BUFFER_SIZE);
  *(jpeg->jpeg_len) = 0;

  /* Resize width and height */
  jpeg->width = JPEG_WIDTH_RESIZED;
  jpeg->height = JPEG_HEIGHT_RESIZED;
  jpeg->filename = JPEG_FILENAME_RESIZED;

  /* Invoke stream_get_thumbnail API */
  ret = rtk_stream_get_thumbnail (stream, jpeg);
  printf ("stream_get_thumbnail: return %d\n", ret);

  /* Write buffer to file */
  if (ret == 0) {
    buf_file = JPEG_THUMBNAIL_RESIZED;
    if (jpeg->jpeg_buf) {
      fp = fopen (buf_file, "wb");
      fwrite (jpeg->jpeg_buf, *jpeg->jpeg_len, 1, fp);
      fclose (fp);
    }
    printf ("\twidth: %d\n\theight: %d\n", jpeg->width, jpeg->height);
    printf ("\tjpeg_len: %u\n", *(jpeg->jpeg_len));
    printf ("\tjpeg_buf: %s\n", buf_file);
    printf ("\tjpeg_filename: %s\n", jpeg->filename);
  }

  /* Clean up */
  free (jpeg->jpeg_buf);
  free (jpeg->jpeg_len);
  free (jpeg);
  free (stream);

  return EXIT_SUCCESS;
}
