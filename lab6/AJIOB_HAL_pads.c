#include "AJIOB_HAL_pads.h"

#include "HAL_Dogs102x6.h"
#include "CTS_Layer.h"
#include "HAL_UCS.h"
#include "HAL_PMM.h"

void AJIOB_HAL_pads_init()
{
    // Set Vcore to accomodate for max. allowed system speed
    SetVCore(3);

    // Set system clock to max (25MHz)
    Init_FLL_Settle(25000, 762);

    // Configure CapTouch ports
    P1OUT &= ~0x7E;
    P1DIR |= 0x7E;
    P6OUT = 0x00;
    P6DIR = 0x00;

    TI_CAPT_Init_Baseline(&slider);
}

bool AJIOB_HAL_pads_is_pressed(uint8_t i)
{
    i--;
    if (i >= AJIOB_HAL_PAD_COUNT)
    {
        return false;
    }

    uint16_t deltaCount[AJIOB_HAL_PAD_COUNT];
    TI_CAPT_Custom(&slider, deltaCount);
    return (deltaCount[i] > AJIOB_HAL_PAD_DETECTION_LEVEL);
}

static bool saved_values[AJIOB_HAL_PAD_COUNT] = {0};

bool AJIOB_HAL_pads_is_press_rise(uint8_t i)
{
    bool curr = AJIOB_HAL_pads_is_pressed(i);
    i--;
    if (i >= AJIOB_HAL_PAD_COUNT)
    {
        return false;
    }
    bool res = (curr && !(saved_values[i]));
    saved_values[i] = res;

    return res;
}
