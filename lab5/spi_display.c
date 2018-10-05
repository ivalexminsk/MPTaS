#include "spi_display.h"
#include "AJIOB_regs_help.h"

void spi_display_init()
{
    spi_display_disable();

    // set sync mode (I2C or SPI)
    SET_BITS(UCA0CTL0, UCSYNC);

    // set msb first
    SET_BITS(UCB1CTL0, UCMSB);

    // set 8 bit
    RESET_BITS(UCB1CTL0, UC7BIT);

    // set master mode
    SET_BITS(UCB1CTL0, UCMST);

    // set 3SPI mode
    RESET_BITS(UCB1CTL0, BIT2);
    RESET_BITS(UCB1CTL0, BIT1);

    // set SMCLK as clock
    SET_BITS(UCB1CTL1, BIT7);
    RESET_BITS(UCB1CTL1, BIT6);

    // No modulation
    //UCB1MCTL = 0;

    // set clock divider as 1 (0.7 MHz/1 for display)
    UCB1BR0 = 1;
    UCB1BR1 = 0;

    // enable display spi pins
    //// MISO
    SET_BITS(P4SEL, BIT2);
    //// MOSI
    SET_BITS(P4SEL, BIT1);
    //SET_BITS(P3DIR, BIT3);
    //// SCK
    SET_BITS(P4SEL, BIT3);
    //SET_BITS(P2DIR, BIT7);
    //// CS (out, 1)
    SET_BITS(P7DIR, BIT4);
    SET_BITS(P7OUT, BIT4);
    //// RST (out, 0 = rst)
    SET_BITS(P5DIR, BIT7);
    RESET_BITS(P5OUT, BIT7);
    //// CD (0 = read, 1 = write)
    SET_BITS(P5DIR, BIT6);
    RESET_BITS(P5OUT, BIT6);

    spi_display_enable();

    // enable accelerometer power pins
    //// RST (out, 1 = not rst)
    SET_BITS(P5OUT, BIT7);
}

void spi_display_enable()
{
    // enable spi
    RESET_BITS(UCB1CTL1, UCSWRST);
}

void spi_display_disable()
{
    //TODO: disable interrupts

    // disable spi
    SET_BITS(UCB1CTL1, UCSWRST);
}

void display_init()
{
    //TODO:
}

void display_update()
{
    //TODO:
}
