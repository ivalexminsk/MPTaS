#pragma once

#include "types.h"

/**
 * @brief Input processor in LPM1
 * @warinig Don't use in interrupts. Need to set is_need_to_on_lpm before execution
 *
 */
void pmm_set_lpm();
void pmm_switch_curr_mode();

typedef enum pmm_mode_t
{
    pmm_lpm,
    pmm_active,
} pmm_mode_t;

extern pmm_mode_t curr_pmm_mode;
extern bool is_need_to_on_lpm;
