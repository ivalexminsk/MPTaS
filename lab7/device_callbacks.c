#include "device_callbacks.h"

#include "AJIOB_HAL_display.h"
#include "AJIOB_HAL_flash.h"
#include "HAL_Dogs102x6.h"
#include "calc_logic.h"

short num1 = 0;
short num2 = 0;
long res = 0;
inputs_t operation = inputs_digit0;

void append_digit(device_state_t curr_state, inputs_t curr_input)
{
    switch(curr_state)
    {
    case device_state_num1_3:
    case device_state_num1_2:
    case device_state_num1_1:
    case device_state_num1_0:
        num1 = (num1 << 4) | (curr_input - inputs_digit0);
        break;
    case device_state_num2_3:
    case device_state_num2_2:
    case device_state_num2_1:
    case device_state_num2_0:
        num2 = (num2 << 4) | (curr_input - inputs_digit0);
        break;
    }

    if (curr_state == device_state_num2_0)
    {
        calculate_res(curr_state, curr_input);
    }
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
        append_digit(curr_state, (inputs_t)(((read_val >> (4 * i)) & 0xF) + inputs_digit0));
        curr_state++;
    }
}

void clear_all(device_state_t curr_state, inputs_t curr_input)
{
    AJIOB_HAL_display_print_reset_num_pos();
    Dogs102x6_clearScreen();
    num1 = num2 = 0;
    res = 0;
    operation = inputs_digit0;
}

void calculate_res(device_state_t curr_state, inputs_t curr_input)
{
    switch(operation)
    {
    case inputs_operationPlus:
        res = add(num1, num2);
        break;
    case inputs_operationMinus:
        res = sub(num1, num2);
        break;
    case inputs_operationMul:
        res = multiply(num1, num2);
        break;
    case inputs_operationMod:
        res = mod(num1, num2);
        break;
    }

    AJIOB_HAL_display_print_answer(res);
}
