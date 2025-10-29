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

void print_int(int a, int output_stream) {
    // Skip printing if below 1 (optional based on your spec)
    if (a < 1) return;

    int copy = a;
    char array[20];
    size_t len = 0;

    // Extract digits in reverse order
    while (copy != 0) {
        char ones_digit = copy % 10;
        array[len++] = ones_digit;
        copy /= 10;
    }

    // Print digits in correct order depending on stream
    switch (output_stream) {
        case TTY:
            while (len > 0) {
                terminal_putchar('0' + array[--len]);
            }
            break;

        case SERIAL:
            while (len > 0) {
                serial_putchar(SERIAL_COM1_BASE, '0' + array[--len]);
            }
            break;

        default:
            print("Error: output stream does not exist\n", SERIAL);
            return;
    }
}

void put_char(char c, int output_stream){
    switch (output_stream) {
        case TTY:
            terminal_putchar(c);
            break;

        case SERIAL:
            serial_putchar(SERIAL_COM1_BASE,c);
            break;

        default:
            print("Error: output stream does not exist\n", SERIAL);
            return;
    }
}