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

    uint8_t lcdDataBits1 = 0x50;
    uint8_t lcdDataBits2 = 0xA0;

    lcdIO_create();

    while(1)
    {
      lcdIO_setEnableHigh();
      lcdIO_setDataBits(&lcdDataBits1);
      //delay4seconds();
      lcdIO_delayMicroSeconds(100);
      lcdIO_setEnableLow();
      lcdIO_setDataBits(&lcdDataBits2);
      //delay4seconds();
      lcdIO_delayMicroSeconds(100);
    }
    lcdIO_destroy();

    return 0; 
}
