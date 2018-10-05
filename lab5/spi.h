#pragma once

#include "types.h"

void spi_init();

void spi_send_recv(uint8_t* in_buff, int in_size, uint8_t* out_buff, int out_size);

void accelerometer_init();
void accelerometer_interrupt_handle();

// internal
void spi_enable();
void spi_disable();

void spi_rx_enable_int();
void spi_tx_enable_int();
void spi_rx_disable_int();
void spi_tx_disable_int();
void spi_cs_disable();
void spi_cs_enable();

uint8_t accelerometer_read_reg(uint8_t reg);
