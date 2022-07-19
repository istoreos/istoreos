#ifndef DLFW_MAIN_H
#define DLFW_MAIN_H

/******************************************************************************
**  Constants & Macros
******************************************************************************/

#define UPIO_BT_POWER_OFF 0
#define UPIO_BT_POWER_ON  1

#define RTD1295_BT_DISABLE_PIN 24

/* UPIO signals */
enum {
    UPIO_BT_WAKE = 0,
    UPIO_HOST_WAKE,
    UPIO_LPM_MODE,
    UPIO_MAX_COUNT
};

/* UPIO assertion/deassertion */
enum {
    UPIO_UNKNOWN = 0,
    UPIO_DEASSERT,
    UPIO_ASSERT
};

#endif

