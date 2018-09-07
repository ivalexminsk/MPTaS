#include "interrupt.h"

#include "types.h"
#include "led.h"
#include "button.h"
#include "AJIOB_regs_help.h"
#include "interrupt_handlers.h"

void timer_init()
{
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

#define max_timer_value (0x10000)
const long one_second_timer = max_timer_value / 2;

/* Multiply second to this value */
float timer_custom_divider[] = 
{
  1.,
  0.1,
  0.1,
  0.8,
  0.8,
};

void timer_interrupt_enable(ccr_channels_t channel)
{
  /* Set interrupt value */
  unsigned short new_comparator_value = ((unsigned short)(TA1R + (one_second_timer * timer_custom_divider[channel]))) % max_timer_value;

  switch(channel)
  {
  case ccr_button:
    TA1CCR0 = new_comparator_value;
    break;
  case ccr_turn_on:
    TA1CCR1 = new_comparator_value;
    break;
  case ccr_turn_off:
    TA1CCR2 = new_comparator_value;
    break;
  default:
    break;
  }

  /* Enable interrupts */
  switch(channel)
  {
  case ccr_button:
    SET_BITS(TA1CCTL0, BIT4);
    break;
  case ccr_turn_on:
    SET_BITS(TA1CCTL1, BIT4);
    break;
  case ccr_turn_off:
    SET_BITS(TA1CCTL2, BIT4);
    break;
  default:
    break;
  }

  timer_interrupt_clear(channel);
}

void timer_interrupt_disable(ccr_channels_t channel)
{
  switch(channel)
  {
  case ccr_button:
    RESET_BITS(TA1CCTL0, BIT4);
    break;
  case ccr_turn_on:
    RESET_BITS(TA1CCTL1, BIT4);
    break;
  case ccr_turn_off:
    RESET_BITS(TA1CCTL2, BIT4);
    break;
  default:
    break;
  }
}

void timer_interrupt_clear(ccr_channels_t channel)
{
  switch(channel)
  {
  case ccr_button:
    RESET_BITS(TA1CCTL0, BIT0);
    break;
  case ccr_turn_on:
    RESET_BITS(TA1CCTL1, BIT0);
    break;
  case ccr_turn_off:
    RESET_BITS(TA1CCTL2, BIT0);
    break;
  default:
    break;
  }
}
