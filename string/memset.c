#include "../string.h"
void* memset(void* dest, int sourcebyte, size_t len){
    unsigned char* dptr = dest;
    for (size_t i = 0; i < len ; i++){
        dptr[i] = (unsigned char) sourcebyte;
    }
    return dest;
}