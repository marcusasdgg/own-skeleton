
#include "stdio.h"

void kernel_main(){
    print("hello world!\n", TTY);
    print("Ni!\n",SERIAL);
    while (1 == 1);
}