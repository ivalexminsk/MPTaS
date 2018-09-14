#include "pmm.h"
#include "led.h"

static enum pmm_mode_t 
{
    pmm_lpm,
    pmm_active,
} curr_pmm_mode = pmm_active;

void pmm_set_active_mode()
{
    //TODO:
    set_led_state(MAIN_POWER_MODE_LED, true);
    set_led_state(LOW_POWER_MODE_LED, false);
    curr_pmm_mode = pmm_active;
}

void pmm_set_lpm()
{
    //TODO:

    set_led_state(MAIN_POWER_MODE_LED, false);
    set_led_state(LOW_POWER_MODE_LED, true);
    curr_pmm_mode = pmm_lpm;
}

void pmm_switch_curr_mode()
{
    if (curr_pmm_mode == pmm_lpm)
    {
        pmm_set_active_mode();
    }
    else
    {
        pmm_set_lpm();
    }
}
