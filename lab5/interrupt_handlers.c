#include "types.h"
#include "interrupt_timer.h"
#include "interrupt_handlers.h"
#include "led.h"
#include "button.h"
#include "spi_display.h"

int current_button_num = 1;
bool led_state = false;

void button_main_callback()
{
	button_interrupt_disable(1);
	// button_interrupt_disable(2);

	timer_interrupt_enable(ccr_button);
}

// Turn on button
void button1_callback()
{
	current_button_num = 1;
	button_main_callback();
}

// Turn off
void button2_callback()
{
	current_button_num = 2;
	button_main_callback();
}

void timer_button_callback()
{
	if (!button_read(current_button_num))
	{
		/* Not miss click */
		button_universal_internal_exec();
	}

	timer_interrupt_disable(ccr_button);

	button_interrupt_enable(1);
	button_interrupt_enable(2);
}

void timer_shift_callback()
{
    //TODO
}

void button_universal_internal_exec()
{
	if (current_button_num == 1)
	{
		//S1
		is_need_to_change_mirror = true;
	}
	else
	{
		//S2
	}
}
