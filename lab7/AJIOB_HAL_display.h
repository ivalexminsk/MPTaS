#pragma once

#include "device_state.h"

#include <stdint.h>

#define DISPLAY_LINES_TO_SHOW 2
#define DISPLAY_ROW_MAX_X_PLUS 50
#define DISPLAY_PLUS_MAX 127

#define DISPLAY_LOGO_SLEEP_TICKS 1000000

#define DISPLAY_FONT_X_STEP 6

#define DISPLAY_FONT_Y_NUMS     0
#define DISPLAY_FONT_Y_ANSWER   1
#define DISPLAY_FONT_Y_INPUT    7

void AJIOB_HAL_display_init();
void AJIOB_HAL_display_print_input_mode(inputs_t mode);
void AJIOB_HAL_display_print_answer(long val);
void AJIOB_HAL_display_print_append_nums(inputs_t input);
void AJIOB_HAL_display_print_reset_num_pos();
