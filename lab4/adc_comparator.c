#include "adc_comparator.h"

#include "AJIOB_regs_help.h"
#include "types.h"

void adc_init()
{
    //TODO:
}

void comparator_init()
{
    //Enable Minus & select PAD5 [CB4]
    CBCTL0_H = CBIPEN + CBIPSEL_4;

    //Enable Plus & select PAD3 [CB2]
    CBCTL0_L = CBIPEN + CBIPSEL_2;

    //Set filter delay to 3600ns
    SET_BITS(CBCTL1, CBFDLY_3);

    //Enable output filter
    SET_BITS(CBCTL1, CBF);

    //Select interrupt rising edge
    RESET_BITS(CBCTL1, CBIES);

    //Set comparator power mode to ultra low power
    SET_BITS(CBCTL1, BIT9);
    RESET_BITS(CBCTL1, BIT8);
}

void comparator_interrupt_enable()
{
    //Enable comparator
    SET_BITS(CBCTL1, CBON);

    //Enable interrupt
    SET_BITS(CBINT, CBIE);
    comparator_interrupt_clear();
}

void comparator_interrupt_disable()
{
    //Disable interrupt
    RESET_BITS(CBINT, CBIE);

    //Disable comparator
    RESET_BITS(CBCTL1, CBON);
}

void comparator_interrupt_clear()
{
    RESET_BITS(CBINT, CBIFG);
}
