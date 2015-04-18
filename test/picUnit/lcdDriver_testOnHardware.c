#include <stdio.h>
#include <stdlib.h>
#include <platform.h>
#include <lcdIO.h>
#include <lcdDriver.h>

int main(int argc, char **argv) {
    uint8_t text[10] = "CYBERCOM";

    lcdIO_create();
    lcdDriver_create();
    lcdDriver_displayString(text);

    for(;;) {}

    lcdDriver_destroy();
    lcdIO_destroy();

    return 0; 
}
