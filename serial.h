    
#include <stdint.h>
#include <stddef.h>

#define SERIAL_COM1_BASE                0x3F8      /* COM1 base port */

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

#define SERIAL_LINE_ENABLE_DLAB         0x80

// future revamps
// allow multiple concurrent serial connections to be possible HOWEVER
// we can only use one at a time and we switch between using a switch function, i.e. keep a variable tracking current comm port in use.
// our initialize function will take in an argument that gets the requested comm port and initializes it instead of 0 by default

// in the future we will create a layer of abstraction,
// i.e. the putchar and getchar will push into an output and input stream that will
// in its own task push it into the display or something.


void serial_initialize(); // figure out prototype for it  later.
// configure initial baud rate

void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

//configure line
void serial_configure_line(unsigned short com);

void serial_configure_fifo(unsigned short com);

void serial_configure_modem(unsigned short com);

//these 2 functions work like so:
// the serial interface has an internal queue that we push in on the buffer
// get char will take the char from the queue also it should be blocking for now ig.
char serial_getchar();
// this function will probably be only called in an interrupt?.
void serial_push_input_buffer(unsigned char c);

void serial_putchar(unsigned short com, uint8_t c);

int serial_is_transmit_fifo_empty(unsigned int com);

// blocking read until we get length characters into buffer
void serial_read(unsigned short com, unsigned char* buffer, size_t len);

void serial_write(unsigned short com, const unsigned char* buffer,size_t len);




