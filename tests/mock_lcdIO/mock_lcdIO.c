#include <mock_lcdIO.h>

//lcdIO data
static uint8_t lcdDataBits;

typedef struct lcdCommandListType
{
  uint8_t dataBits;
  uint8_t inputType;
} lcdCommandSType;

//mock lcdIO data
static uint8_t countActivateRead;
static uint8_t countActivateCommandMode;
static uint8_t activeInputMode;
static uint8_t countExpectedLcdCommands;
static uint8_t countActualLcdCommands;
static uint8_t countSetDataBits;
static uint8_t callsInWrongOrderError;
static lcdCommandSType expectedLcdCommandsS[MAX_EXPECTED_LCD_COMMANDS];
static lcdCommandSType actualLcdCommandsS[MAX_EXPECTED_LCD_COMMANDS];

const uint8_t COMMAND_MODE = 1;
const uint8_t CHARACTER_MODE = 2;

static enum lcd_states_t lcdState;

//lcdIO functions
void lcdIO_create()
{
  //init lcdIO data
  lcdDataBits = 0;

  //init mock lcdIO data
  countActivateRead = 0;
  countActivateCommandMode = 0;
  countExpectedLcdCommands = 0;
  countActualLcdCommands = 0;
  countSetDataBits = 0;
  activeInputMode = 0;
  lcdState = READY_FOR_COMMAND_MODE_CHANGE;
  callsInWrongOrderError = 0;

  uint8_t i = 0;

  for (i = 0; i < MAX_EXPECTED_LCD_COMMANDS; i++)
  {
    expectedLcdCommandsS[i].dataBits = 0;
    expectedLcdCommandsS[i].inputType = 0;

    actualLcdCommandsS[i].dataBits = 0;
    actualLcdCommandsS[i].inputType = 0;
  }
}

void lcdIO_destroy()
{
  lcdIO_create();
}

void lcdIO_activateWriteMode()
{
  countActivateRead++;
}

void lcdIO_activateCommandMode()
{
  activeInputMode = COMMAND_MODE;
  countActivateCommandMode++;
  if(READY_FOR_COMMAND_MODE_CHANGE == lcdState)
  {
    lcdState = DELAY_1_US_NEEDED_1;
  }
  else
  {
    callsInWrongOrderError = 1; 
  }
}

void lcdIO_activateCharacterMode()
{
  activeInputMode = CHARACTER_MODE;
  if(READY_FOR_COMMAND_MODE_CHANGE == lcdState)
  {
    lcdState = DELAY_1_US_NEEDED_1;
  }
  else
  {
    callsInWrongOrderError = 1; 
  }
}

void lcdIO_setDataBits(uint8_t * lcdDataBits_p)
{
  countSetDataBits++;
  lcdDataBits = *lcdDataBits_p;

  if(!(READY_FOR_COMMAND_MODE_CHANGE == lcdState ||
     DELAY_1_US_NEEDED_1 == lcdState ||
     READY_FOR_ENABLE_HIGH_1 == lcdState))
  {
    callsInWrongOrderError = 1;
  }
}

void lcdIO_setEnableHigh()
{
  actualLcdCommandsS[countActualLcdCommands].dataBits = lcdDataBits;
  actualLcdCommandsS[countActualLcdCommands].inputType = activeInputMode;

  if(READY_FOR_ENABLE_HIGH_1 == lcdState ||
     READY_FOR_COMMAND_MODE_CHANGE == lcdState)
  {
    lcdState = DELAY_1_US_NEEDED_2;
  }
  else
  {
    callsInWrongOrderError = 1; 
  }
}

void lcdIO_setEnableLow()
{
  countActualLcdCommands++;
  if(READY_FOR_ENABLE_LOW_1 == lcdState)
  {
    lcdState = DELAY_100_US_NEEDED_1;
  }
  else
  {
    callsInWrongOrderError = 1; 
  }
}

void lcdIO_delayMicroSeconds(uint8_t microSeconds)
{
  if(DELAY_1_US_NEEDED_1 == lcdState && microSeconds >= 1)
  {

    lcdState = READY_FOR_ENABLE_HIGH_1;
  }
  else if(DELAY_1_US_NEEDED_2 == lcdState &&
    microSeconds >= 1)
  {
    lcdState = READY_FOR_ENABLE_LOW_1;
  }
  else if(DELAY_100_US_NEEDED_1 == lcdState &&
    microSeconds >= 100)
  {
    lcdState = READY_FOR_COMMAND_MODE_CHANGE;
  }
  else
  {
    callsInWrongOrderError = 1; 
  }

}

//mock lcdIO functions
uint8_t mock_lcdIO_getCountActivateRead()
{
  return countActivateRead;
}

uint8_t mock_lcdIO_getCountActivateCommandMode()
{
  return countActivateCommandMode;
}

uint8_t mock_lcdIO_getCountSetDataBits()
{
  return countSetDataBits;
}

uint8_t mock_lcdIO_updatedDataBits()
{
  if (0 == lcdDataBits)
  {
    return 0; //lcd data bits has not been updated 
  }

  return 1; //lcd data bits has been updated
}

void mock_lcdIO_addExpectedLcdCommand(uint8_t newExpectedLcdDataBits, uint8_t lcdInputType)
{
  expectedLcdCommandsS[countExpectedLcdCommands].dataBits = newExpectedLcdDataBits;
  expectedLcdCommandsS[countExpectedLcdCommands].inputType = lcdInputType;
  countExpectedLcdCommands++;
}

uint8_t mock_lcdIO_lcdCommandsEqualExpected()
{
  uint8_t i = 0;

  if(1 == callsInWrongOrderError)
  {
    return 0; //enable high, wait and enable low was not called in correct order after set bits
  }

  for(i = 0; i < countExpectedLcdCommands; i++)
  {
    if(expectedLcdCommandsS[i].dataBits != actualLcdCommandsS[i].dataBits)
    {
      return 0; //expected lcd commands not equal to actual commands
    }

    if(expectedLcdCommandsS[i].inputType != actualLcdCommandsS[i].inputType)
    {
      return 0; //expected lcd commands not equal to actual commands
    }

  }

  return 1; //expected lcd commands equal to actual commands
}
