#include "sw_interrupts.h"

#include "driverlib.h"

#include "device_state.h"

void Button_S1_ISR()
{
    __disable_interrupt();

    enter_button();

    //sleep 1/8s
    __delay_cycles(131000);

    __enable_interrupt();
}
