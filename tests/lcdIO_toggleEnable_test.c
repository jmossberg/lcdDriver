#include <stdio.h>
#include <stdlib.h>
#include <platform.h>
#include <lcdIO.h>

static void delay4seconds()
{
  uint16_t i;
  for(i = 0; i<20000; i++)
  {
    lcdIO_delayMicroSeconds(100);
  }
}

int main(int argc, char **argv) {

    lcdIO_create();

    while(1)
    {
      lcdIO_delayMicroSeconds(100);
    //  lcdIO_setEnableHigh();
    //  delay4seconds();
    //  lcdIO_setEnableLow();
    //  delay4seconds();
    }
    lcdIO_destroy();

    return 0; 
}
