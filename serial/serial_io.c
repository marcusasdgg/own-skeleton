#include "../serial.h"
#include "../io.h"

void serial_putchar(unsigned short comm, unsigned char c){
    while (!serial_is_transmit_fifo_empty(comm))
    {}
    out_b(SERIAL_DATA_PORT(comm), c);
}

char serial_getchar( unsigned short comm){
    return 'a';
}

void serial_read(unsigned short com, unsigned char* buffer, size_t len){
    for (size_t i = 0 ; i < len ;i++)
        buffer[i] = serial_getchar(com);
}

void serial_write(unsigned short com, const unsigned char* buffer,size_t len){
    for (size_t i = 0 ; i < len ;i++)
        serial_putchar(com,buffer[i]);
}
