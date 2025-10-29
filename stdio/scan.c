#include "../stdio.h"
#include "../tty.h"
#include "../serial.h"

unsigned char get_char(int output_stream){
    if (output_stream == TTY)
        return terminal_getchar();
    if (output_stream == SERIAL)
        return serial_getchar();
    else return 0;
}
