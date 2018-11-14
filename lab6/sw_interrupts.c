#include "sw_interrupts.h"

#include <stdbool.h>
#include <string.h>

#include "driverlib.h"
#include "HAL_Dogs102x6.h"

#include "AJIOB_HAL_file.h"
#include "AJIOB_HAL_buffer.h"
#include "AJIOB_HAL_timer_a.h"
#include "AJIOB_HAL_display.h"

static bool is_measure_mode = true;

void Button_S2_ISR()
{
    __disable_interrupt();

    if (is_measure_mode)
    {
        AJIOB_HAL_write_file(AJIOB_HAL_buffer_get_raw(), HAL_BUFFER_SIZE);
    }

    __enable_interrupt();
}

void PAD1_ISR()
{
    __disable_interrupt();

    if (is_measure_mode)
    {
        uint8_t read_buff[HAL_BUFFER_SIZE] = {0};

        AJIOB_HAL_timer_a_stop();

        AJIOB_HAL_read_file(read_buff, HAL_BUFFER_SIZE);
        Dogs102x6_clearScreen();
        for (uint8_t i = 0; i < HAL_BUFFER_SIZE; i++)
        {
            AJIOB_HAL_display_print_value(read_buff[i]);
        }
    }
    else
    {
        memset(AJIOB_HAL_buffer_get_raw(), 0, HAL_BUFFER_SIZE);
        Dogs102x6_clearScreen();
        AJIOB_HAL_timer_a_start();
    }

    is_measure_mode = !is_measure_mode;

    __enable_interrupt();
}
