#include "types.h"
#include "interrupt.h"
#include "interrupt_handlers.h"
#include "led.h"
#include "button.h"
#include "adc_comparator.h"

int current_button_num = 1;
bool led_state = false;

void button_main_callback()
{
	button_interrupt_disable(1);
	button_interrupt_disable(2);

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
		adc_interrupt_disable();
		set_led_state(POTENTIOM_LED, false);
		set_led_state(TERMO_LED, false);
		comparator_interrupt_enable();
	}
	else
	{
		//S2
		comparator_interrupt_disable();
		set_led_state(PAD3_LED, false);
		set_led_state(PAD5_LED, false);
		adc_interrupt_enable();
	}
}
