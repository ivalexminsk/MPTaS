#include "led.h"

#include "AJIOB_regs_help.h"

#define LED_CHECK                               \
  if ((led > LAST_LED)/* || (led < FIRST_LED)*/)\
  {return;}                                     \

static int led_bits[] = 
{
  BIT1,
  BIT2,
  BIT3,
  BIT4,
  BIT5,
};

void led_init(led_t led)
{
  LED_CHECK;

  int bit = led_bits[led];

  SET_BITS(P1DIR, bit);
  RESET_BITS(P1OUT, bit);
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
  
  int bit = led_bits[led];
  if (state)
  {
    SET_BITS(P1OUT, bit);
  }
  else
  {
    RESET_BITS(P1OUT, bit);
  }
}

bool get_led_state(led_t led)
{  
  int bit = led_bits[led];
  return ((P1OUT & bit) ? true : false);
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
