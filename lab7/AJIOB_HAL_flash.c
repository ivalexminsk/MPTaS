#include "AJIOB_HAL_flash.h"

#include "driverlib.h"

#include <stdint.h>

short AJIOB_read_memo()
{
    return (*((short*)(INFOA_START)));
}

void AJIOB_write_memo(short val)
{
    //Unlock Info Segment A
    FlashCtl_unlockInfoA();

    bool status;

    do {
        //Erase INFOA
        FlashCtl_eraseSegment((uint8_t*)INFOA_START);
        status = FlashCtl_performEraseCheck((uint8_t*)INFOA_START,
            FLASH_SEGMENT_SIZE);
    } while (status == STATUS_FAIL);

    //Write data to INFOA
    FlashCtl_write16((uint16_t*)&val, (uint16_t*)(INFOA_START), 1);

    //Lock Info Segment A
    FlashCtl_lockInfoA();
}
