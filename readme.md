this is a variation on the meaty skeleton 

however we will first build barebones using nasm and gcc
fuck styling and correctly foldering our code we ball for now

todo:
- write a linker script to link kernel.c and boot.asm
- write some ld commands to figure out how to link everything together
- use mbgrub rescue to create an iso

- write vga support printing strings and stuff.

- part of the gcc requirements is we hav eto provide implementations for
- memcpy
- memcmp
- memmove
- memset

also i hate shell so we are making our top level build system with python


update:

we have since implemented a lot of this stuff now we are moving on to these milestones:

interrupt support
keyboard scan support

update:
Finished basic interrupt support and keyboard scan support

new milestone:
Paging and memory allocation
user space programs