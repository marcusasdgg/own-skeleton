
MAGIC equ 0xE85250D6
ARCH equ 0
CHECKSUM equ -(MAGIC + ARCH + 12)


section .multiboot2:
align 4
    dd MAGIC   
    dd ARCH
    dd 12
    dd CHECKSUM
