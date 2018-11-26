#include "device_callbacks.h"

#include "AJIOB_HAL_display.h"
#include "AJIOB_HAL_flash.h"
#include "HAL_Dogs102x6.h"

short num1 = 0;
short num2 = 0;
long res = 0;
inputs_t operation = inputs_digit0;

void append_digit(device_state_t curr_state, inputs_t curr_input)
{
    //TODO:
}

void select_operation(device_state_t curr_state, inputs_t curr_input)
{
    operation = curr_input;
}

void memo_operation(device_state_t curr_state, inputs_t curr_input)
{
    if (curr_input == inputs_memoWrite)
    {
        AJIOB_write_memo(res);
        return;
    }

    //inputs_memoRead
    short read_val = AJIOB_read_memo();
    for (int8_t i = (sizeof(read_val) * 2 - 1); i > 0; i++)
    {
        //digit select emulation
        append_digit(curr_state, (((read_val >> (4 * i)) & 0xF) + inputs_digit0));
        curr_state++;
    }
}

void clear_all(device_state_t curr_state, inputs_t curr_input)
{
    Dogs102x6_clearScreen();
    num1 = num2 = 0;
    res = 0;
    operation = inputs_digit0;
}
