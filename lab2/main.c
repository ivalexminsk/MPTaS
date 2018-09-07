
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

typedef enum ccr_channels_t
{
  button = 1,
  turn_on,
  turn_off
} ccr_channels_t;

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

  /* Pullup */
  SET_BITS(P1REN, button_bit);
  SET_BITS(P1OUT, button_bit);

  /* Interrrupts */
  SET_BITS(P1IES, button_bit);
  SET_BITS(P1IE, button_bit);
  RESET_BITS(P1IFG, button_bit);
}

void timer_init()
{
  /* Capture/compare interrupt enable */
  SET_BITS(TA1CCTL1, BIT4);

  /* Select compare mode */
  RESET_BITS(TA1CCTL1, BIT8);
  
  /* TASSEL = ACLK */
  SET_BITS(TA1CTL, BIT8);
  RESET_BITS(TA1CTL, BIT9);
  
  /* ID = /1 */
  RESET_BITS(TA1CTL, BIT6);
  RESET_BITS(TA1CTL, BIT7);
  
  /* MC = 10b */
  RESET_BITS(TA1CTL, BIT4);
  SET_BITS(TA1CTL, BIT5);

  // /* TAIE */
  // SET_BITS(TA1CTL, BIT1);

  // /* TAIFG */
  // RESET_BITS(TA1CTL, BIT0);
}

volatile int temp;

void arifm_delay()
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
  arifm_delay();
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

  timer_init();
  
  button_init();

  for (int i = led4; i <= LAST_LED; i++)
  {
    led_init((led_t)i);
  }
  
  /* Load */
  for (int i = led4; i <= LAST_LED; i++)
  {
    set_led_state((led_t)i, true);
  }

  arifm_delay();

  for (int i = led4; i <= LAST_LED; i++)
  {
    set_led_state((led_t)i, false);
  }

  /* Load end */
  
   __bis_SR_register(LPM4_bits + GIE);
  while(1);
}

#pragma vector=PORT1_VECTOR
__interrupt void port1_interrupt()
{
  if (button_read())
  {
    static led_t next_led = led4;
    blink_led(next_led);
    next_led = (led_t)((next_led + 1) % (LAST_LED + 1));
  }
  RESET_BITS(P1IFG, button_bit);
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void timer_a1_interrupt()
{
  static led_t next_led = led4;
  blink_led(next_led);
  next_led = (led_t)((next_led + 1) % (LAST_LED + 1));
  RESET_BITS(TA1CTL, BIT0);
  RESET_BITS(TA1CCTL1, BIT0);
}
