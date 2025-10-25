#include "../stdio.h"
#include "../tty.h"
#include "../serial.h"

void print(const char* str, int output_stream){
    size_t i = 0;
    switch(output_stream){
        case TTY:
            while (str[i] != '\0')
                terminal_putchar(str[i++]);
            break;
        case SERIAL:
            while (str[i] != '\0')
                serial_putchar(SERIAL_COM1_BASE, str[i++]);
            break;
        default:
            print("Error: output stream does not exist\n", SERIAL);
            return;
    }
}