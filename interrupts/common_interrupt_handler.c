#include "../interrupts.h"
#include "../stdio.h"
void common_interrupt_handler(struct cpu_state cpu, struct stack_state stack, unsigned int interrupt){
    print("received interrupt\n", TTY);
}