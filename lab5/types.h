#pragma once

#include "io430.h"

#define BIT10 BITA
#define BIT11 BITB
#define BIT12 BITC
#define BIT13 BITD
#define BIT14 BITE
#define BIT15 BITF

typedef int bool;
#define true 1
#define false 0

typedef unsigned char uint8_t;
#define nullptr 0

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

typedef struct gpio_info_t
{
  out_port_type_t* dir_port;
  out_port_type_t* out_port;
  out_port_type_t* ren_port;
  out_port_type_t* ies_port;
  out_port_type_t* ie_port;
  out_port_type_t* ifg_port;
  out_port_type_t* in_port;
  unsigned short bit_mask;
} gpio_info_t;

typedef enum ccr_channels_t
{
  ccr_button = 1,
  ccr_shift = 2,
} ccr_channels_t;

#define VCORE_MIN 1
#define VCORE_MAX 3
