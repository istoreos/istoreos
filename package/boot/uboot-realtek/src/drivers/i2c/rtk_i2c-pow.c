#include "rtk_i2c-pow.h"

#define _BIT(_n)      (1 << (_n))

#ifdef CONFIG_RTD1395
void rtk_i2c_set_pow(int BusId)
{
        if (BusId == 0 || BusId == 1)
        {
                unsigned int *rst = (unsigned int *)0x98007088;
                unsigned int *clk = (unsigned int *)0x9800708c;

                if (BusId == 0) {
                        *rst |= _BIT(11);
                        *clk |= _BIT(9);
                } else {
                        *rst |= _BIT(12);
                        *clk |= _BIT(10);
                }
        }
        else if (BusId == 5)
        {
                unsigned int *rst = (unsigned int *)0x98000004;
                unsigned int *clk = (unsigned int *)0x98000010;

                *rst |= _BIT(16);
                *clk |= _BIT(1);
        }
}

void rtk_i2c_clear_pow(int BusId)
{}

#endif
