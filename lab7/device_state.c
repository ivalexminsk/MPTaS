#include "device_state.h"

#include "device_callbacks.h"
#include "AJIOB_HAL_display.h"

#include <stdlib.h>

inputs_t inputs_num_3[] = {
    inputs_digit0,
    inputs_digit1,
    inputs_digit2,
    inputs_digit3,
    inputs_digit4,
    inputs_digit5,
    inputs_digit6,
    inputs_digit7,
    inputs_digit8,
    inputs_digit9,
    inputs_digitA,
    inputs_digitB,
    inputs_digitC,
    inputs_digitD,
    inputs_digitE,
    inputs_digitF,
    inputs_memoRead,
    inputs_NULL,
};

inputs_t inputs_num_210[] = {
    inputs_digit0,
    inputs_digit1,
    inputs_digit2,
    inputs_digit3,
    inputs_digit4,
    inputs_digit5,
    inputs_digit6,
    inputs_digit7,
    inputs_digit8,
    inputs_digit9,
    inputs_digitA,
    inputs_digitB,
    inputs_digitC,
    inputs_digitD,
    inputs_digitE,
    inputs_digitF,
    inputs_NULL,
};

inputs_t inputs_operation[] = {
    inputs_operationPlus,
    inputs_operationMinus,
    inputs_operationMul,
    inputs_operationMod,
    inputs_NULL,
};

inputs_t inputs_result[] = {
    inputs_memoWrite,
    inputs_nextCalc,
    inputs_NULL,
};

inputs_t* inputs_for_states[] = {
    NULL,                //device_state_begin_NULL
    inputs_num_3,        //device_state_num1_3
    inputs_num_210,      //device_state_num1_2
    inputs_num_210,      //device_state_num1_1
    inputs_num_210,      //device_state_num1_0
    inputs_operation,    //device_state_operation
    inputs_num_3,        //device_state_num2_3
    inputs_num_210,      //device_state_num2_2
    inputs_num_210,      //device_state_num2_1
    inputs_num_210,      //device_state_num2_0
    inputs_result,       //device_state_result
    NULL,                //device_state_end_NULL
};

callback_func_t callbacks_for_inputs[] = {
    append_digit,           //inputs_digit0
    append_digit,           //inputs_digit1
    append_digit,           //inputs_digit2
    append_digit,           //inputs_digit3
    append_digit,           //inputs_digit4
    append_digit,           //inputs_digit5
    append_digit,           //inputs_digit6
    append_digit,           //inputs_digit7
    append_digit,           //inputs_digit8
    append_digit,           //inputs_digit9
    append_digit,           //inputs_digitA
    append_digit,           //inputs_digitB
    append_digit,           //inputs_digitC
    append_digit,           //inputs_digitD
    append_digit,           //inputs_digitE
    append_digit,           //inputs_digitF
    select_operation,       //inputs_operationPlus
    select_operation,       //inputs_operationMinus
    select_operation,       //inputs_operationMul
    select_operation,       //inputs_operationMod
    memo_operation,         //inputs_memoRead
    memo_operation,         //inputs_memoWrite
    clear_all,              //inputs_nextCalc
    NULL,                   //inputs_NULL
};

device_state_t local_device_state = DEVICE_STATE_FIRST;
int local_input_index = 0;

void select_prev_button()
{
    local_input_index--;
    if (local_input_index < 0)
    {
        local_input_index = 0;
    }

    repaint_input_mode();
}

void select_next_button()
{
    local_input_index++;
    if (inputs_for_states[local_device_state][local_input_index] == inputs_NULL)
    {
        local_input_index--;
    }

    repaint_input_mode();
}

void enter_button()
{
    inputs_t curr_input = inputs_for_states[local_device_state][local_input_index];
    callback_func_t cb = callbacks_for_inputs[curr_input];
    cb(local_device_state, curr_input);

    //switch to next state & loop it
    local_device_state++;
    if (curr_input == inputs_memoRead)
    {
        //skip next 3 digits input
        local_device_state += 3;
    }
    if (local_device_state >= device_state_end_NULL)
    {
        local_device_state = DEVICE_STATE_FIRST;
    }
    local_input_index = 0;

    AJIOB_HAL_timer_a_reset();

    repaint_input_mode();
}

void repaint_input_mode()
{
    inputs_t curr_input = inputs_for_states[local_device_state][local_input_index];
    AJIOB_HAL_display_print_input_mode(curr_input);
}
