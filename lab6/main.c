
#include <stdio.h>
#include "driverlib.h"
#include "HAL_Cma3000.h"
#include "AJIOB_HAL_display.h"
#include "AJIOB_HAL_timer_a.h"
#include "AJIOB_HAL_file.h"

void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  Cma3000_init();

  AJIOB_HAL_display_init();
  AJIOB_HAL_timer_a_init();
  AJIOB_HAL_init_file();

  char mytest[] = "AJIOB was here";

  bool res = AJIOB_HAL_write_file((uint8_t*)mytest, sizeof(mytest)/sizeof(mytest[0]) - 1);
  printf("Ret code: %d\n", res);

  __enable_interrupt();

  while (1);
  {
    Cma3000_readAccel();
    printf("X=%d\tY=%d\tZ=%d\n", Cma3000_xAccel, Cma3000_yAccel, Cma3000_zAccel);
  }
}
