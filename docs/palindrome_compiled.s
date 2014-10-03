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
## $0 - A - initially, the address of the first character in the string S.
## $1 - B - initially, the address of the the last character in S.
## $2 - the character at address A.
## $3 - the character at address B.
## $31 - syscall parameter / return values.
## $30 - syscall parameters.
## $29 - syscall parameters.
.data
0x00200000:65  #A
0x00200001:66  #B
0x00200002:66  #B
0x00200003:65  #A
0x00200004:00  #\0
0x00200005:10  #\n
0x00200006:89  #Y
0x00200007:78  #N

.text
  #main:
	
  # read the string S:
	la $30, 0x00200100
	li $29, 0x400               # 1024
	li $31, 0x8	                # load "read_string" code into $31.
	syscall

	la $0, 0x00200100	          # A = S.
	la $1, 0x00200100	          # we need to move B to the end

#length_loop:			            # length of the string
	lb $2, ($3)		              # load the byte at addr B into $2.
	beqz $2, 0x2                # if $2 == 0, branch out of loop.

	addi $1, $1, 0x1	          # otherwise, increment B,
	b 0xFFFFFFFC		            # and repeat the loop.

#end_length_loop:
	subi $1, $1, 0x2	          # subtract 2 to move B back past the '\0' and '\n'.

#test_loop:
	bge $0, $1, 0x06	            # if A >= B, it's a palindrome.

	lb $2, ($0)		              # load the byte at addr A into $2,
	lb $3, ($1)		              # load the byte at addr B into $3.
	bne $2, $3, 0x06             # if $2 != $3, not a palindrome.

# Otherwise,

	addi $0, $0, 0x1           # increment A,
	subi $1, $1, 1	            # decrement B,
	b 0xFFFFFFF9		            # and repeat the loop.

#is_palin:			              # print the is_palin_msg, and exit.

	la $30, 0x00200006
	li $31, 0x4
	syscall
	b 0x4

#not_palin:
	la $30, 0x00200007	    # print the not_palin_msg, and exit.
	li $31, 0x4
  syscall
	b 0x00

#exit:			        	        # exit the program
	li $31, 0x10		              # load "exit" code into $31.
	syscall			                # make the system call.
