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
    // set clock phase (data is captured on the first UCLK edge and changed on the following edge)
    SET_BITS(UCB1CTL0, UCCKPH);

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

void spi_display_tx_enable_int()
{
    SET_BITS(UCB1IE, UCRXIE);
    RESET_BITS(UCB1IFG, UCRXIFG);
}

void spi_display_tx_disable_int()
{
    RESET_BITS(UCB1IE, UCRXIE);
}

void spi_display_enable()
{
    // enable spi
    RESET_BITS(UCB1CTL1, UCSWRST);

    spi_display_tx_enable_int();
}

void spi_display_disable()
{
    spi_display_tx_disable_int();

    // disable spi
    SET_BITS(UCB1CTL1, UCSWRST);
}

void spi_display_cs_disable()
{
    SET_BITS(P7OUT, BIT4);
}

void spi_display_cs_enable()
{
    RESET_BITS(P7OUT, BIT4);
}

void spi_display_command_mode_enable()
{
    RESET_BITS(P7OUT, BIT4);
}

void spi_display_data_mode_enable()
{
    SET_BITS(P7OUT, BIT4);
}

void display_init()
{
    //TODO:
}

void display_update()
{
    //TODO:
}
