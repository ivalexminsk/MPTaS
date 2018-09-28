#pragma once

void adc_init();
void adc_interrupt_enable();
void adc_interrupt_disable();
void adc_interrupt_clear();
void adc_output_parse();

void comparator_init();
void comparator_interrupt_enable();
void comparator_interrupt_disable();
void comparator_interrupt_clear();
void comparator_output_parse();
