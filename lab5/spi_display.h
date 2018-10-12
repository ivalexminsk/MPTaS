#pragma once

#include "types.h"

void spi_display_init();

void spi_display_disable();
void spi_display_enable();

void spi_display_cs_disable();
void spi_display_cs_enable();

void spi_display_send(uint8_t* send_buff, int send_size);

void display_init();
void display_clear_full();
void display_clear_part(uint8_t row, uint8_t column);
void display_update();
