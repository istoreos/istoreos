#ifndef __BIG_UTIL_H__
#define __BIG_UTIL_H__

/************************************************************************
 *  Function prototypes
 ************************************************************************/
void * my_malloc( unsigned int NBYTES );
void my_freeAll( void );
unsigned int do_RSA( const unsigned int signature_addr,
                     const unsigned int rsa_key_addr,
                     const unsigned int output_addr );

#endif // __BIG_UTIL_H__
