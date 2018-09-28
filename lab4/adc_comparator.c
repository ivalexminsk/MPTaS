#include "adc_comparator.h"

#include "AJIOB_regs_help.h"
#include "types.h"
#include "led.h"

void adc_init()
{
    adc_interrupt_disable();

    //enable auto sampling (but need first SHI rising edge)
    SET_BITS(ADC12CTL0, ADC12MSC);

    //TODO:
}

void adc_interrupt_enable()
{
    //enable ADC convertion
    SET_BITS(ADC12CTL0, ADC12ENC);

    //enable ADC
    SET_BITS(ADC12CTL0, ADC12ON);

    //TODO:
}

void adc_interrupt_disable()
{
    //disable ADC
    RESET_BITS(ADC12CTL0, ADC12ON);

    //disable ADC convertion
    RESET_BITS(ADC12CTL0, ADC12ENC);

    //TODO:
}

void adc_interrupt_clear()
{
    //TODO:
}

void adc_output_parse()
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

    //Enable interrupt (main & inverted)
    SET_BITS(CBINT, CBIE);
    SET_BITS(CBINT, CBIIE);
    comparator_interrupt_clear();
}

void comparator_interrupt_disable()
{
    //Disable interrupt
    RESET_BITS(CBINT, CBIE);
    RESET_BITS(CBINT, CBIIE);

    //Disable comparator
    RESET_BITS(CBCTL1, CBON);
}

void comparator_interrupt_clear()
{
    RESET_BITS(CBINT, CBIFG);
    RESET_BITS(CBINT, CBIIFG);
}

void comparator_output_parse()
{
    //value = 1 => (+ > -)
    //value = 0 => (+ < -)
    //+ => PAD3
    //- => PAD5
    bool state = CBCTL1 & CBOUT;
    set_led_state(PAD3_LED, state);
    set_led_state(PAD5_LED, !state);
}
