#pragma once

void button1_callback();
void button2_callback();
void timer_button_callback();
void timer_shift_callback();

void button_universal_internal_exec();

extern int current_button_num;

#define LPM_BUTTON  1
#define FREQ_BUTTON  2
