#include "AJIOB_HAL_pads.h"

#include "HAL_Dogs102x6.h"
#include "HAL_Buttons.h"
#include "HAL_Board.h"
#include "CTS_Layer.h"
#include "HAL_UCS.h"
#include "HAL_PMM.h"

void AJIOB_HAL_pads_init()
{
    // Set Vcore to accomodate for max. allowed system speed
    SetVCore(3);

    // Set system clock to max (25MHz)
    Init_FLL_Settle(25000, 762);

    // Configure CapTouch ports
    P1OUT &= ~0x7E;
    P1DIR |= 0x7E;
    P6OUT = 0x00;
    P6DIR = 0x00;

    Buttons_init(BUTTON_S2);
    Buttons_interruptEnable(BUTTON_S2);
    buttonsPressed = 0;
}

void CapDemo(void)
{
    uint8_t quit = 0, spacing = 0, height = 0, height1 = 0, i;
    uint16_t deltaCount[5];

    Dogs102x6_clearScreen();

    buttonsPressed = 0;

    TI_CAPT_Init_Baseline(&slider);
    buttonDebounce = 0;

    Dogs102x6_stringDraw(0, 0, "== Touch  Demo ==", DOGS102x6_DRAW_NORMAL);

    //menu active until selection is made
    while (!quit)
    {
        TI_CAPT_Custom(&slider, deltaCount);

        // 5 = No. of sensors
        for (i = 0; i < 5; i++)
        {
            spacing = 20 * i + 10;

            if (deltaCount[i] < 4000)
                height = 63 - deltaCount[i] / 60;
            else
                height = 10;

            // Limit the height of the columns
            if (height < 10)
                height = 10;

            // three pixels wide
            Dogs102x6_verticalLineDraw(63, height, spacing - 1, DOGS102x6_DRAW_NORMAL);
            Dogs102x6_verticalLineDraw(63, height, spacing, DOGS102x6_DRAW_NORMAL);
            Dogs102x6_verticalLineDraw(63, height, spacing + 1, DOGS102x6_DRAW_NORMAL);

            __delay_cycles(1000);

            // erasing old lines
            Dogs102x6_verticalLineDraw(height, 8, spacing, DOGS102x6_DRAW_INVERT);
            Dogs102x6_verticalLineDraw(height, 8, spacing - 1, DOGS102x6_DRAW_INVERT);
            Dogs102x6_verticalLineDraw(height, 8, spacing + 1, DOGS102x6_DRAW_INVERT);

            if (i < 4)
            {
                //for the "in between" heights
                if (deltaCount[i + 1] < 2400)
                    height1 = 63 - deltaCount[i + 1] / 40;
                else
                    height1 = 10;

                // Limit the height of the columns
                if (height + height1 < 10)
                    height1 = 10;

                Dogs102x6_verticalLineDraw(63, (height + height1) / 2, (spacing + 10),
                                           DOGS102x6_DRAW_NORMAL);
                Dogs102x6_verticalLineDraw(63, (height + height1) / 2, (spacing + 11),
                                           DOGS102x6_DRAW_NORMAL);
                Dogs102x6_verticalLineDraw(63, (height + height1) / 2, (spacing + 9),
                                           DOGS102x6_DRAW_NORMAL);

                __delay_cycles(1000);

                Dogs102x6_verticalLineDraw((height + height1) / 2, 8, (spacing + 11),
                                           DOGS102x6_DRAW_INVERT);
                Dogs102x6_verticalLineDraw((height + height1) / 2, 8, (spacing + 10),
                                           DOGS102x6_DRAW_INVERT);
                Dogs102x6_verticalLineDraw((height + height1) / 2, 8, (spacing + 9),
                                           DOGS102x6_DRAW_INVERT);
            }
        }

        if ((buttonsPressed & BUTTON_S2))
            quit = 1;
    }

    Board_ledOff(LED_ALL);
    Dogs102x6_clearScreen();
    buttonDebounce = 1;
    buttonsPressed = 0;
}
