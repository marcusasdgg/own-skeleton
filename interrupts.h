struct cpu_state {
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
    unsigned int esp;
} __attribute__((packed));

struct stack_state {
    unsigned int error_code;
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
} __attribute__((packed));

// this is the global interrupt handler which is called by every interrupt
void common_interrupt_handler(struct cpu_state cpu, struct stack_state stack, unsigned int interrupt);

// each of these is defined by a macro in interrupt_handlers.asm i.e. these are just the stubs of all 255 interrupt handlers 
// these interrupt handlers are just a syntatic sugar which calls the common interrupt handler.

void interrupt_handler_0();
void interrupt_handler_1();
void interrupt_handler_7();
void interrupt_handler_33(); // our special little keyboard interrupt
