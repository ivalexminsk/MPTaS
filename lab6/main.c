
#include <stdio.h>
#include "driverlib.h"
#include "HAL_Cma3000.h"

void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  Cma3000_init();

  printf("Hello\n");

  while (1)
  {
    Cma3000_readAccel();
    printf("X=%d\tY=%d\tZ=%d\n", Cma3000_xAccel, Cma3000_yAccel, Cma3000_zAccel);
  }
}