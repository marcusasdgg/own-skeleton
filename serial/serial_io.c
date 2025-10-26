#include "../serial.h"
#include "../io.h"
#include "../circular_queue.h"

// output buffer is unused so far.
static struct Queue inputBuffer;
static struct Queue outputBuffer;

void serial_initialize(){
    serial_configure_baud_rate(SERIAL_COM1_BASE,1);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_configure_fifo(SERIAL_COM1_BASE);
    initialise_Queue(&inputBuffer);
	initialise_Queue(&outputBuffer);
}

void serial_putchar(unsigned short comm, unsigned char c){
    while (!serial_is_transmit_fifo_empty(comm))
    {}
    out_b(SERIAL_DATA_PORT(comm), c);
}

char serial_getchar(){
    while (isempty_Queue(&inputBuffer)){}
	return pop_Queue(&inputBuffer); 
}

void serial_push_input_buffer(unsigned char c){
    emplace_Queue(&inputBuffer, c);
}

void serial_read(unsigned short com, unsigned char* buffer, size_t len){
    for (size_t i = 0 ; i < len ;i++)
        buffer[i] = serial_getchar(com);
}

void serial_write(unsigned short com, const unsigned char* buffer,size_t len){
    for (size_t i = 0 ; i < len ;i++)
        serial_putchar(com,buffer[i]);
}
