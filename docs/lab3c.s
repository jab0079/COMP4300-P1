# lab3c.s Hand Compiled Source

.text

#main:	
	li $1, 0x00
	li $2, 0x10
	li $3, 0x100
	li $4, 0x1000
	li $5, 0x7

#loop:
	subi $5, $5, 0x01
	add $1, $1, $2
	add $1, $1, $3
	add $1, $1, $4
	bge  $5, $0, 0xFFFFFFFA         #go back to loop
	nop

	add $4, $0, $1
	li $2, 0x01
	syscall

	li $2, 0x10
	syscall
	