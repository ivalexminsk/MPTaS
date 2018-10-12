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
void accelerometer_write_reg(uint8_t reg, uint8_t value);

#define REQUIRED_WHO_AM_I       0x17
#define REQUIRED_REVID          0x10

#define REG_WHO_AM_I            0x00
#define REG_REV_ID              0x01
#define REG_CTRL                0x02
#define REG_INT_STATUS          0x05
#define REG_MOTION_THRESHILD    0x09
