#include "../pic.h"
#include "../io.h"

void disable_PIC(void) {
    out_b(PIC1_DATA, 0xff);
    out_b(PIC2_DATA, 0xff);
}