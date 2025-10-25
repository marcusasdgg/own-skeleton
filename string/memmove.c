#include "../string.h"
// this function is used if the 2 memory regions might overlap. so we copy the nonoverlapping parts first
void* memmove(void* destination, const void* source, size_t len){
    // how the fuck do we do an inplace copy ? 

    unsigned char* src = (const unsigned char*) source;
    unsigned char* dest = destination;

    // if your destination is behind your source we can copy safely without fear of missing information
    if (dest < src){
        for (size_t i = 0; i < len ; i++){
            dest[i] = src[i];
        }   
    }
    else {
        // dest is past or greater then src, so we do a backwards copy ensuring that we copy the bits of src before they get overwritten.
        for (size_t i = len; i != 0; i--)
            dest[i-1] = src[i-1];
    }
    return destination;
}