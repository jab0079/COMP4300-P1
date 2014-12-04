
.text

#main:
    li $1, 0x00
    li $2, 0x20

#loop:
    subi $2, $2, 1
    nop
    nop
    nop
    nop
    nop
# -7
    bge  $2, $1, 0xFFFFFFF9
#I added two nops...is that what was meant? 
    nop
    nop
    nop
#Exit
    li $2, 0x02
    syscall
