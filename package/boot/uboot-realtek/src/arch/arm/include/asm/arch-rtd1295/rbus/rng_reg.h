/************************************************************************
 *
 *  rng_reg.h
 *
 *  Defines for Phoenix TRNG registers
 *
 ************************************************************************/

#ifndef TRNG_REG_H
#define TRNG_REG_H

/************************************************************************
 *  Definition
 ************************************************************************/
#define TRNG_REG_BASE           0x9801aa00

#define RNG_CALI_CHK	(TRNG_REG_BASE + 0x18)
#define RNG_ANA			(TRNG_REG_BASE + 0x14)
#define RNG_CALI_RETURN (TRNG_REG_BASE + 0x20)
#define RNG_LOCK_CHK	(TRNG_REG_BASE + 0x24)
#define RNG_RETURN3		(TRNG_REG_BASE + 0x2c)
#define RNG_RETURN4		(TRNG_REG_BASE + 0x30)
#define RNG_RESULTR		(TRNG_REG_BASE + 0x38)
#define RNG_DUMMY		(TRNG_REG_BASE + 0x44)

#endif /* #ifndef TRNG_REG_H */
