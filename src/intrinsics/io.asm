global in_b
global out_b

out_b:
    mov dx, di
    mov al, sil
    out dx, al
    ret

in_b:
    mov dx, di
    in al, dx
    ret