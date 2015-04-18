#include <lcdIO.h>
#include <platform.h>

// helper macros
#define testbit(var, bit) ((var) & (1 <<(bit)))
#define setbit(var, bit) ((var) |= (1 << (bit)))
#define clrbit(var, bit) ((var) &= ~(1 << (bit))) 

//lcdIO data
static uint8_t lcdDataBits;
static uint8_t portcRegister;

static void lcdIO_waitForButton()
{
  static uint16_t downCounter = 0;
  static uint16_t upCounter = 0;
  static uint8_t buttonState = 1; // up
  static uint8_t buttonReady = 0;

  while(0 == buttonReady)
  {
    if(testbit(PORTA, 3)) //input sensor says button position is up
    {
      downCounter = 0;
      if(0 == buttonState)  //but button state is down
      {
        upCounter++;
        if(upCounter>200)
        {
          buttonState = 1; // new button state is up
          buttonReady = 1;
          upCounter = 0;
          //PORTC = 3;
        }
      }
    }
    else //input sensor says button position is down
    {
     upCounter = 0;
     if(1 == buttonState) // but button state is up
     {
       downCounter++;
       if(downCounter>200)
       {
         buttonState = 0; // new button state is down
         downCounter = 0;
         //PORTC = 1;
       }
     }
    }
  }

  buttonReady = 0;
}

void lcdIO_create()
{

  //Pin RS - Register Select
  //Pin E - Enable
  //Pin D4 - Data bit 4
  //Pin D5 - Data bit 5
  //Pin D6 - Data bit 6
  //Pin D7 - Data bit 7

  //RA0 - Variable resistance
  //RA3 - Switch
  //RC0 - J1_10 - Diode 1 - Data bit 4
  //RC1 - J1_11 - Diode 2 - Data bit 5
  //RC2 - J1_12 - Diode 3 - Data bit 6
  //RC3 - J1_6 - Diode 4 - Data bit 7
  //RC4 - J1_5 - Pin RS
  //RC5 - J1_4 - Pin E


  TRISC = 0; //Set PORTC to outputs
  PORTC = 0;

  PORTA = 0;
  ANSEL = 0;
  TRISA = 0xFF; //Set PORTA to inputs

  lcdDataBits = 0;
  portcRegister = 0;

  __delay_ms(50);
}

void lcdIO_destroy()
{
  lcdDataBits = 0;
}

void lcdIO_activateWriteMode()
{
}

void lcdIO_activateCommandMode()
{
  clrbit(portcRegister, 4); 
//  PORTC = portcRegister; //Set command mode, i.e. RC4 low
  RC4 = 0;
}

void lcdIO_activateCharacterMode()
{
  setbit(portcRegister, 4); 
//  PORTC = portcRegister; //Set command mode, i.e. RC4 high
  RC4 = 1;
}

void lcdIO_setEnableHigh()
{
  setbit(portcRegister, 5); 
//  PORTC = portcRegister;
  RC5 = 1;
}

void lcdIO_setEnableLow()
{
  clrbit(portcRegister, 5); 
//  PORTC = portcRegister;
  RC5 = 0;
}

void lcdIO_setDS1High()
{
  setbit(portcRegister, 0); 
  PORTC = portcRegister;
}

void lcdIO_setDS1Low()
{
  clrbit(portcRegister, 0); 
  PORTC = portcRegister;
}

void lcdIO_waitForEnableToRegisterInLcd()
{
    __delay_ms(4000);
}

void lcdIO_delayMicroSeconds(uint8_t microSeconds)
{
#if DEBUG_LCD_IO == 1
  lcdIO_waitForButton();
#else
  uint8_t i;
  for(i = 0; i<microSeconds; i++)
  {
    __delay_us(1);
  }
#endif
}


void lcdIO_setDataBits(uint8_t * lcdDataBits_p)
{
//Bit number 0 to 3 from *lcdDataBits_p shall be sent to display. Bit 4 to 7 shall be ignored.
  //portcRegister = (portcRegister | 0xF0) | (*lcdDataBits_p | 0x0F);
  portcRegister = (portcRegister & 0xF0) | ((*lcdDataBits_p >> 4) & 0x0F);
  PORTC = portcRegister;
}
