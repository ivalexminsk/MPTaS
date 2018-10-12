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

//high-level
void display_init();
void display_write_data(uint8_t data);
void display_clear_full();
void display_clear_part(uint8_t row_page, uint8_t column);
void display_update(uint8_t new_value);
