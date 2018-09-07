#pragma once

#include "io430.h"

typedef int bool;
#define true 1
#define false 0

typedef enum led_t
{
  led4 = 0,
  led5,
  led6,
  led7,
  led8,
} led_t;

#define FIRST_LED led4
#define LAST_LED led8

typedef enum ccr_channels_t
{
  button = 1,
  turn_on,
  turn_off
} ccr_channels_t;
