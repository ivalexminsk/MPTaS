#pragma once

#include "driverlib.h"
#include "ff.h"

#define HAL_FILE_NAME "IvAlex_stat.txt"

#define ERROR_LED_PORT GPIO_PORT_P8
#define ERROR_LED_PIN  GPIO_PIN1

void AJIOB_HAL_init_file();
void AJIOB_HAL_write_file();

FRESULT GetFile(char* fileName);
FRESULT WriteFile(char* fileName, char* text, WORD size);
