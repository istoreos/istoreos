// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2019, Linaro Limited
 */

#if !defined _RNG_H_
#define _RNG_H_

struct udevice;

/**
 * dm_rng_read() - read a random number seed from the rng device
 * @buffer:	input buffer to put the read random seed into
 * @size:	number of bytes of random seed read
 *
 * Return: 0 if OK, -ve on error
 */
int dm_rng_read(struct udevice *dev, void *buffer, size_t size);

/* struct dm_rng_ops - Operations for the hwrng uclass */
struct dm_rng_ops {
	/**
	 * @read() - read a random number seed
	 *
	 * @data:	input buffer to read the random seed
	 * @max:	total number of bytes to read
	 *
	 * Return: 0 if OK, -ve on error
	 */
	int (*read)(struct udevice *dev, void *data, size_t max);
};

#endif /* _RNG_H_ */
