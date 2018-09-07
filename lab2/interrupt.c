#include "interrupt.h"

#include "types.h"
#include "led.h"
#include "button.h"
#include "AJIOB_regs_help.h"

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

#pragma weak button1_callback
void button1_callback()
{
}

#pragma weak button2_callback
void button2_callback()
{
}

#pragma weak timer_button_1_callback
void timer_button_1_callback()
{
}

#pragma weak timer_button_2_callback
void timer_button_2_callback()
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
  if (timer_interrupt_vector_read(ccr_button_1))
  {
    timer_button_1_callback();
  }
  if (timer_interrupt_vector_read(ccr_button_2))
  {
    timer_button_2_callback();
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

unsigned short volatile* timer_cctl[] = 
{
  &TA1CCTL0,
  &TA1CCTL1,
  &TA1CCTL2,
  &TA1CCTL2,
  &TA1CCTL2,
};

unsigned short volatile* timer_ccr[] = 
{
  &TA1CCR0,
  &TA1CCR1,
  &TA1CCR2,
  &TA1CCR2,
  &TA1CCR2,
};

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
  unsigned short volatile* ccr_ptr = timer_ccr[channel];
  *ccr_ptr = ((unsigned short)(TA1R + (one_second_timer * timer_custom_divider[channel]))) % max_timer_value;

  /* Enable interrupts */
  unsigned short volatile* reg_ptr = timer_cctl[channel];
  SET_BITS(*reg_ptr, BIT4);

  timer_interrupt_clear(channel);
}

void timer_interrupt_disable(ccr_channels_t channel)
{
  unsigned short volatile* reg_ptr = timer_cctl[channel];
  RESET_BITS(*reg_ptr, BIT4);
}

void timer_interrupt_clear(ccr_channels_t channel)
{
  unsigned short volatile* reg_ptr = timer_cctl[channel];
  RESET_BITS(*reg_ptr, BIT0);
}
