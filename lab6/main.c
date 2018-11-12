
#include <stdio.h>
#include "driverlib.h"
#include "HAL_Cma3000.h"
#include "AJIOB_HAL_display.h"
#include "AJIOB_HAL_timer_a.h"
#include "AJIOB_HAL_file.h"

FRESULT GetDirectory(char* directoryName);

void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  Cma3000_init();

  AJIOB_HAL_display_init();
  AJIOB_HAL_timer_a_init();
  AJIOB_HAL_init_file();

  char mytest[] = "AJIOB was here";

  int r1 = GetDirectory("");
  printf("Ret code 1: %d\n", r1);

  int res = WriteFile(HAL_FILE_NAME, mytest, sizeof(mytest)/sizeof(mytest[0]) - 1);
  printf("Ret code: %d\n", res);

  int res2 = GetFile(HAL_FILE_NAME);
  printf("Ret code get: %d\n", res2);

  __enable_interrupt();

  while (1);
  {
    Cma3000_readAccel();
    printf("X=%d\tY=%d\tZ=%d\n", Cma3000_xAccel, Cma3000_yAccel, Cma3000_zAccel);
  }
}
