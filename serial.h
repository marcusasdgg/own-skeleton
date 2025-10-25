    
#include <stdint.h>
#include <stddef.h>

#define SERIAL_COM1_BASE                0x3F8      /* COM1 base port */

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

#define SERIAL_LINE_ENABLE_DLAB         0x80


void serial_initialize(); // figure out prototype for it  later.
// configure initial baud rate

void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

//configure line
void serial_configure_line(unsigned short com);

void serial_configure_fifo(unsigned short com);

void serial_configure_modem(unsigned short com);

char serial_getchar(unsigned short com);

void serial_putchar(unsigned short com, uint8_t c);

int serial_is_transmit_fifo_empty(unsigned int com);

// blocking read until we get length characters into buffer
void serial_read(unsigned short com, unsigned char* buffer, size_t len);

void serial_write(unsigned short com, const unsigned char* buffer,size_t len);


