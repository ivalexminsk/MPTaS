
#include <stdio.h>
#include "driverlib.h"
#include "HAL_Cma3000.h"
#include "AJIOB_HAL_display.h"
#include "AJIOB_HAL_timer_a.h"

void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  Cma3000_init();

  AJIOB_HAL_display_init();
  AJIOB_HAL_timer_a_init();

  __enable_interrupt();

  while (1);
  {
    Cma3000_readAccel();
    printf("X=%d\tY=%d\tZ=%d\n", Cma3000_xAccel, Cma3000_yAccel, Cma3000_zAccel);
  }
}
