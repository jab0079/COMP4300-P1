# Stack Hand Compiled Source

.data
0x00200000:3  #X
0x00200004:7  #A
0x00200008:5  #B
0x0020000C:4  #C

.text
  PUSH 0x00200000	# Push X onto stack
  PUSH 0x00200000	# Push X onto stack
  MULT 			# Multiply top two values on the stack (X^2)
  PUSH 0x00200004	# Push A onto stack
  MULT 			# Multiply top two values on the stack (AX^2)
  PUSH 0x00200000	# Push X onto stack
  PUSH 0x00200008	# Push B onto stack
  MULT 			# Multiply top two values on the stack (BX)
  ADD 			# Add top two values on the stack (AX^2 + BX)
  PUSH 0x0020000C	# Push C onto stack
  ADD 			# Add top two values on the stack (AX^2 + BX + C)
  POP 0x00200010	# Pop answer off stack into memory
  END
