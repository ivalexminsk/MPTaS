#pragma once

#include <stdint.h>
#include <stdbool.h>

#define HAL_FILE_NAME "IvAlex.txt"

#define ERROR_LED_PORT GPIO_PORT_P8
#define ERROR_LED_PIN  GPIO_PIN1

void AJIOB_HAL_init_file();
bool AJIOB_HAL_write_file(uint8_t* arr, int size);
bool AJIOB_HAL_read_file(uint8_t* arr, int size);
