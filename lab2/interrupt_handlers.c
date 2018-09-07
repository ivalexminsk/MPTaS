#include "types.h"
#include "interrupt.h"
#include "led.h"

bool isS1 = true;

// Turn on button
void button1_callback()
{
	button_interrupt_disable(1);
	button_interrupt_clear(1);
	isS1 = true;
	timer_interrupt_enable(ccr_button1);
}

// Turn off
void button2_callback()
{
	button_interrupt_disable(2);
	button_interrupt_clear(2);
	isS1 = false;
	timer_interrupt_enable(ccr_button2);
}

void timer_button_callback()
{
	if (isS1) 
	{
		button_interrupt_enable(1);

		timer_interrupt_disable(ccr_button1);
		timer_interrupt_clear(ccr_button1);

		timer_interrupt_enable(turn_on);
	}
	else
	{
		button_interrupt_enable(2);

		timer_interrupt_disable(ccr_button2);
		timer_interrupt_clear(ccr_button2);
		
		timer_interrupt_enable(turn_off);
	}
}

void timer_turn_on_callback()
{
	static led_t current_led = led4;

	set_led_state(current_led, true);

	if (current_led == led8)
	{
		timer_interrupt_disable(turn_on);
		timer_interrupt_clear(turn_on);
	}

	current_led = calc_next_led(current_led);
}

void timer_turn_off_callback()
{
	static led_t current_led = led8;
	
	set_led_state(current_led, false);

	if (current_led == led4)
	{
		timer_interrupt_disable(turn_off);
		timer_interrupt_clear(turn_off);
	}

	current_led = calc_next_led(current_led);
}