COMP4300 - Computer Architecture - Project 2

===============================================================================


Authors -------------------------------------------------------------
	
	Adam Eichelkraut - ake0005@tigermail.auburn.edu
	Jared Brown - jab0079@tigermail.auburn.edu



Synopsis------------------------------------------------------------
    
	This project extended the previous accumulator-based machine 
	into a General Purpose Register (GPR) multi-cycle machine. 
	Along with simulating these units, this project also emulates a 
	memory unit and a loading unit. The memory unit is a centralized 
	array-based segmented memory. The loader loads the accompanied
	source files into the memory unit to be used by the simulator.
	All loaded items from the source files by the loader are loaded
	in binary representation, following the binary encoding scheme
	shown below.

	GENERAL PURPOSE REGISTER MACHINE INSTRUCTION SET
		ADDI -  | 0x01 | ... 5-bit dest | 5-bit src1 | 14-bit imm |
		B    -  | 0x02 | ... 24-bit relative offset		  |
		BEQZ -  | 0x03 | ... 5-bit src1 | 19-bit relative offset  |
		BGE  -  | 0x04 | ... 5-bit src1 | 5-bit src2 | 14-bit off |
		BNE  -  | 0x05 | ... 5-bit src1 | 5-bit src2 | 14-bit off |
		LA   -  | 0x06 | ... 5-bit dest | 19-bit relative offset  |
		LB   -  | 0x07 | ... 5-bit dest | 5-bit src1 | 14-bit off |
		LI   -  | 0x08 | ... 5-bit dest | 19-bit immediate value  |
		SUBI -  | 0x09 | ... 5-bit dest | 5-bit src1 | 14-bit imm |
		SYSCALL | 0x0A | N/A (24-bits) -------------------------- |
 
Compilation ---------------------------------------------------------
	
	Included with this project are a hierarchy of Makefiles that
	should assist with the compilation. To compile, simply type
	in 'make' to the commandline while in the uppermost directory
	that also contains this README file.

	NOTE: The uppermost Makefile creates two directories within
	the same directory called /bin and /obj. The /bin directory
	will contain all executables for this project. The /obj
	directory will contain all compiled objects associated with
	their respective source file names.
	
Source Tree ---------------------------------------------------------

  (with respect to the upper-most directory)

	bin/	  - contains all executables (created by Makefile)
    
	docs/	  - contains all extra documentation and sample code
    
	include/  - contains the header files for all sources
    
	obj/	  - contains all compiled sources (created by Makefile)
    
	src/ 	  - contains all source files
    
	src/stackCode - contains all source files for the stackSim
    
	src/accumCode - contains all source files for the accumSim

	src/gprCode - contains all source files for the gprSim
    
	src/utils     - contains all utility source files 
			            used by all executables

Testing -------------------------------------------------------------

  Below are explanations on the output that comes out of each
  executable.
	
	When you run an executable, one of the highlighted
	regions to pay attention to is the
	"Loading source into memory..." section. This output
	happens right before the source gets loaded into memory.

	The two blocks of output after that are the USER DATA
	and the USER TEXT segments from memory. 
	This output is the loaded source file in memory as hexadecimal values.

	After the USER TEXT segment is when the simulator starts
	to run. While the simulator is running, there is no feedback
	as to the internal workings from memory during processing.
	
	When the simulator finishes, each sample file records their
	output into the USER DATA segment, therefore, we will print
	out that segment to show the user the correct answer.
	
	The program cleans up memory and closes.

---------------------------------------------------------------------
