# Accumulator Hand Compiled Source

.data
X:	.word 3
A:	.word 7
B:	.word 5
C:	.word 4

.text
  LOAD X    # Load X into accumulator's register
  MULT X    # Multiply by X (X^2)
  MULT A    # Multiply register by A (AX^2)
  STO C+4   # Store AX^2 in address after C
  LOAD X    # Load X back into register
  MULT B    # Multiply register by B (BX)
  ADD C+4   # Add (AX^2) to register
            # Register now contains AX^2+BX.
  ADD C     # AX^2+BX+C
  STO C+4   # Store output
