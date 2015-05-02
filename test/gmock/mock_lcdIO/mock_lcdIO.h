#ifndef MOCK_LCDIO_H
#define MOCK_LCDIO_H
#include <lcdIO.h>
#include <stdint.h>

#define MAX_EXPECTED_LCD_COMMANDS 16

enum lcd_states_t
{
READY_FOR_COMMAND_MODE_CHANGE,
DELAY_1_US_NEEDED_1,
READY_FOR_ENABLE_HIGH_1,
DELAY_1_US_NEEDED_2,
READY_FOR_ENABLE_LOW_1,
DELAY_100_US_NEEDED_1
};

uint8_t mock_lcdIO_getCountActivateRead();
uint8_t mock_lcdIO_getCountActivateCommandMode();
uint8_t mock_lcdIO_getCountSetDataBits();
uint8_t mock_lcdIO_updatedDataBits();
void mock_lcdIO_addExpectedLcdCommand(uint8_t newExpectedLcdCommand, uint8_t lcdInputType);
uint8_t mock_lcdIO_lcdCommandsEqualExpected();

#endif
