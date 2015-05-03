#include <lcdIO.h>


/* STM32 <--> LCD Pin connections
/
/  PORT | Bit | Extension board | LCD Pin
/  -----|-----|-----------------|---------------------
/  C    | 0   | EXT1-19         | Data bit 4
/  C    | 1   | EXT1-20         | Data bit 5
/  C    | 2   | EXT2-2          | Data bit 6
/  C    | 3   | EXT2-9          | Data bit 7
/  C    | 4   | EXT2-12         | RS (Register Select)
/  C    | 5   | EXT2-13         | E (Enable)   

void lcdIO_activateCommandMode()
{
  setPortC(4, LOW);
}
