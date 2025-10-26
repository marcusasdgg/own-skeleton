#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);

// same as serial getchar reads from a queue and tty_push_buffer pushes into queue, 2nd function is callec
// from interrupt.
char terminal_getchar();
void tty_push_intput_buffer(unsigned char c);
char* terminal_read(size_t size);



#endif
