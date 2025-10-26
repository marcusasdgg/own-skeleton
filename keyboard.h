#include <stddef.h>
#include <stdint.h>

// this file is our keyboard driver 
#define KBD_DATA_PORT   0x60

// we need some map of the scan codes to the assigned character
// ignore modifier and special keys for now ig.

// all of the definitions will also be here for funsys
#define RELEASE_KEY(base) (base + 0x128)

#define 

unsigned char scanned_letter_keyboard(unsigned char byte);

