#ifndef __I2CUTIL_H__
#define __I2CUTIL_H__

#define I2C_Read(args...)                I2C_Read_EX(0, args)
#define I2C_Write(args...)               I2C_Write_EX(0, args)

/*#define MAX_I2C_CNT                      3*/
/*#define FIFO_THRESHOLD                   4*/
/*#define DEFAULT_SPEED                    100*/

#define S_OK         0
#define S_FALSE     -1

#define NON_STOP    0x1
#define NO_READ		0x2

int I2C_Write_EX(
	unsigned char id,
	unsigned short Addr,
	unsigned short nData,
	unsigned char *pData,
	unsigned int flag);
int I2C_Read_EX(
	unsigned char id,
	unsigned short Addr,
	unsigned short nSubAddr,
	unsigned char *pSubAddr,
	unsigned short nData,
	unsigned char *pData,
	unsigned int flag);
int I2C_SetSpeed(unsigned int ID, unsigned int speed);

unsigned int I2C_GetSpeed(unsigned int ID);

int I2C_StartXfer(
	unsigned char	Id,
	unsigned short	Addr,
	unsigned short	nSubAddr,
	unsigned char	*pSubAddr,
	unsigned short	nData,
	unsigned char	*pData,
	unsigned int	flag
);

unsigned char I2C_GetBusCount(void);

void I2C_Init(void);
void I2C_UnInit(void);

void I2CN_Init(int Bus_ID);
void I2CN_UnInit(int Bus_ID);

#endif

