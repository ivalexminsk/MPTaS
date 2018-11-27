
#include "driverlib.h"
#include "HAL_Cma3000.h"
#include "AJIOB_HAL_display.h"
#include "AJIOB_HAL_timer_a.h"
#include "AJIOB_HAL_buttons.h"
#include "sw_interrupts.h"
#include "device_callbacks.h"
#include "adc.h"

#include "calc_logic.h"

#include <stdio.h>

#define READY_LED_PORT  GPIO_PORT_P8
#define READY_LED_PIN   GPIO_PIN2

void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  AJIOB_HAL_display_init();
  AJIOB_HAL_buttons_init();
  AJIOB_HAL_timer_a_init();
  adc_init();
  adc_interrupt_enable();

  // board is ready
  GPIO_setAsOutputPin(READY_LED_PORT, READY_LED_PIN);
  GPIO_setOutputHighOnPin(READY_LED_PORT, READY_LED_PIN);

  clear_all(device_state_begin_NULL, inputs_NULL);
  repaint_input_mode();

  __enable_interrupt();

  while (1)
  {
    if (AJIOB_HAL_buttons_is_pressed_S1())
    {
      Button_S1_ISR();
    }

    __delay_cycles(1000);
  }
}
