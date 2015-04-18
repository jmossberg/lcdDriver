#include <stdio.h>
#include <stdlib.h>
#include <picUnit.h>
#include <platform.h> //platform specific includes
#include <lcdDriver.h>
#include <mock_lcdIO.h>

uint8_t foo = 7;
uint8_t bar = 4;

static uint8_t test_foo() {
    picUnit_assert(foo == 7);
    return 0;
}

static uint8_t test_bar() {
    picUnit_assert(bar == 4);
    return 0;
}

static uint8_t test_foobar() {
    picUnit_assert(foo > bar);
    return 0;
}

static uint8_t testlcdDriverCreateAndDestroy() {
    picUnit_assert(0 == lcdDriver_create());
    picUnit_assert(0 == lcdDriver_destroy());
    return 0;
}

static uint8_t testlcdDriver_displayCharacter_activateCommandMode() {
    uint8_t test_character = 'A';

    lcdIO_create();
 
    //check via fake lcdIO if expectations are fulfilled 
    picUnit_assert(0 == lcdDriver_create());
    picUnit_assert(0 == lcdDriver_displayCharacter(&test_character));
    picUnit_assert(0 == lcdDriver_destroy());

    picUnit_assert(1 == mock_lcdIO_getCountActivateCommandMode());
    lcdIO_destroy();

    return 0;
}


static uint8_t testLcdDriver_displayCharacter_activate4BitMode() {
    uint8_t test_character = 'A';

    lcdIO_create();

    //set expectations
    //expect lcd data bits to set lcd to 4 bit mode
    //that is code 0x20 (0b00100000)
    mock_lcdIO_addExpectedLcdCommand(0x20, COMMAND_MODE);
 
    //check via fake lcdIO if expectations are fulfilled 
    picUnit_assert(0 == lcdDriver_create());
    picUnit_assert(0 == lcdDriver_displayCharacter(&test_character));
    picUnit_assert(0 == lcdDriver_destroy());

    picUnit_assert(mock_lcdIO_lcdCommandsEqualExpected());

    lcdIO_destroy();

    return 0; 
}

static uint8_t testLcdDriver_displayCharacter_clearDisplay() {
    uint8_t test_character = 'A';

    lcdIO_create();

    //set expectations
    //expect lcd data bits to set lcd to 4 bit mode
    //that is code 0x20 (0b00100000)
    mock_lcdIO_addExpectedLcdCommand(0x20, COMMAND_MODE);
    //expect lcd clear, that is code 0x01
    mock_lcdIO_addExpectedLcdCommand(0x00, COMMAND_MODE); // first nibble
    mock_lcdIO_addExpectedLcdCommand(0x10, COMMAND_MODE); // second nibble
 
    //check via fake lcdIO if expectations are fulfilled 
    picUnit_assert(0 == lcdDriver_create());
    picUnit_assert(0 == lcdDriver_displayCharacter(&test_character));
    picUnit_assert(0 == lcdDriver_destroy());

    picUnit_assert(mock_lcdIO_lcdCommandsEqualExpected());

    lcdIO_destroy();

    return 0; 
}

static uint8_t testLcdDriver_displayCharacter_turnDisplayOn() {
    uint8_t test_character = 'A';

    lcdIO_create();

    //set expectations
    //expect lcd data bits to set lcd to 4 bit mode
    //that is code 0x20 (0b00100000)
    mock_lcdIO_addExpectedLcdCommand(0x20, COMMAND_MODE);
    //expect lcd clear, that is code 0x01
    mock_lcdIO_addExpectedLcdCommand(0x00, COMMAND_MODE); // first nibble
    mock_lcdIO_addExpectedLcdCommand(0x10, COMMAND_MODE); // second nibble
    //expect lcd display on, that is code 0x0f
    mock_lcdIO_addExpectedLcdCommand(0x00, COMMAND_MODE); // first nibble
    mock_lcdIO_addExpectedLcdCommand(0xf0, COMMAND_MODE); // second nibble
 
    //check via fake lcdIO if expectations are fulfilled 
    picUnit_assert(0 == lcdDriver_create());
    picUnit_assert(0 == lcdDriver_displayCharacter(&test_character));
    picUnit_assert(0 == lcdDriver_destroy());

    picUnit_assert(mock_lcdIO_lcdCommandsEqualExpected());

    lcdIO_destroy();

    return 0; 
}

