#include "AJIOB_HAL_file.h"

#include <string.h>

#include "ff.h"
#include "driverlib.h"
#include "HAL_SDCard.h"
#include "SDCard.h"

// additional hidden SDCard API
extern char buff[];
FRESULT GetFile(char* fileName);
FRESULT WriteFile(char* fileName, char* text, WORD size);

// internal prototypes
void AJIOB_HAL_file_error();

// function definitions

void AJIOB_HAL_init_file()
{
    SDCard_init();
}

void AJIOB_HAL_file_error()
{
    GPIO_setAsOutputPin(ERROR_LED_PORT, ERROR_LED_PIN);
    GPIO_setOutputHighOnPin(ERROR_LED_PORT, ERROR_LED_PIN);
}

bool AJIOB_HAL_write_file(uint8_t* arr, int size)
{
    FRESULT rc = WriteFile(HAL_FILE_NAME, (char*)arr, size);
    bool is_success = (rc == FR_OK);
    if (!is_success)
    {
        AJIOB_HAL_file_error();
    }
    return is_success;
}

bool AJIOB_HAL_read_file(uint8_t* arr, int size)
{
    FRESULT rc = GetFile(HAL_FILE_NAME);
    
    bool is_success = (rc == FR_OK);
    if (!is_success)
    {
        AJIOB_HAL_file_error();
    }

    memcpy(arr, buff, size);

    return is_success;
}
