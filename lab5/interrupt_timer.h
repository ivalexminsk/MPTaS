#pragma once

#include "types.h"

void timer_init();
void timer_a_init();
void timer_b_init();
void timer_interrupt_enable(ccr_channels_t channel);
void timer_interrupt_disable(ccr_channels_t channel);
void timer_interrupt_clear(ccr_channels_t channel);

void timer_b_interrupt_enable();
void timer_b_interrupt_clear();
