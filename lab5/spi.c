#include "spi.h"
#include "AJIOB_regs_help.h"

void spi_init()
{
    // set msb first
    SET_BITS(UCA0CTL0, UCMSB);

    // set 8 bit
    RESET_BITS(UCA0CTL0, UC7BIT);

    // set master mode
    SET_BITS(UCA0CTL0, UCMST);

    // set 4SPI mode, ss - active = low
    SET_BITS(UCA0CTL0, BIT2);
    RESET_BITS(UCA0CTL0, BIT1);

    // set SMCLK as clock
    SET_BITS(UCA0CTL1, (BIT7 | BIT6));

    // set clock divider as 1
    UCA0BR0 = 0;
    UCA0BR1 = 0;
}

void spi_enable()
{
    // enable spi
    RESET_BITS(UCA0CTL1, UCSWRST);

    //enable interrupts
    SET_BITS(UCA0IE, UCTXIE);
    SET_BITS(UCA0IE, UCRXIE);

    //reset flags
    RESET_BITS(UCA0IFG, UCTXIFG);
    RESET_BITS(UCA0IFG, UCRXIFG);
}

void spi_disable()
{
    UCA0IE = 0;

    // disable spi
    SET_BITS(UCA0CTL1, UCSWRST);
}

void spi_send_recv(uint8_t* in_buff, int in_size, uint8_t* out_buff, int out_size)
{
    //TODO:
}

#pragma vector=USCI_A0_VECTOR
__interrupt void spi_interrupt()
{
    if (UCA0IFG & UCTXIFG)
    {
        //TX interrupt

        //TODO:

        RESET_BITS(UCA0IFG, UCTXIFG);
    }
    else if(UCA0IFG & UCRXIFG)
    {
        //RX interrupt

        //TODO:

        RESET_BITS(UCA0IFG, UCRXIFG);
    }
}
