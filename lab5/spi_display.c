#include "spi_display.h"
#include "AJIOB_regs_help.h"
#include "led.h"
#include "FontAJIOB.h"

void spi_display_init()
{
    spi_display_disable();

    // set sync mode (I2C or SPI)
    SET_BITS(UCB1CTL0, UCSYNC);

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
    //// CD (0 = command, 1 = data)
    SET_BITS(P5DIR, BIT6);
    RESET_BITS(P5OUT, BIT6);
    //// BackLight (0 = off, 1 = on)
    SET_BITS(P7DIR, BIT6);
    SET_BITS(P7OUT, BIT6);

    spi_display_enable();

    // enable accelerometer power pins
    //// RST (out, 1 = not rst)
    SET_BITS(P5OUT, BIT7);
}

void spi_display_tx_enable_int()
{
    SET_BITS(UCB1IE, UCTXIE);
    RESET_BITS(UCB1IFG, UCTXIFG);
}

void spi_display_tx_disable_int()
{
    RESET_BITS(UCB1IE, UCTXIE);
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
    RESET_BITS(P5OUT, BIT6);
}

void spi_display_data_mode_enable()
{
    SET_BITS(P5OUT, BIT6);
}

void display_init()
{
    //Start line as 0
    uint8_t scroll_line = 0x40;
    spi_display_send(&scroll_line, 1);

    // SEG reverce (6 o'clock)
    uint8_t seg_direction = 0xA1;
    spi_display_send(&seg_direction, 1);

    // COM reverce
    uint8_t com_direction = 0xC8;
    spi_display_send(&com_direction, 1);

    // Show sram content
    uint8_t enable_sram = 0xA4;
    spi_display_send(&enable_sram, 1);

    // Show sram content in not inverse mode
    uint8_t sram_not_inverse = 0xA6;
    spi_display_send(&sram_not_inverse, 1);

    // Set LCD Bias 1/9 (duty 1/65)
    uint8_t lcd_bias = 0xA2;
    spi_display_send(&lcd_bias, 1);

    // Power Control (Booster, Regularot, Follower on)
    uint8_t power_control = 0x2F;
    spi_display_send(&power_control, 1);

    // VLCD Resistor ratio
    uint8_t vlcd_resistor_ratio = 0x27;
    spi_display_send(&vlcd_resistor_ratio, 1);

    // Set display contrast
    uint8_t display_contrast[] = {0x81, 0x10};
    spi_display_send(display_contrast, sizeof(display_contrast) / sizeof(display_contrast[0]));

    // Set row/column wrap around to off, temp comp = -0,11%/degree C
    uint8_t wrap_around_off[] = {0xFA, 0x90};
    spi_display_send(wrap_around_off, sizeof(wrap_around_off) / sizeof(wrap_around_off[0]));

    // Display enable
    uint8_t display_enable = 0xAF;
    spi_display_send(&display_enable, 1);

    display_clear_full();
}

void display_write_data(uint8_t data)
{
    spi_display_data_mode_enable();

    spi_display_send(&data, 1);

    spi_display_command_mode_enable();
}

void display_clear_full()
{
    for (int i = 0; i < DISPLAY_ROW_PAGES; i++)
    {
        for (int j = 0; j < DISPLAY_COLUMNS; j++)
        {
            display_clear_part(i, j);
        }
    }
}

void display_clear_part(uint8_t row_page, uint8_t column)
{
    display_write_image_sector(row_page, column, DISPLAY_EMPTY_BYTE);
}

void display_write_image_sector(uint8_t row_page, uint8_t column, uint8_t value)
{
    uint8_t page_select_command = 0xB0 | (row_page & 0x0F);
    spi_display_send(&page_select_command, 1);

    uint8_t colunm_select_high = 0x10 | ((column & 0xF0) >> 4);
    spi_display_send(&colunm_select_high, 1);

    uint8_t colunm_select_low = 0x00 | (column & 0x0F);
    spi_display_send(&colunm_select_low, 1);

    display_write_data(value);
}

bool display_is_data_ready = false;
uint8_t* display_send_buff_local = nullptr;
int display_send_size_local = 0;

void spi_display_send(uint8_t* send_buff, int send_size)
{
    display_is_data_ready = false;

    display_send_buff_local = send_buff;
    display_send_size_local = send_size;

    if (!(display_send_size_local))
    {
        //no data to recv/transmit
        return;
    }

    spi_display_cs_enable();

    // start transmitting/receiving
    spi_display_tx_enable_int();
    uint8_t to_send_now = *display_send_buff_local;
    display_send_buff_local++;
    display_send_size_local--;

    GIE_ENABLE;

    UCB1TXBUF = to_send_now;

    while(!display_is_data_ready);

    spi_display_cs_disable();
}

void display_mirror_on()
{
    // SEG no reverce (12 o'clock)
    uint8_t seg_direction = 0xA0;
    spi_display_send(&seg_direction, 1);
}

void display_mirror_off()
{
    // SEG reverce (6 o'clock)
    uint8_t seg_direction = 0xA1;
    spi_display_send(&seg_direction, 1);
}

void display_digit_print(uint8_t digit, uint8_t index, bool is_for_mirror, bool is_clear)
{
    for (uint8_t i = 0; i < SYMBOL_ROW_PAGES; i++)
    {
        uint8_t i_real = i + index * SYMBOL_ROW_PAGES;
        for (uint8_t j = 0; j < SYMBOL_COLUMNS; j++)
        {
            uint8_t j_real = j + (is_for_mirror ? SYMBOL_COLUMN_ALTER : 0);
            uint8_t val_real = (is_clear ? DISPLAY_EMPTY_BYTE : FontAJIOB_array[digit][i * SYMBOL_COLUMNS + j]);

            display_write_image_sector(i_real, j_real, val_real);
        }
    }
}

void display_update(uint8_t new_value)
{
    static uint8_t old_value = 255;
    static bool old_mirror = false;

    bool new_mirror = (new_value > NO_MIRROR_MAX);

    if (old_value != new_value)
    {
        if (old_mirror != new_mirror)
        {
            //clear old
            for (uint8_t i = 0; i < SYMBOLS_ALL; i++)
            {
                display_digit_print(0, i, old_mirror, true);
            }

            //set new mirror
            if (new_mirror)
            {
                display_mirror_on();
            }
            else
            {
                display_mirror_off();
            }
        }

        uint8_t to_write = new_value;

        //(re-)write new value
        for (int8_t i = SYMBOLS_ALL - 1; i >= 0; i--)
        {
            display_digit_print(to_write % NUM_DIGITS, i, new_mirror, false);
            to_write /= NUM_DIGITS;
        }
    }

    old_value = new_value;
    old_mirror = new_mirror;
}

#pragma vector=USCI_B1_VECTOR
__interrupt void spi_display_interrupt()
{
    short value = UCB1IV;
    if (value == 0x02)
    {
        //RX interrupt
        //not used
    }
    else if(value == 0x04)
    {
        //TX interrupt

        if (display_send_size_local)
        {
            //send more data
            UCB1TXBUF = *display_send_buff_local;
            display_send_buff_local++;
            display_send_size_local--;
        }
        else
        {
            spi_display_tx_disable_int();

            display_is_data_ready = true;
        }
    }
}
