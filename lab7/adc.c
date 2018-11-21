#include "adc.h"

#include <stdbool.h>

#include "driverlib.h"
#include "AJIOB_regs_help.h"

void adc_init()
{
    adc_interrupt_disable();

    //enable temperature sensor
    SET_BITS(REFCTL0, REFMSTR);
    SET_BITS(REFCTL0, REFON);

    //enable potentiometer
    ////set potentiometer output as analog input
    SET_BITS(P6SEL, BIT5);
    ////set potentiometer input (max value) to "1"
    SET_BITS(P8DIR, BIT0);
    SET_BITS(P8OUT, BIT0);

    //select start scanning from 0
    RESET_BITS(ADC12CTL1, (ADC12CSTARTADD0 | ADC12CSTARTADD1 | ADC12CSTARTADD2 | ADC12CSTARTADD3));

    //Source select = ADC12SC
    RESET_BITS(ADC12CTL1, (ADC12SHS0 | ADC12SHS1));

    //adc clock select (SMCLK)
    SET_BITS(ADC12CTL1, (ADC12SSEL0 | ADC12SSEL1));

    //Pulse mode enable
    SET_BITS(ADC12CTL1, ADC12SHP);

    //repeated multichannel mode select
    SET_BITS(ADC12CTL1, (ADC12CONSEQ0 | ADC12CONSEQ1));

    //enable auto sampling (but need first SHI rising edge)
    SET_BITS(ADC12CTL0, ADC12MSC);

    //set adc resolution for 8 bits
    RESET_BITS(ADC12CTL2, (BIT5 | BIT4));

    //set sample rate buffer to 50ksps
    RESET_BITS(ADC12CTL2, ADC12SR);

    // channel 0 config (select potentiometer as source)
    RESET_BITS(ADC12MCTL0, ADC12INCH_15);
    SET_BITS(ADC12MCTL0, ADC12INCH_5);

    // channel 1 config (select temp as source)
    ///set channel 1 as last for adc
    SET_BITS(ADC12MCTL1, ADC12EOS);
    ///select channel source
    RESET_BITS(ADC12MCTL1, ADC12INCH_15);
    SET_BITS(ADC12MCTL1, ADC12INCH_10);
}

void adc_interrupt_enable()
{
    //enable ADC
    SET_BITS(ADC12CTL0, ADC12ON);

    //enable ADC convertion and start calc
    SET_BITS(ADC12CTL0, (ADC12ENC | ADC12SC));

    ///enable channel 1 interrupts
    SET_BITS(ADC12IE, ADC12IE1);

    adc_interrupt_clear();
}

void adc_interrupt_disable()
{
    //disable interrupts
    RESET_BITS(ADC12IE, ADC12IE1);

    //disable ADC
    RESET_BITS(ADC12CTL0, ADC12ON);

    //disable ADC convertion and reset start calc bit
    RESET_BITS(ADC12CTL0, (ADC12ENC | ADC12SC));
}

void adc_interrupt_clear()
{
    RESET_BITS(ADC12IFG, ADC12IFG1);
}

void adc_output_parse()
{
    //channel 0 = temp
    //channel 1 = potentiom
    short val_temp = ADC12MEM0;
    short val_potent = ADC12MEM1;

    //TODO: parse POT value
}
