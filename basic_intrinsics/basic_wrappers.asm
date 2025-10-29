global _cli
global _halt

global _sti

_cli:
    cli
    ret

_halt:
    hlt
    ret

_sti:
    sti 
    ret