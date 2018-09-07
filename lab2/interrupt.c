#include "interrupt.h"

#include "types.h"
#include "led.h"
#include "button.h"
#include "AJIOB_regs_help.h"

void timer_init()
{
//   /* Capture/compare interrupt enable */
//   SET_BITS(TA1CCTL1, BIT4);

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

bool timer_interrupt_vector_read(unsigned short bit_num)
{
  return ((TA1IV & (BIT0 << bit_num)) ? true : false);
}

#pragma weak button1_callback
void button1_callback()
{
}

#pragma weak button2_callback
void button2_callback()
{
}

#pragma weak timer_button_callback
void timer_button_callback()
{
}

#pragma weak timer_turn_on_callback
void timer_turn_on_callback()
{
}

#pragma weak timer_turn_off_callback
void timer_turn_off_callback()
{
}

#pragma vector=PORT1_VECTOR
__interrupt void port1_interrupt()
{
  button1_callback();
}

#pragma vector=PORT2_VECTOR
__interrupt void port2_interrupt()
{
  button2_callback();
}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void timer_a1_interrupt()
{
  if (timer_interrupt_vector_read(ccr_button))
  {
    timer_button_callback();
    // TA1CCR1 = (TA1R + 0x3fff) % 0xffff;
  }
  if (timer_interrupt_vector_read(ccr_turn_on))
  {
    timer_turn_on_callback();
  }
  if (timer_interrupt_vector_read(ccr_turn_off))
  {
    timer_turn_off_callback();
  }
}
