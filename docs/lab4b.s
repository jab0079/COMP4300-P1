# Hand-compliled source for lab4b.s

.text

#main:
    li $0, 0x00 # zero register always zero
    li $5, 0x02 #2
    li $f0, 0x00 #0
    li $f1, 0x0A #10
    li $f3, 0x64 #100
    li $f4, 0x3E8 #1000

#loop:
    subi $5, $5, 0x01 #1
    fadd $f0, $f0, $f1
    fadd $f0, $f0, $f3
    fadd $f0, $f0, $f4
    bge  $5, $0, 0xFFFFFFF8 #-8, three nops after
    nop
    nop 
    nop 

    li $2, 0x02 # pc points here on branch execute
    nop
    nop
    nop
    syscall # 3 nops before
    