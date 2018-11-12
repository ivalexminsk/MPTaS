#pragma once

#include <stdint.h>

#define HAL_BUFFER_SIZE 25

void buffer_append(uint8_t data);
uint8_t buffer_get(uint16_t index);
