/*
 * @author jjm2473
 * @since 2021-03-15
 */

#include <stdio.h>
#include <string.h>

#include "io.h"
#include "WjCryptLib_Sha256.h"

int sha256(int fd, unsigned char *sha256) {
  ssize_t size;
  char buf[512];
  Sha256Context sha256Context;
  SHA256_HASH sha256Hash;
  Sha256Initialise( &sha256Context );
  while((size = syncread(fd, buf, 512)) > 0) {
    Sha256Update( &sha256Context, buf, size );
  }
  if (size < 0) {
    return 1;
  }
  Sha256Finalise( &sha256Context, &sha256Hash );
  memcpy(sha256, sha256Hash.bytes, SHA256_HASH_SIZE);
  return 0;
}