#include "types.h"
#include "interrupt.h"
#include "led.h"
#include "button.h"

int current_button_num = 1;

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
	ccr_channels_t ccr_command = (current_button_num == 1 ? ccr_turn_on : ccr_turn_off);

	if (!button_read(current_button_num))
	{
		/* Not miss click */
		timer_interrupt_enable(ccr_command);
	}

	timer_interrupt_disable(ccr_button);

	button_interrupt_enable(1);
	button_interrupt_enable(2);
}

led_t timer_turn_universal_callback(led_t current_led, ccr_channels_t channel, bool led_state)
{
	set_led_state(current_led, led_state);

	if (current_led == LAST_LED)
	{
		timer_interrupt_disable(channel);
	}

	current_led = calc_next_led(current_led);
	timer_interrupt_clear(channel);

	return current_led;
}

void timer_turn_on_callback()
{
	static led_t current_led = FIRST_LED;

	current_led = timer_turn_universal_callback(current_led, ccr_turn_on, true);
}

void timer_turn_off_callback()
{
	static led_t current_led = FIRST_LED;
	
	current_led = timer_turn_universal_callback(current_led, ccr_turn_off, false);
}