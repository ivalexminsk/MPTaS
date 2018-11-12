#include "AJIOB_HAL_buffer.h"

uint8_t AJIOB_HAL_buffer[HAL_BUFFER_SIZE] = {0};

uint16_t AJIOB_HAL_buffer_index = 0;

void buffer_append(uint8_t data)
{
    AJIOB_HAL_buffer[AJIOB_HAL_buffer_index] = data;

    AJIOB_HAL_buffer_index++;
    AJIOB_HAL_buffer_index %= HAL_BUFFER_SIZE;
}

uint8_t buffer_get(uint16_t index)
{
    return AJIOB_HAL_buffer[(index + AJIOB_HAL_buffer_index) % HAL_BUFFER_SIZE];
}
