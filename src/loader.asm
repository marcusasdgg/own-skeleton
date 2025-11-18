
MAGIC equ 0xE85250D6
ARCH equ 0
CHECKSUM equ multi_boot_start - multi_boot_end


; This is the multiboot 2 header + its tags
global
section .multiboot2:
align 4
multi_boot_start:
    dd MAGIC   
    dd ARCH
    dd 12
    dd CHECKSUM
; now tags

multi_boot_end:; end of our multiboot


section .bss
    align 16
; paging stuff will be here.


stack_bottom:
    resb 16384 ; 16 KiB is reserved for stack
stack_top:



section .data
gdt_start:
	dq 0x0000000000000000 ; null decriptor
    dq 

gdt_end:
gdt_descriptor:
	dw gdt_end - gdt_start - 1 ;limit
	dd gdt_start ; base


; our entry point of where code starts execution:
; before we go into our rust run-time we want to setup some stuff
; in order, stack initalisation, paging, global descriptor table, then our rust kernel main.
section .boot.text 
bits 32
global _start:function (_start.end - _start)
_start:
   

    ; we ball screw long mode availability checks




; where our kernel actually starts before is to setup 
section .text
bits 64
    extern kernel_main
    call kernel_main