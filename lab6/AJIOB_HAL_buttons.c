#include "AJIOB_HAL_buttons.h"

#include "HAL_Buttons.h"

void AJIOB_HAL_buttons_init()
{
    Buttons_init(BUTTON_S2);
    Buttons_interruptEnable(BUTTON_S2);
    buttonsPressed = 0;
}

bool AJIOB_HAL_buttons_is_pressed_S2()
{
    return (buttonsPressed & BUTTON_S2);
}
