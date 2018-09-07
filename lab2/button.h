#pragma once

#include "types.h"

void button_init(int num);
bool button_read(int num);
void button_interrupt_enable(int num);
void button_interrupt_disable(int num);

extern const int button1_bit;
extern const int button2_bit;
