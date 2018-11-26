#pragma once

typedef enum device_state_t
{
    device_state_begin_NULL = 0,    //Begin of sequence flag
    device_state_num1_3,
    device_state_num1_2,
    device_state_num1_1,
    device_state_num1_0,
    device_state_operation,
    device_state_num2_3,
    device_state_num2_2,
    device_state_num2_1,
    device_state_num2_0,
    device_state_result,
    device_state_end_NULL,          //End of sequence flag
} device_state_t;

#define DEVICE_STATE_FIRST (device_state_t)(device_state_begin_NULL + 1)
#define DEVICE_STATE_LAST  (device_state_t)(device_state_end_NULL - 1)

typedef enum inputs_t
{
    inputs_digit0 = 0,
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
    inputs_operationPlus,
    inputs_operationMinus,
    inputs_operationMul,
    inputs_operationMod,
    inputs_memoRead,
    inputs_memoWrite,
    inputs_nextCalc,
    inputs_NULL,    //Must be always last
} inputs_t;

void select_prev_button();
void select_next_button();
void enter_button();
void repaint_input_mode();
