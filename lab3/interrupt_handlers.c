#include "types.h"
#include "interrupt.h"
#include "led.h"
#include "button.h"

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
                led_state = ((current_button_num == 1) ? true : false);
	}

	timer_interrupt_disable(ccr_button);

	button_interrupt_enable(1);
	button_interrupt_enable(2);
}

void timer_shift_callback()
{
	led_t current_led = LAST_LED;

	for(; current_led > FIRST_LED; current_led--)
	{
		set_led_state(current_led, get_led_state(current_led - 1));
	}

	set_led_state(FIRST_LED, led_state);

	//timer_interrupt_clear(ccr_shift);
	timer_interrupt_enable(ccr_shift);
}
