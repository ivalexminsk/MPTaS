#include "pmm.h"
#include "led.h"
#include "types.h"

pmm_mode_t curr_pmm_mode = pmm_active;
bool is_need_to_on_lpm = true;

void pmm_set_active_mode_diodes()
{
    //crunch: lpm mode was resetted in inpterrupt logic

    set_led_state(MAIN_POWER_MODE_LED, true);
    set_led_state(LOW_POWER_MODE_LED, false);
    curr_pmm_mode = pmm_active;
}

void pmm_set_lpm()
{
    if (!is_need_to_on_lpm) return;

    set_led_state(MAIN_POWER_MODE_LED, false);
    set_led_state(LOW_POWER_MODE_LED, true);
    curr_pmm_mode = pmm_lpm;
    is_need_to_on_lpm = false;

    // input in lpm mode
    LPM1;
}

void pmm_switch_curr_mode()
{
    if (curr_pmm_mode == pmm_lpm)
    {
        pmm_set_active_mode_diodes();
    }
    else
    {
        is_need_to_on_lpm = true;
    }
}
