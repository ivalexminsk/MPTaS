#pragma once

#define ADC_SCROLL_RIGHT_MIN    0xAAA
#define ADC_SCROLL_LEFT_MAX     0x555

typedef enum pot_state_t
{
    pot_state_left  = -1,
    pot_state_mid   = 0,
    pot_state_right = 1,
} pot_state_t;

void adc_init();
void adc_interrupt_enable();
void adc_interrupt_disable();
void adc_interrupt_clear();
void adc_output_parse();

extern pot_state_t pot_state;
