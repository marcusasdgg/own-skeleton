#include "stdio.h"
#include "basic_intrinsics.h"

void kernel_main(){
    print("hello world!\n", TTY);
    while (1 == 1){
        char c = get_char(TTY);
        put_char(c,TTY);
        //_halt();
    }
}