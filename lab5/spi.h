#pragma once

#include "types.h"

void spi_init();

void spi_send_recv(uint8_t* in_buff, int in_size, uint8_t* out_buff, int out_size);

// internal
void spi_enable();
void spi_disable();
