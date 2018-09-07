#pragma once

#include "types.h"

void led_init(led_t led);
void blink_led(led_t led);
void set_led_state(led_t led, bool state);
bool get_led_state(led_t led);
led_t calc_next_led(led_t led);

void arifm_delay();
