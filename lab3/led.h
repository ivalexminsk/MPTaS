#pragma once

#include "types.h"

void led_init(led_t led);
void blink_led(led_t led);
void set_led_state(led_t led, bool state);
void led_loggle(led_t led);
bool get_led_state(led_t led);
led_t calc_next_led(led_t led);

void arifm_delay();

#define MAIN_POWER_MODE_LED led1
#define LOW_POWER_MODE_LED led3

#define U_HIGH_LED led4
#define U_LOW_LED led5

#define TIMER_LED led8
