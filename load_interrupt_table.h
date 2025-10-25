#include <stddef.h>
#include <stdint.h>
#include "interrupts.h"

struct idt_entry{
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t offset_high
}__attribute__((packed));

struct idt_descriptor{
    uint16_t limit;
    uint32_t offset
}__attribute__((packed));




void initialise_idt();
void set_idt_entry(int entrynum, struct idt_entry entry);
void load_interrupt_table(struct idt_descriptor* decr);