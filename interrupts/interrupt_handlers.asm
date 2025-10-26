    extern common_interrupt_handler
    %macro no_error_code_interrupt_handler_ 1
    global interrupt_handler_%1
    interrupt_handler_%1:
        push    dword 0                     ; push 0 as error code
        push    dword %1                    ; push the interrupt number
        jmp     extensible_interrupt_handler    ; jump to the common handler
    %endmacro

    %macro error_code_interrupt_handler_ 1
    global interrupt_handler_%1
    interrupt_handler_%1:
        push    dword %1                    ; push the interrupt number
        jmp     extensible_interrupt_handler    ; jump to the common handler
    %endmacro

    extensible_interrupt_handler:               ; the common parts of the generic interrupt handler
        push    eax
        push    ebx
        push    ecx
        push    edx
        push    ebp

        ; call the C function
        
        call    common_interrupt_handler

        ; restore the registers
        pop     ebp
        pop     edx
        pop     ecx
        pop     ebx
        pop     eax

        ; restore the esp
        add     esp, 8

        ; return to the code that got interrupted
        iret


no_error_code_interrupt_handler_ 0       ; create handler for interrupt 0
no_error_code_interrupt_handler_ 1       ; create handler for interrupt 1
error_code_interrupt_handler_    7       ; create handler for interrupt 7
no_error_code_interrupt_handler_ 33 ; create handler for 33 (keyboard)
no_error_code_interrupt_handler_ 32