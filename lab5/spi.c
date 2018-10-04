#include "spi.h"
#include "AJIOB_regs_help.h"

void spi_init()
{
    spi_disable();

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
    SET_BITS(UCA0CTL1, BIT7);
    RESET_BITS(UCA0CTL1, BIT6);

    // No modulation
    UCA0MCTL = 0;

    // set clock divider as 2 (0.7 MHz/2 for accelerometer)
    UCA0BR0 = 2;
    UCA0BR1 = 0;

    // enable accelerometer spi pins
    //// MISO
    SET_BITS(P3SEL, BIT4);
    //// MOSI
    SET_BITS(P3SEL, BIT3);
    //SET_BITS(P3DIR, BIT3);
    //// SCK
    SET_BITS(P2SEL, BIT7);
    //SET_BITS(P2DIR, BIT7);
    //// interrupts (up -> down => interrupt)
    RESET_BITS(P2DIR, BIT5);
    SET_BITS(P2REN, BIT5);
    SET_BITS(P2OUT, BIT5);
    SET_BITS(P2IES, BIT5);
    SET_BITS(P2IE, BIT5);
    RESET_BITS(P2IFG, BIT5);
    //// CS (out, 1)
    SET_BITS(P3DIR, BIT5);
    SET_BITS(P3OUT, BIT5);

    spi_enable();

    // enable accelerometer power pins
    //// VCC (out, 1), more output current (I) enable
    SET_BITS(P3DS, BIT6);
    SET_BITS(P3DIR, BIT6);
    SET_BITS(P3OUT, BIT6);
}


void spi_rx_enable_int()
{
    SET_BITS(UCA0IE, UCRXIE);
    RESET_BITS(UCA0IFG, UCRXIFG);
}

void spi_tx_enable_int()
{
    SET_BITS(UCA0IE, UCTXIE);
    RESET_BITS(UCA0IFG, UCTXIFG);
}

void spi_rx_disable_int()
{
    RESET_BITS(UCA0IE, UCRXIE);
}

void spi_tx_disable_int()
{
    RESET_BITS(UCA0IE, UCTXIE);
}

void spi_cs_disable()
{
    SET_BITS(P3OUT, BIT5);
}

void spi_cs_enable()
{
    RESET_BITS(P3OUT, BIT5);
}

void spi_enable()
{
    // enable spi
    RESET_BITS(UCA0CTL1, UCSWRST);
}

void spi_disable()
{
    spi_tx_disable_int();
    spi_rx_disable_int();

    // disable spi
    SET_BITS(UCA0CTL1, UCSWRST);
}

bool is_data_ready = false;
uint8_t* send_buff_local = nullptr;
int send_size_local = 0;
uint8_t* recv_buff_local = nullptr;
int recv_size_local = 0;

void spi_send_recv(uint8_t* send_buff, int send_size, uint8_t* recv_buff, int recv_size)
{
    is_data_ready = false;

    send_buff_local = send_buff;
    send_size_local = send_size;
    recv_buff_local = recv_buff;
    recv_size_local = recv_size;

    if (!(send_size_local + recv_size_local))
    {
        //no data to recv/transmit
        return;
    }

    //spi_enable();
    spi_cs_enable();

    // start transmitting/receiving
    uint8_t to_send_now = 0;
    if (send_size_local)
    {
        spi_tx_enable_int();
        to_send_now = *send_buff_local;
        send_buff_local++;
        send_size_local--;
    }
    else
    {
        spi_rx_enable_int();
    }
    UCA0TXBUF = to_send_now;

    while(!is_data_ready);

    spi_cs_disable();
    //spi_disable();
}

#pragma vector=USCI_A0_VECTOR
__interrupt void spi_interrupt()
{
    short value = UCA0IV;
    if (value == 0x02)
    {
        //RX interrupt

        *recv_buff_local = UCA0RXBUF;
        recv_size_local--;
        if (recv_size_local)
        {
            UCA0TXBUF = 0;
            RESET_BITS(UCA0IFG, UCRXIFG);
        }
        else
        {
            spi_rx_disable_int();
            is_data_ready = true;
        }
    }
    else if(value == 0x04)
    {
        //TX interrupt

        if (send_size_local)
        {
            //send more data
            UCA0TXBUF = *send_buff_local;
            send_buff_local++;
            send_size_local--;
        }
        else
        {
            spi_tx_disable_int();

            if (recv_size_local)
            {
                spi_rx_enable_int();

                //recv data
                UCA0TXBUF = 0;
            }
            else
            {
                is_data_ready = true;
            }
        }
    }
}
