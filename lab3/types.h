#pragma once

#include "io430.h"

typedef int bool;
#define true 1
#define false 0

typedef enum led_t
{
  led1 = 0,
  led2,
  led3,
  led4,
  led5,
  led6,
  led7,
  led8,
} led_t;

#define FIRST_LED led1
#define LAST_LED led8

typedef unsigned char volatile out_port_type_t;

typedef struct led_info_t
{
  out_port_type_t* dir_port;
  out_port_type_t* out_port;
  unsigned short bit_mask;
} led_info_t;

typedef enum ccr_channels_t
{
  ccr_button = 1,
  ccr_shift = 2,
} ccr_channels_t;
