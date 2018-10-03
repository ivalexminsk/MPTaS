#pragma once

#include "types.h"

void led_init(led_t led);
void blink_led(led_t led);
void set_led_state(led_t led, bool state);
void led_loggle(led_t led);
bool get_led_state(led_t led);
led_t calc_next_led(led_t led);

void arifm_delay();

#define PAD3_LED led6
#define PAD5_LED led8

#define POTENTIOM_LED led3
#define TERMO_LED led2
