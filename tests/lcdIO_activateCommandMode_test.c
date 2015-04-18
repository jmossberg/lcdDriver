#include <stdio.h>
#include <stdlib.h>
#include <platform.h>
#include <lcdIO.h>

int main(int argc, char **argv) {

    lcdIO_create();
    lcdIO_activateCommandMode();
    for(;;){}
    lcdIO_destroy();

    return 0; 
}
