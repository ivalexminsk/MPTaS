#include "interrupt.h"

#include "types.h"
#include "led.h"
#include "button.h"
#include "AJIOB_regs_help.h"
#include "interrupt_handlers.h"
#include "pmm.h"

void timer_init()
{
  /* Select compare mode */
  //RESET_BITS(TA1CCTL0, BIT8);
  RESET_BITS(TA1CCTL1, BIT8);
  RESET_BITS(TA1CCTL2, BIT8);

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

bool timer_interrupt_vector_read(int val, unsigned short bit_num)
{
  return ((val & (BIT0 << bit_num)) ? true : false);
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
  int val = TA1IV;

  if (timer_interrupt_vector_read(val, ccr_button))
  {
    //crunch: need to locale in interrupt handler:
    if ((current_button_num == LPM_BUTTON) 
      && !button_read(current_button_num) 
      && curr_pmm_mode == pmm_lpm)
    {
      LPM1_EXIT;
    }
    timer_button_callback();
  }
  if (timer_interrupt_vector_read(val, ccr_shift))
  {
    timer_shift_callback();
  }
}

#define max_timer_value (0x10000)
const long one_second_timer = max_timer_value / 2;

/* Multiply second to this value */
float timer_custom_divider[] =
{
  1.,
  0.1,
  0.4,
};

void timer_interrupt_enable(ccr_channels_t channel)
{
  /* Set interrupt value */
  unsigned short new_comparator_value = ((unsigned short)(TA1R + (one_second_timer * timer_custom_divider[channel]))) % max_timer_value;

  switch(channel)
  {
  case ccr_button:
    TA1CCR1 = new_comparator_value;
    break;
  case ccr_shift:
    TA1CCR2 = new_comparator_value;
    break;
  default:
    break;
  }

  /* Enable interrupts */
  switch(channel)
  {
  case ccr_button:
    SET_BITS(TA1CCTL1, BIT4);
    break;
  case ccr_shift:
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
    RESET_BITS(TA1CCTL1, BIT4);
    break;
  case ccr_shift:
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
    RESET_BITS(TA1CCTL1, BIT0);
    break;
  case ccr_shift:
    RESET_BITS(TA1CCTL2, BIT0);
    break;
  default:
    break;
  }
}
