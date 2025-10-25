#include <stddef.h>

void out_b(unsigned short port, unsigned char data);
unsigned char in_b(unsigned short port);

//this just sends some random ass data to a unused port, i.e. an effective nop.
void io_wait();