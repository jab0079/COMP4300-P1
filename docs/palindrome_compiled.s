# GPR Hand Compiled Source 

## Daniel J. Ellard -- 02/21/94
## palindrome.asm -- read a line of text and test if it is a palindrome.
##
## A palindrome is a string that is exactly the same when read backwards
## as when it is read forward (e.g. anna).
##
## Whitespace is considered significant in this version, so "ahahaha"
## is a palindrome while "aha haha" is not.
##
## Register usage:
## $8 - A - initially, the address of the first character in the string S.
## $9 - B - initially, the address of the the last character in S.
## $10 - the character at address A.
## $11 - the character at address B.
## $2 - syscall parameter / return values.
## $4 - syscall parameters.
## $5 - syscall parameters.
.data
0x00200004:00  #\0
0x00200006:89  #Y
0x00200007:00  #\0
0x00200008:78  #N
0x00200009:00  #\0

.text
#main:
	# read the string S:
	la $4, 0x00200100
	li $5, 0x400		# 1024
	li $2, 0x1		# load "read_string" code into $2.
	syscall

	la $8, 0x00200100	# A = S.
	la $9, 0x00200100	# we need to move B to the end

#length_loop:			# length of the string
	lb $10, ($9)		# load the byte at addr B into $10.
	beqz $10, 0x2           # if $10 == 0, branch out of loop.

	addi $9, $9, 0x1	# otherwise, increment B,
	b 0xFFFFFFFC		# and repeat the loop.

#end_length_loop:
	subi $9, $9, 0x1	# subtract 2 to move B back past the '\0' and '\n'.

#test_loop:
	bge $8, $9, 0x06	# if A >= B, it's a palindrome.

	lb $10, ($8)		# load the byte at addr A into $10,
	lb $11, ($9)		# load the byte at addr B into $11.
	bne $10, $11, 0x07	# if $10 != $11, not a palindrome.

	# Otherwise,
	addi $8, $8, 0x1	# increment A,
	subi $9, $9, 1		# decrement B,
	b 0xFFFFFFF9		# and repeat the loop.

#is_palin:			# print the is_palin_msg, and exit.

	la $4, 0x00200006
	li $2, 0x00
	syscall
	b 0x4

#not_palin:
	la $4, 0x00200008	# print the not_palin_msg, and exit.
	li $2, 0x00
	syscall
	b 0x00

#exit:				# exit the program
	li $2, 0x02		# load "exit" code into $2.
	syscall			# make the system call.
