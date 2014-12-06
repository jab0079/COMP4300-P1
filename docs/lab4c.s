# Hand-compliled source for lab4c.s (DTMF loop)

.data
0x00200004:0.00  
0x00200006:1.65
0x00200008:0.80 
0x0020000A:-0.57
0x0020000C:-0.92
0x0020000F:0
0x00200011:0

.text

#main:
    li $15, 0x64       # $1: count = 100
    li $14, 0x00
    la $1, 0x00200004   # load address of 0.00
    la $2, 0x00200006   # load address of 1.65
    la $3, 0x00200008   # load address of 0.80
    la $4, 0x0020000A   # load address of -0.57
    la $5, 0x0020000C   # load address of -0.92
    ld $f0, ($1)        # $f0: 0 const register (for mem-mem fadd work around)
    ld $f1, ($2)        # $f1: kx = 1.65
    ld $f2, ($3)        # $f2: ky = 0.80
    ld $f4, ($1)        # $f4: X1 = 0.0
    ld $f5, ($4)        # $f5: X2 = -0.57
    ld $f7, ($1)        # $f7: Y1 = 0.0
    ld $f8, ($5)        # $f8: Y2 = -0.92

#loop:
    subi $15, $15, 0x01   # decrement count by 1
    
    # $f3: X0 = kx * X1 - X2
    fmul $f3, $f1, $f4  # X0 = kx * X1
    fsub $f3, $f3, $f5  # X0 = X0 - X2
    # $f6: Y0 = ky * Y1 - Y2
    fmul $f6, $f2, $f7  # Y0 = ky * Y1
    fsub $f6, $f6, $f8  # Y0 = Y0 - Y2
    
    # X2 = X1
    fadd $f5, $f0, $f4
    # X1 = X0
    fadd $f4, $f0, $f3
    # Y2 = Y1
    fadd $f8, $f0, $f7
    # Y1 = Y0
    fadd $f7, $f0, $f6
    
    # while count > 0 execute loop, 
    bge $15, $14, 0xFFFFFFF3 # otherwise branch to exit: pc -= 13
    nop
    nop 
    nop

    # store X0 & Y0: simulates tone output
#    sd $f3, 0x0020000F      # pick any (fixed) addr you like?
#    sd $f6, 0x00200011         

#exit:
    li $2, 0x02 # pc points here on branch execute
    nop
    nop
    nop
    syscall
    
    