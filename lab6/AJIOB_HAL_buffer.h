#pragma once

#include <stdint.h>

#define HAL_BUFFER_SIZE 25

void AJIOB_HAL_buffer_append(uint8_t data);
uint8_t* AJIOB_HAL_buffer_get_raw();
