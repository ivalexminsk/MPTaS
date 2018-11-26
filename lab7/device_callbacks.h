#pragma once

#include "device_state.h"

typedef void (*callback_func_t)(device_state_t curr_state, inputs_t curr_input);

void append_digit(device_state_t curr_state, inputs_t curr_input);
void select_operation(device_state_t curr_state, inputs_t curr_input);
void memo_operation(device_state_t curr_state, inputs_t curr_input);
void clear_all(device_state_t curr_state, inputs_t curr_input);
void calculate_res(device_state_t curr_state, inputs_t curr_input);
