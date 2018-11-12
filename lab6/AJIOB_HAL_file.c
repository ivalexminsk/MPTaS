#include "AJIOB_HAL_file.h"

#include "HAL_SDCard.h"
#include "SDCard.h"

// additional SDCard API
// FRESULT GetFile(char* fileName);
// FRESULT WriteFile(char* fileName, char* text, WORD size);

void AJIOB_HAL_init_file()
{
}

void AJIOB_HAL_file_error()
{
    GPIO_setAsOutput(ERROR_LED_PORT, ERROR_LED_PIN);
    GPIO_setOutputHighOnPin(ERROR_LED_PORT, ERROR_LED_PIN);
}

void AJIOB_HAL_write_file()
{
}
