#include "button.h"

#include "AJIOB_regs_help.h"

const int button1_bit = BIT7;
const int button2_bit = BIT2;

void button_init(int num)
{
  if (num == 1)
  {
    int button_bit = button1_bit;

    RESET_BITS(P1DIR, button_bit);

    /* Pullup */
    SET_BITS(P1REN, button_bit);
    SET_BITS(P1OUT, button_bit);

    /* Interrrupts */
    SET_BITS(P1IES, button_bit);
  }
  else if (num == 2)
  {
    int button_bit = button2_bit;

    RESET_BITS(P2DIR, button_bit);

    /* Pullup */
    SET_BITS(P2REN, button_bit);
    SET_BITS(P2OUT, button_bit);

    /* Interrrupts */
    SET_BITS(P2IES, button_bit);
  }

  button_interrupt_enable(num);
}

bool button_read(int num)
{
  int value;
  switch(num)
  {
  case 1:
    value = (P1IN & button1_bit);
    break;
  case 2:
    value = (P2IN & button2_bit);
    break;
  default:
    value = 0;
    break;
  }
  return (value ? true : false);
}

void button_interrupt_enable(int num)
{
  if (num == 1)
  {
    SET_BITS(P1IE, button1_bit);
  }
  else if (num == 2)
  {
    SET_BITS(P2IE, button2_bit);
  }

  button_interrupt_clear(num);
}

void button_interrupt_disable(int num)
{
  if (num == 1)
  {
    RESET_BITS(P1IE, button1_bit);
  }
  else if (num == 2)
  {
    RESET_BITS(P2IE, button2_bit);
  }
}

void button_interrupt_clear(int num)
{
  if (num == 1)
  {
    RESET_BITS(P1IFG, button1_bit);
  }
  else if (num == 2)
  {
    RESET_BITS(P2IFG, button2_bit);
  }
}
