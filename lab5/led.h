#pragma once

#include "types.h"

void led_init(led_t led);
void blink_led(led_t led);
void set_led_state(led_t led, bool state);
void led_loggle(led_t led);
bool get_led_state(led_t led);
led_t calc_next_led(led_t led);

void arifm_delay();
void long_delay();

#define ERROR_LED led1
#define GOOD_LED led3
