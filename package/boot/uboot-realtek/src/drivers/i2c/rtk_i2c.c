#include <common.h>
#include "rtk_i2c-lib.h"

#ifdef CONFIG_I2C_MULTI_BUS

unsigned int current_i2c_speed = 0;
static unsigned int current_bus = 0;

int i2c_set_bus_num(unsigned int bus)
{
	if ((bus < 0) || (bus >= I2C_GetBusCount())) {
		printf("Bad bus: %d\n", bus);
		return -1;
	}
	current_bus = bus;
	return 0;
}

unsigned int i2c_get_bus_num(void)
{
	return current_bus;
}
#endif

/* ------------------------------------------------------------------------ */
/* API Functions                                                            */
/* ------------------------------------------------------------------------ */
void i2c_init(int speed, int slaveaddr)
{

	I2C_Init();
	I2C_UnInit();
#ifdef CONFIG_I2C_MULTI_BUS
	current_bus = 0;
#endif
}

unsigned int i2c_get_bus_speed(void)
{
	unsigned int current_speed;

	current_speed = I2C_GetSpeed(current_bus);

	return current_speed;
}

int i2c_set_bus_speed(unsigned int speed)
{
	int ret = 0;

	I2CN_Init(current_bus);
	ret = I2C_SetSpeed(current_bus, speed);
	I2CN_UnInit(current_bus);

	return ret;
}

/*
 * i2c_probe: - Test if a chip answers for a given i2c address
 *
 * @chip:	address of the chip which is searched for
 * @return:	0 if a chip was found, -1 otherwhise
 */
int i2c_probe(uchar chip)
{
	int ret = 0, tmp = 0;
	uchar buffer[2];

	I2CN_Init(current_bus);
	ret = I2C_Read_EX(current_bus, chip, 1, (unsigned char *)&tmp,
			1, buffer, NON_STOP);
	I2CN_UnInit(current_bus);

	return ret;
}

/*
 * i2c_read: - Read multiple bytes from an i2c device
 *
 * The higher level routines take into account that this function is only
 * called with len < page length of the device (see configuration file)
 *
 * @chip:	address of the chip which is to be read
 * @addr:	i2c data address within the chip
 * @alen:	length of the i2c data address (1..2 bytes)
 * @buffer:	where to write the data
 * @len:	how much byte do we want to read
 * @return:	0 in case of success
 */
int i2c_read(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
	int ret = 0;
	unsigned char tmp[2];

	if (alen >= 4)
		return -1;

	I2CN_Init(current_bus);
	memcpy(tmp, (char *)&addr, alen);
	ret = I2C_Read_EX(current_bus, chip, alen, tmp, len, buffer, NON_STOP);
	I2CN_UnInit(current_bus);

	return ret;
}

/*
 * i2c_write: -  Write multiple bytes to an i2c device
 *
 * The higher level routines take into account that this function is only
 * called with len < page length of the device (see configuration file)
 *
 * @chip:	address of the chip which is to be written
 * @addr:	i2c data address within the chip
 * @alen:	length of the i2c data address (1..2 bytes)
 * @buffer:	where to find the data to be written
 * @len:	how much byte do we want to read
 * @return:	0 in case of success
 */
int i2c_write(uchar chip, uint addr, int alen, uchar *buffer, int len)
{
	unsigned char tmp[256];
	int ret = 0;

	if (alen >= 4)
		return -1;
	if (len + alen > 256)
		return -1;

	I2CN_Init(current_bus);
	memcpy(tmp, (char *)&addr, alen);
	memcpy(tmp + alen, buffer, len);
	ret = I2C_Write_EX(current_bus, chip, alen + len, tmp, NO_READ);
	I2CN_UnInit(current_bus);

	return ret;
}