static uint8_t testLcdDriver_displayCharacter_requestCharacterA() {
    uint8_t test_character = 'A';

    lcdIO_create();

    //set expectations
    //expect lcd data bits to set lcd to 4 bit mode
    //that is code 0x20 (0b00100000)
    mock_lcdIO_addExpectedLcdCommand(0x20, COMMAND_MODE);
    //expect lcd clear, that is code 0x01
    mock_lcdIO_addExpectedLcdCommand(0x00, COMMAND_MODE); // first nibble
    mock_lcdIO_addExpectedLcdCommand(0x10, COMMAND_MODE); // second nibble
    //expect lcd display on, that is code 0x0f
    mock_lcdIO_addExpectedLcdCommand(0x00, COMMAND_MODE); // first nibble
    mock_lcdIO_addExpectedLcdCommand(0xf0, COMMAND_MODE); // second nibble
    //expect lcd to receive character A, that is code 0x41
    mock_lcdIO_addExpectedLcdCommand(0x40, CHARACTER_MODE); // first nibble
    mock_lcdIO_addExpectedLcdCommand(0x10, CHARACTER_MODE); // second nibble
 
    //check via fake lcdIO if expectations are fulfilled 
    picUnit_assert(0 == lcdDriver_create());
    picUnit_assert(0 == lcdDriver_displayCharacter(&test_character));
    picUnit_assert(0 == lcdDriver_destroy());

    picUnit_assert(mock_lcdIO_lcdCommandsEqualExpected());

    lcdIO_destroy();

    return 0; 
}

static uint8_t testlcdDriver_displayCharacter_setDataBits() {
    uint8_t test_character = 'A';

    lcdIO_create();
 
    //check via fake lcdIO if expectations are fulfilled 
    picUnit_assert(0 == lcdDriver_create());
    picUnit_assert(0 == lcdDriver_displayCharacter(&test_character));
    picUnit_assert(0 == lcdDriver_destroy());

    picUnit_assert(7 == mock_lcdIO_getCountSetDataBits());

    lcdIO_destroy();

    return 0;
}


static uint8_t all_tests(uint8_t * tests_run_p, uint8_t test_results[]) {
    picUnit_run_test(test_foo, tests_run_p, test_results);
    picUnit_run_test(test_bar, tests_run_p, test_results);
    picUnit_run_test(test_foobar, tests_run_p, test_results);
    picUnit_run_test(testlcdDriverCreateAndDestroy, tests_run_p, test_results);
    picUnit_run_test(testlcdDriver_displayCharacter_activateCommandMode, tests_run_p, test_results);
    picUnit_run_test(testLcdDriver_displayCharacter_activate4BitMode, tests_run_p, test_results);
    picUnit_run_test(testLcdDriver_displayCharacter_clearDisplay, tests_run_p, test_results);
    picUnit_run_test(testLcdDriver_displayCharacter_turnDisplayOn, tests_run_p, test_results);
    picUnit_run_test(testLcdDriver_displayCharacter_requestCharacterA, tests_run_p, test_results);
    picUnit_run_test(testlcdDriver_displayCharacter_setDataBits, tests_run_p, test_results);
    return 0;
}

int main(int argc, char **argv) {
    uint8_t tests_run = 0;
    uint8_t test_results[(MAX_NUM_OF_TESTS / 8)] = {0, 0, 0, 0, 0, 0, 0, 0};

    all_tests(&tests_run, test_results);
    //the next line probable does not work because the pointers are not valid in the eeprom driver
    picUnit_writeTestResultsToNonVolatileMemory(&tests_run, test_results);

    return 0;
}
