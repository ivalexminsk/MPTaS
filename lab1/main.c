
#include "io430.h"

#include "AJIOB_helpful.h"

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

#define LAST_LED led8

#define LED_CHECK                               \
  if ((led > LAST_LED)/* || (led < led4)*/)         \
  {return;}                                     \

int led_bits[] = 
{
  BIT1,
  BIT2,
  BIT3,
  BIT4,
  BIT5,
};

int button_bit = BIT7;

void led_init(led_t led)
{
  LED_CHECK;

  int bit = led_bits[led];

  SET_BITS(P1DIR, bit);
  RESET_BITS(P1OUT, bit);
}

void button_init()
{
  RESET_BITS(P1DIR, button_bit);
  SET_BITS(P1REN, button_bit);
  SET_BITS(P1OUT, button_bit);
}

volatile int temp;

void delay()
{
  for(int i = 0; i < 10000; i++)
  {
    temp *= (37 - i) * (2 + i);
  }
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

void blink_led(led_t led)
{
  LED_CHECK;

  set_led_state(led, true);
  delay();
  set_led_state(led, false);
}

bool button_read()
{
  return ((P1IN & button_bit) ? true : false);
}

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  button_init();

  for (int i = led4; i <= LAST_LED; i++)
  {
    led_init((led_t)i);
  }

  led_t next_led = led4;
  bool curr_button_state = false;

  while(1)
  {
    bool new_button_state = button_read();
    if (new_button_state != curr_button_state)
    {
      blink_led(next_led);
      next_led = (led_t)((next_led + 1) % (LAST_LED + 1));
    }

    curr_button_state = new_button_state;
  }
}
