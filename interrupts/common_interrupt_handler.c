#include "../interrupts.h"
#include "../stdio.h"
#include "../pic.h"
#include "../io.h"
void common_interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack){
    char str[] = "received interrupt ";
    print(str, TTY);
    print_int(interrupt,TTY);
    print(": ",TTY);
    
    // print(str,SERIAL);
    // print_int(interrupt, SERIAL);
    // print(": ", SERIAL);

    switch (interrupt){
        case 32:
            pic_sendEOI(interrupt - 32);
            break;
        case 33: //glorious keyboard interrupt
            print("scancode ", TTY);
            //print("#define", SERIAL);

            unsigned char c = in_b(0x60);
            print_int(c,TTY);
            if (c <= 0x80){
                print("\n",SERIAL);
                print_int(c,SERIAL);
            }
                
            pic_sendEOI(1);
            break;
        default:
            print("Interrupt is not implemented\n", SERIAL);
            print("Interrupt is not implemented\n", TTY);
            break;
    }

    print("\n",TTY);
    IRQ_set_mask(0);
}