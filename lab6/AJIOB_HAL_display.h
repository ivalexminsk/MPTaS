#pragma once

#include <stdint.h>

#include "HAL_Dogs102x6.h"

#define DISPLAY_LINES_TO_SHOW 2
#define DISPLAY_ROW_MAX_X_PLUS 50
#define DISPLAY_PLUS_MAX 127

void AJIOB_display_print_value(int8_t val);
