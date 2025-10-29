#include "../interrupts.h"
#include "../stdio.h"
#include "../pic.h"
#include "../io.h"
#include "../tty.h"
#include "../keyboard.h"
void common_interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack){
    // char str[] = "received interrupt ";
    // print(str, TTY);
    // print_int(interrupt,TTY);
    // print(": ",TTY);
    
    // print(str,SERIAL);
    // print_int(interrupt, SERIAL);
    // print(": ", SERIAL);

    switch (interrupt){
        case 32:
            IRQ_set_mask(0);
            pic_sendEOI(interrupt - 32);
            print("\n",TTY);
            break;
        case 33: //glorious keyboard interrupt
            // print("scancode ", TTY);
            // print("#define", SERIAL);

            unsigned char c = in_b(0x60);
            //print_int(c,TTY);
            
            if (c <= 0x80){
                
                print_int(c,SERIAL);
                print(": \'",SERIAL);
                put_char(scanned_letter_keyboard(c), SERIAL);
                print("\'\n",SERIAL);
                tty_push_input_buffer(scanned_letter_keyboard(c));;
            }
        
            pic_sendEOI(1);
            break;
        default:
            print("Interrupt is not implemented\n", SERIAL);
            print("Interrupt is not implemented\n", TTY);
            break;
    }

    //print("\n",TTY);
    
}