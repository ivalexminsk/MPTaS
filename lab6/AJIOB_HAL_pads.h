#pragma once

#include <stdint.h>
#include <stdbool.h>

// 3500-4000 => powerful pressing
// 1500-2000 => finger move near
//// Use TI "Touch Demo" for watching
#define AJIOB_HAL_PAD_DETECTION_LEVEL       1500

#define AJIOB_HAL_PAD_COUNT                 5

void AJIOB_HAL_pads_init();

/**
 * @brief Checks if pad was pressed
 * 
 * @param i Index of pad to check (from 1 to AJIOB_HAL_PAD_COUNT)
 * @return true Pad was pressed
 * @return false Pad was not pressed
 */
bool AJIOB_HAL_pads_is_pressed(uint8_t i);
