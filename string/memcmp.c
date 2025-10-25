#include "../string.h"

int memcmp(const void *a, const void *b, size_t len) {
    const unsigned char *byte1 = a;
    const unsigned char *byte2 = b;

    for (size_t i = 0; i < len; i++) {
        if (byte1[i] != byte2[i])
            return byte1[i] - byte2[i];
    }
    return 0;
}