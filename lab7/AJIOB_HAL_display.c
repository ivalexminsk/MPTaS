#include "AJIOB_HAL_display.h"

#include "driverlib.h"
#include "HAL_Dogs102x6.h"
#include "IvAlex_Logo.h"

// internal prototypes

//definitions

void AJIOB_HAL_display_init()
{
    Dogs102x6_init();
    Dogs102x6_backlightInit();
    Dogs102x6_setBacklight(5);

    Dogs102x6_imageDraw(image_data_IvAlex_Logo, 0, 0);
    __delay_cycles(DISPLAY_LOGO_SLEEP_TICKS);
}

void AJIOB_HAL_display_print_input_mode(inputs_t mode)
{
    //TODO:
}

void AJIOB_HAL_display_print_answer(long val)
{
    int8_t symbols = (sizeof(val) * 2);
    for (int8_t i = 0; i < symbols; i++)
    {
        int8_t start_pos = symbols - i - 1;
        Dogs102x6_charDraw(DISPLAY_FONT_Y_ANSWER, start_pos * DISPLAY_FONT_X_STEP,
            val & 0xF, DOGS102x6_DRAW_NORMAL);

        val >>= 4;
    }
}
