#include "../pic.h"
#include "../io.h"
#define PIC1_PORT_A 0x20
#define PIC2_PORT_A 0xA0

/* The PIC interrupts have been remapped */
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT   PIC2_START_INTERRUPT + 7

#define PIC_ACK     0x20
void pic_sendEOI(uint8_t irq){

    if (irq < 15) {
        out_b(PIC1_PORT_A, PIC_ACK);
    } else {
        out_b(PIC2_PORT_A, PIC_ACK);
    }
}