#include "led.h"

#include "AJIOB_regs_help.h"

#define LED_CHECK                               \
  if ((led > LAST_LED)/* || (led < FIRST_LED)*/)\
  {return;}                                     \

static gpio_info_t led_bits[] = 
{
  { //1.0
    .dir_port = &P1DIR,
    .out_port = &P1OUT,
    .bit_mask = BIT0,
  },
  { //8.1
    .dir_port = &P8DIR,
    .out_port = &P8OUT,
    .bit_mask = BIT1,
  },
  { //8.2
    .dir_port = &P8DIR,
    .out_port = &P8OUT,
    .bit_mask = BIT2,
  },
  { //1.1
    .dir_port = &P1DIR,
    .out_port = &P1OUT,
    .bit_mask = BIT1,
  },
  { //1.2
    .dir_port = &P1DIR,
    .out_port = &P1OUT,
    .bit_mask = BIT2,
  },
  { //1.3
    .dir_port = &P1DIR,
    .out_port = &P1OUT,
    .bit_mask = BIT3,
  },
  { //1.4
    .dir_port = &P1DIR,
    .out_port = &P1OUT,
    .bit_mask = BIT4,
  },
  { //1.5
    .dir_port = &P1DIR,
    .out_port = &P1OUT,
    .bit_mask = BIT5,
  },
};

void led_init(led_t led)
{
  LED_CHECK;

  gpio_info_t bit_info = led_bits[led];

  SET_BITS(*(bit_info.dir_port), bit_info.bit_mask);
  RESET_BITS(*(bit_info.out_port), bit_info.bit_mask);
}

void blink_led(led_t led)
{
  LED_CHECK;

  set_led_state(led, true);
  arifm_delay();
  set_led_state(led, false);
}

void set_led_state(led_t led, bool state)
{
  LED_CHECK;
  
  gpio_info_t bit_info = led_bits[led];
  if (state)
  {
    SET_BITS(*(bit_info.out_port), bit_info.bit_mask);
  }
  else
  {
    RESET_BITS(*(bit_info.out_port), bit_info.bit_mask);
  }
}

bool get_led_state(led_t led)
{  
  int bit = led_bits[led].bit_mask;
  out_port_type_t* out = led_bits[led].out_port;
  return (((*out) & bit) ? true : false);
}

void arifm_delay()
{
  static volatile int temp;
  for(int i = 0; i < 3000; i++)
  {
    temp *= (37 - i) * (2 + i);
  }
}

led_t calc_next_led(led_t led)
{
    return ((led_t)((led + 1) % (LAST_LED + 1)));
}
