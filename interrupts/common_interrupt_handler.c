#include "../interrupts.h"
#include "../stdio.h"
#include "../pic.h"
void common_interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack){
    char str[] = "received interrupt ";
    print(str, TTY);
    print_int(interrupt,TTY);
    print("\n",TTY);
    
    print(str,SERIAL);
    print_int(interrupt, SERIAL);
    print("\n", SERIAL);

    pic_sendEOI(interrupt - 32);
    IRQ_set_mask(0);
}