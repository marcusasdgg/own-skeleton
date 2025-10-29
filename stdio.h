#include <stddef.h>
#include <stdint.h>
// our weird version of stdio so far only including 2 functions 
// scan and print.

enum stream {
    TTY = 0,
    SERIAL = 1,
};

// prints null terminated string to given enum output stream.
void print(const char* str, int output_stream);

void print_int(int, int output_stream);

void put_char(const char, int output_stream);

unsigned char get_char(int output_stream);


// scans buffer from input stream.
void scan(uint8_t* buffer, size_t length, int output_stream);