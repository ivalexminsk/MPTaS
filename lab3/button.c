#include "button.h"

#include "AJIOB_regs_help.h"

static gpio_info_t button_info[] = 
{
  {
    .bit_mask = BIT0,
  },
  {
    .dir_port = &P1DIR,
    .out_port = &P1OUT,
    .ren_port = &P1REN,
    .ies_port = &P1IES,
    .ie_port  = &P1IE,
    .ifg_port = &P1IFG,
    .in_port  = &P1IN,
    .bit_mask = BIT7,
  },
  {
    .dir_port = &P2DIR,
    .out_port = &P2OUT,
    .ren_port = &P2REN,
    .ies_port = &P2IES,
    .ie_port  = &P2IE,
    .ifg_port = &P2IFG,
    .in_port  = &P2IN,
    .bit_mask = BIT2,
  },
};

void button_init(int num)
{
  gpio_info_t info = button_info[num];
  int button_bit = info.bit_mask;

  RESET_BITS(*(info.dir_port), button_bit);

  /* Pullup */
  SET_BITS(*(info.ren_port), button_bit);
  SET_BITS(*(info.out_port), button_bit);

  /* Interrrupts */
  SET_BITS(*(info.ies_port), button_bit);

  button_interrupt_enable(num);
}

bool button_read(int num)
{
  gpio_info_t info = button_info[num];
  int value = ((*(info.in_port)) & (info.bit_mask));
  return (value ? true : false);
}

void button_interrupt_enable(int num)
{
  gpio_info_t info = button_info[num];
  SET_BITS(*(info.ie_port), info.bit_mask);
  
  button_interrupt_clear(num);
}

void button_interrupt_disable(int num)
{
  gpio_info_t info = button_info[num];
  RESET_BITS(*(info.ie_port), info.bit_mask);
}

void button_interrupt_clear(int num)
{
  gpio_info_t info = button_info[num];
  RESET_BITS(*(info.ifg_port), info.bit_mask);
}
