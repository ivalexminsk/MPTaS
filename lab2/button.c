#include "button.h"

#include "AJIOB_regs_help.h"

const int button_bit = BIT7;

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

bool button_read()
{
  return ((P1IN & button_bit) ? true : false);
}
