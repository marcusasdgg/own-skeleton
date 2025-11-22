%include 

MAGIC equ 0xE85250D6
ARCH equ 0
CHECKSUM equ multi_boot_start - multi_boot_end
INTIAL_PAGE_TABLE_SIZE equ INITIAL_TABLES_END - PML4_TABLE

PT_ADDR_MASK equ 0xffffffffff000
PT_PRESENT equ 1                 ; marks the entry as in use
PT_READABLE equ 2   
PT_BIG equ 1 << 8

CR4_PAE_ENABLE equ 1 << 5


; This is the multiboot 2 header + its tags
section .multiboot2:
align 4
multi_boot_start:
    dd MAGIC   
    dd ARCH
    dd 12
    dd CHECKSUM
address_tag_start:      
        dw MULTIBOOT_HEADER_TAG_ADDRESS
        dw MULTIBOOT_HEADER_TAG_OPTIONAL
        dq address_tag_end - address_tag_start
        dq   multiboot_header
        dq   _start
        dq   _edata
        dq   _end
address_tag_end:
entry_address_tag_start:        
        dw MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS
        dw MULTIBOOT_HEADER_TAG_OPTIONAL
        dq entry_address_tag_end - entry_address_tag_start
        dq multiboot_entry
entry_address_tag_end:
framebuffer_tag_start:  
        dw MULTIBOOT_HEADER_TAG_FRAMEBUFFER
        dw MULTIBOOT_HEADER_TAG_OPTIONAL
        dq framebuffer_tag_end - framebuffer_tag_start
        dq 1024
        dq 768
        dq 32
framebuffer_tag_end:
        dw MULTIBOOT_HEADER_TAG_END
        dw 0
        dq 8
multiboot_header_end:
; now tags we need to tell GRUB to give us a standard framebuffer

multi_boot_end:; end of our multiboot


section .bss
    align 16
;initial paging stuff will be here. so table pml4, pml3 coresponding to pml4 and pml2 corresponding to pml3
; pml4 table with 512 entries of 8 bytes
.paging:
global PML4_TABLE ; make this accessible everywhere
global Initial_PML3_TABLE
global Initial_PML2_TABLE

PML4_TABLE:
    resb 4096
Initial_PML3_TABLE: 
    resb 4096
Initial_PML2_TABLE:
    resb 4096
INITIAL_TABLES_END:
    

stack_bottom:
    resb 16384 ; 16 KiB is reserved for stack
stack_top:



section .data
; whee this is our 64 bit gdt, I don't think we need to setup the 32 bit one just do this in long mode.
; Access bits
gdt:



; our entry point of where code starts execution: GRUB sets us up in 32 bit protected
; before we jump into long mode we need to setup paging and PAE.
section .boot.text 
bits 32
global _start:function (_start.end - _start)
_start:

    ; link reg cr3 to our base page table
    mov edi, PML4_TABLE
        


    xor eax, eax
    mov ecx, INTIAL_PAGE_TABLE_SIZE ; 
    ; zero out our 3 page tables first.
    ; this fucking sucks, rep is a prefix that repeats the instruction ecx times, 
    ; stosd stores word in eax to address edi and increments edi
    rep stosd
    
    mov edi, PML4_TABLE
    mov cr3, edi   

    ; we now link the tables together pml4[0] pointing to pml3 initial
    mov eax, Initial_PML3_TABLE
    and eax, PT_ADDR_MASK
    or eax, PT_PRESENT
    or eax, PT_READABLE
    mov DWORD [edi], eax

    ; pml3 inital pointing to pml2
    mov edi, Initial_PML3_TABLE
    mov eax, Initial_PML2_TABLE
    and eax, PT_ADDR_MASK
    or eax, PT_PRESENT
    or eax, PT_READABLE
    mov DWORD [edi], eax
    
    ; now we configure the first entry of pml2 table
    mov edi, Initial_PML2_TABLE
    mov DWORD [edi], 0 | PT_BIG | PT_PRESENT | PT_READABLE

    ; after all of this we have mapped with first 2 mb of phyiscal address space is mapped to virtual address space we can do more later.
    
    ; enable PAE now we can set LME
    mov eax, cr4
    or eax, CR4_PAE_ENABLE
    mov cr4, eax

    ; Long Mode Enable
    mov ecx, 0xC0000080
    rdmsr
    or  eax, (1 << 8)
    wrmsr

    ; enable paging and protected mode
    or ebx, (1 << 31) | (1 << 0)
    mov cr0, ebx

    mov ax, 0x08
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    jmp 0x08:_start_real
.end:

; where our kernel actually starts in 64 bit
; setup interrupt tables, gdt here, apparently the PIC we used is not applicable in long mode research APIC.
section .text
bits 64
_start_real:
    hlt   ; Done. Replace these lines with your own code
    jmp _start_real