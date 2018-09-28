
#include "types.h"
#include "led.h"
#include "AJIOB_regs_help.h"
#include "interrupt.h"
#include "button.h"
#include "adc_comparator.h"

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  timer_init();

  button_init(1);
  button_init(2);

  adc_init();
  comparator_init();

  for (int i = FIRST_LED; i <= LAST_LED; i++)
  {
    led_init((led_t)i);
  }

  /* Load */
  for (int i = FIRST_LED; i <= LAST_LED; i++)
  {
    set_led_state((led_t)i, true);
    arifm_delay();
  }

  for (int i = FIRST_LED; i <= LAST_LED; i++)
  {
    set_led_state((led_t)i, false);
  }
  /* Load end */

  timer_b_interrupt_enable();
  comparator_interrupt_enable();
  adc_interrupt_enable();
  __bis_SR_register(GIE + LPM0_bits);

  while(1);
}
