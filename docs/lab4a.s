
.text

#main:
    li $1, 0x00
    li $2, 0x20

#loop:
    subi $2, $2, 0x01
    nop
    nop
    nop
    nop
    nop
    bge  $2, $1, 0xFFFFFFF6 # -10
    nop
    nop
    nop
#Exit
    li $2, 0x02
    nop
    nop
    nop
    syscall
