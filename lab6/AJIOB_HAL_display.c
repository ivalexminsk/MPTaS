#include "AJIOB_HAL_display.h"

#include "driverlib.h"
#include "HAL_Dogs102x6.h"
#include "IvAlex_Logo.h"

static uint8_t next_scrollline = 0;

void AJIOB_HAL_display_init()
{
    Dogs102x6_init();
    Dogs102x6_backlightInit();
    Dogs102x6_setBacklight(5);

    Dogs102x6_imageDraw(image_data_IvAlex_Logo, 0, 0);
    __delay_cycles(DISPLAY_LOGO_SLEEP_TICKS);
}

void AJIOB_HAL_display_print_value(int8_t val)
{
    int8_t val_recalced = (((int)val) * DISPLAY_ROW_MAX_X_PLUS) / (DISPLAY_PLUS_MAX);

    Dogs102x6_scrollLine(next_scrollline);

    // previous clearing
    for (uint8_t i = 0; i < DISPLAY_LINES_TO_SHOW; i++)
    {
        Dogs102x6_horizontalLineDraw(0, DOGS102x6_X_SIZE - 1,
            (next_scrollline + i) % DOGS102x6_Y_SIZE, DOGS102x6_DRAW_INVERT);
    }

    // calc new line x coordinates to print
    int x_start = (DOGS102x6_X_SIZE / 2) + (val_recalced > 0 ? 0 : (-1));
    int x_stop = (DOGS102x6_X_SIZE / 2) + (val_recalced > 0 ? 1 : (-1)) + val_recalced;

    // print new data
    for (uint8_t i = 0; i < DISPLAY_LINES_TO_SHOW; i++)
    {
        Dogs102x6_horizontalLineDraw(x_start, x_stop,
            (next_scrollline + i) % DOGS102x6_Y_SIZE, DOGS102x6_DRAW_NORMAL);
    }

    // save new scrollline value
    next_scrollline = (next_scrollline + DISPLAY_LINES_TO_SHOW) % DOGS102x6_Y_SIZE;
}
