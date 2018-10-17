#pragma once

#include "types.h"

//periph init
void spi_display_init();

//low-level
void spi_display_disable();
void spi_display_enable();

void spi_display_cs_disable();
void spi_display_cs_enable();

void spi_display_command_mode_enable();
void spi_display_data_mode_enable();

void spi_display_send(uint8_t* send_buff, int send_size);

void display_digit_print(uint8_t digit, uint8_t index, bool is_for_mirror, bool is_clear);
void display_mirror_on();
void display_mirror_off();

//high-level
void display_init();
void display_write_data(uint8_t data);
void display_clear_full();
void display_clear_part(uint8_t row_page, uint8_t column);
void display_write_image_sector(uint8_t row_page, uint8_t column, uint8_t value);
void display_update(uint8_t new_value);

extern bool is_need_to_change_mirror;

#define DISPLAY_EMPTY_BYTE  0x00

#define DISPLAY_ROW_PAGES   8
#define DISPLAY_COLUMNS     132

#define SYMBOL_ROW_PAGES    1
#define SYMBOL_COLUMNS      10
#define SYMBOL_COLUMN_ALTER 30
#define SYMBOLS_ALL         3
#define NO_MIRROR_MAX       0x7F
#define NUM_DIGITS          10

#define SYMBOL_PLUS_INDEX           0
#define SYMBOL_MINUS_INDEX          1
#define SYMBOL_DIGIT_BEGIN_INDEX    2
