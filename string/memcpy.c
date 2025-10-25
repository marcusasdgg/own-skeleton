#include "../string.h"
void* memcpy(void* restrict a, const void* restrict b, size_t len){
    unsigned char* dst = (unsigned char*) a;
    unsigned char* src = (const unsigned char*) b;

    for (size_t i = 0; i < len ; i++){
        dst[i] = src[i];
    }
    return a;
}