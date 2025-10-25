#include "../load_interrupt_table.h"

static struct idt_entry idt_table[256];

static struct idt_descriptor descriptor = {(uint16_t)256*8 - 1, (uint32_t)idt_table};

void set_idt_entry(int entrynum, struct idt_entry entry) {
    idt_table[entrynum] = entry;
}

void initialise_idt() {

    // we can definitely create a macro to do a lot for us
    struct idt_entry id_entry_0;
    id_entry_0.offset_low = (uint32_t) interrupt_handler_0;
    id_entry_0.offset_high = (uint32_t) interrupt_handler_0 >> 16;
    id_entry_0.segment_selector = 0x08;
    id_entry_0.zero = 0;
    id_entry_0.flags = 0b10001110;
    set_idt_entry(0, id_entry_0);

    struct idt_entry id_entry_33;
    id_entry_33.offset_low = (uint32_t) interrupt_handler_33;
    id_entry_33.offset_high = (uint32_t) interrupt_handler_33 >> 16;
    id_entry_33.segment_selector = 0x08;
    id_entry_33.zero = 0;
    id_entry_33.flags = 0b10001110;
    set_idt_entry(33, id_entry_33);

    load_interrupt_table(&descriptor);
}