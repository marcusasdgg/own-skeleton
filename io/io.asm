global in_b
global out_b

global io_wait


in_b:
    mov dx, [esp + 4]
    in  al, dx
    ret

out_b:
    mov al, [esp+8]
    mov dx, [esp+4]
    out dx, al 
    ret 

io_wait:
    push 0
    push 0x80

    call out_b
    
    add esp, 8
    ret