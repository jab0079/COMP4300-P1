# Accumulator Hand Compiled Source

.data
0x00200000:3  #X
0x00200004:7  #A
0x00200008:5  #B
0x0020000C:4 #C

.text
  LOAD 0x00200000   # Load X into accumulator's register
  MULT 0x00200000   # Multiply by X (X^2)
  MULT 0x00200004   # Multiply register by A (AX^2)
  STO 0x00200010   # Store AX^2 in address after C
  LOAD 0x00200000   # Load X back into register
  MULT 0x00200008   # Multiply register by B (BX)
  ADD 0x00200010   # Add (AX^2) to register
                    # Register now contains AX^2+BX.
  ADD 0x0020000C   # AX^2+BX+C
  STO 0x00200010   # Store output
  END
