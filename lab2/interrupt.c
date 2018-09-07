#include "interrupt.h"

#include "types.h"
#include "led.h"
#include "button.h"
#include "AJIOB_regs_help.h"

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

bool timer_interrupt_vector_read(unsigned short bit)
{
  return ((TA1IV & bit) ? true : false);
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
  if (timer_interrupt_vector_read(BIT1))
  {
    RESET_BITS(TA1CCTL1, BIT0);
    TA1CCR1 = (TA1R + 0x3fff) % 0xffff;
  }
}
