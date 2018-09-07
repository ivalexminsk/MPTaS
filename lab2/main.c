
#include "types.h"
#include "led.h"
#include "AJIOB_regs_help.h"

int button_bit = BIT7;

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

bool button_read()
{
  return ((P1IN & button_bit) ? true : false);
}

bool timer_iv_read(unsigned short bit)
{
  return ((TA1IV & bit) ? true : false);
}

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  timer_init();
  
  button_init();

  for (int i = FIRST_LED; i <= LAST_LED; i++)
  {
    led_init((led_t)i);
  }
  
  /* Load */
  for (int i = FIRST_LED; i <= LAST_LED; i++)
  {
    set_led_state((led_t)i, true);
  }

  arifm_delay();

  for (int i = FIRST_LED; i <= LAST_LED; i++)
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
    next_led = calc_next_led(next_led);
  }
  RESET_BITS(P1IFG, button_bit);
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void timer_a1_interrupt()
{
  static led_t next_led = led4;
  blink_led(next_led);
  next_led = calc_next_led(next_led);
  //RESET_BITS(TA1CTL, BIT0);
  if (timer_iv_read(BIT1))
  {
    RESET_BITS(TA1CCTL1, BIT0);
    TA1CCR1 = (TA1R + 0x3fff) % 0xffff;
  }
}
