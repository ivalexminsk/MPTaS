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
    Timer_A_initUpMode(TIMER_A0_BASE, &t_a_params);
}

void AJIOB_HAL_timer_a_start()
{
    Timer_A_enableCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
    Timer_A_clear(TIMER_A0_BASE);
}

void AJIOB_HAL_timer_a_stop()
{
    Timer_A_disableCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
}

void AJIOB_HAL_timer_a_reset()
{
    Timer_A_clear(TIMER_A0_BASE);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TA0_ISR()
{
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);

    //TODO: switch input symbol
}
