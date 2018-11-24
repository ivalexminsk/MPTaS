#include "AJIOB_HAL_buttons.h"

#include "HAL_Buttons.h"

void AJIOB_HAL_buttons_init()
{
    Buttons_init(BUTTON_S1);
    Buttons_interruptEnable(BUTTON_S1);
    buttonsPressed = 0;
}

bool AJIOB_HAL_buttons_is_pressed_S1()
{
    bool res = (buttonsPressed & BUTTON_S1);
    buttonsPressed &= ~(BUTTON_S1);
    return res;
}
