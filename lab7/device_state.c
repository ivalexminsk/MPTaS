#include "device_state.h"

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
};

device_state_t local_device_state = device_state_num1_3;

void select_prev_button()
{
    //TODO:
}

void select_next_button()
{
    //TODO:
}

void enter_button()
{
    //TODO:
}
