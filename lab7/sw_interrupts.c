#include "sw_interrupts.h"

#include "driverlib.h"

#include "device_state.h"

void Button_S2_ISR()
{
    __disable_interrupt();

    enter_button();

    __enable_interrupt();
}
