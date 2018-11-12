#include "AJIOB_HAL_buffer.h"

uint8_t AJIOB_HAL_buffer[HAL_BUFFER_SIZE] = {0};

void AJIOB_HAL_buffer_append(uint8_t data)
{
    //shift data
    for (int i = 1; i < HAL_BUFFER_SIZE; i++)
    {
        AJIOB_HAL_buffer[i - 1] = AJIOB_HAL_buffer[i];
    }

    AJIOB_HAL_buffer[HAL_BUFFER_SIZE - 1] = data;
}

uint8_t* AJIOB_HAL_buffer_get_raw()
{
    return AJIOB_HAL_buffer;
}
