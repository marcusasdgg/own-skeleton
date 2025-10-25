global load_interrupt_table


load_interrupt_table:
    mov eax, [esp+4]
    lidt [eax]
    ret