#pragma once

#include "types.h"

void timer_init();
void timer_interrupt_enable(ccr_channels_t channel);
void timer_interrupt_disable(ccr_channels_t channel);
void timer_interrupt_clear(ccr_channels_t channel);
