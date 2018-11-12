#include "AJIOB_HAL_timer_a.h"

#include "driverlib.h"
#include "HAL_Cma3000.h"

#include "AJIOB_HAL_display.h"
#include "AJIOB_HAL_buffer.h"

void AJIOB_HAL_timer_a_init()
{
    Timer_A_initUpModeParam t_a_params = {
        .clockSource = TIMER_A_CLOCKSOURCE_ACLK,
        .clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1,
        .timerPeriod = (uint16_t)((float)ACLK_BASE_PERIOD / REQUIRED_TIMER_FREQ),
        .timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE,
        .captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,
        .timerClear = TIMER_A_DO_CLEAR,
        .startTimer = true,
    };
    Timer_A_initUpMode(TIMER_A1_BASE, &t_a_params);
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TA1_ISR()
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    Cma3000_readAccel();

    AJIOB_HAL_buffer_append(Cma3000_xAccel);

    AJIOB_HAL_display_print_value(Cma3000_xAccel);
}
