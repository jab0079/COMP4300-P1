COMP4300 - Computer Architecture - Project 3

===============================================================================


Authors --------------------------------------------------------------------
	
	Adam Eichelkraut - ake0005@tigermail.auburn.edu
	Jared Brown - jab0079@tigermail.auburn.edu



Synopsis--------------------------------------------------------------------
    
	This project extended the previous General Purpose Register (GPR) 
	multi-cycle machine into a scalar piped architecture with 5 stages. 
	Along with simulating these units, this project also emulates a 
	memory unit and a loading unit. The memory unit is a centralized 
	array-based segmented memory. The loader loads the accompanied
	source files into the memory unit to be used by the simulator.
	All loaded items from the source files by the loader are loaded
	in binary representation, following the binary encoding scheme
	shown below. The pipeline machine implements interlocks between
	the 5 MIPS stages to recognize and resolve data hazards through 
	forwarding or using NOPs.


	GENERAL PURPOSE REGISTER MACHINE INSTRUCTION SET (Modified for the Pipeline) 
		
		ADD  -  | 0x01 | 5-bit dest | 5-bit src1 | 5-bit src2 | 9-bit unused |
		ADDI -  | 0x02 | 5-bit dest | 5-bit src1 | 14-bit immediate value... |
		B    -  | 0x03 | 24-bit relative offset ............................ |
		BEQZ -  | 0x04 | 5-bit src1 | 19-bit relative offset ............... |
		BGE  -  | 0x05 | 5-bit src1 | 5-bit src2 | 14-bit offset ........... |
		BNE  -  | 0x06 | 5-bit src1 | 5-bit src2 | 14-bit offset ........... |
		LA   -  | 0x07 | 5-bit src1 | 19-bit relative offset ............... |
		LB   -  | 0x08 | 5-bit src1 | 5-bit src2 | 14-bit offset ........... |
		LI   -  | 0x09 | 5-bit dest | 19-bit immediate value ............... |
		SUBI -  | 0x0A | 5-bit dest | 5-bit src1 | 14-bit immediate value .. |
		NOP  -  | 0x0B | 24-bits usused .................................... |
		SYSCALL | 0x0C | 24-bits usused .................................... |
 
Compilation --------------------------------------------------------------------------
	
	Included with this project are a hierarchy of Makefiles that
	should assist with the compilation. To compile, simply type
	in 'make' to the commandline while in the uppermost directory
	that also contains this README file.

	NOTE: The uppermost Makefile creates two directories within
	the same directory called /bin and /obj. The /bin directory
	will contain all executables for this project. The /obj
	directory will contain all compiled objects associated with
	their respective source file names.
	
Source Tree --------------------------------------------------------------------------

  (with respect to the upper-most directory)

	bin/	  - contains all executables (created by Makefile)
    
	docs/	  - contains all extra documentation and sample code
    
	include/  - contains the header files for all sources
    
	obj/	  - contains all compiled sources (created by Makefile)
    
	src/ 	  - contains all source files
    
	src/stackCode - contains all source files for the stackSim
    
	src/accumCode - contains all source files for the accumSim

	src/gprCode - contains all source files for the gprSim

	src/pipeCode - contains all source files for the pipeSim
    
	src/utils     - contains all utility source files 
			            used by all executables

Testing -----------------------------------------------------------------------
  
  The sample code can be ran using the executables in the bin/ directory
  by passing the path name as a command line argument. 
	For example: "./pipeSim ../docs/lab3c.s"

  Below are explanations on the output that comes out of each
  executable.
	
	When you run an executable, one of the highlighted
	regions to pay attention to is the
	"Loading source into memory..." section. This output
	happens right before the source gets loaded into memory.

	The two blocks of output after that are the USER DATA
	and the USER TEXT segments from memory. 
	This output is the loaded source file in memory as hexadecimal 
	values.

	After the USER TEXT segment is when the simulator starts
	to run. While the simulator is running, there is no feedback
	as to the internal workings from memory during processing.
	
	When the simulator finishes, each sample file records their
	output into the USER DATA segment, therefore, we will print
	out that segment to show the user the correct answer.

	The total clock cycles, total instructions executed, and the
	number of NOPs are also displayed at the end of the run and
	below.

	The program cleans up memory and closes.

	lab3a.s Results
	Instruction Count: 140
	Cycle Count: 143
	NOP Count: 75


	lab3b.s Results (using "racecar") 
	cout => Y (i.e., it is a palindrome)
	Instruction Count: 140
	Cycle Count: 143
	NOP Count: 75
	

	lab3c.s Results 
	cout => 32768
	Instruction Count: 61
	Cycle Count: 63
	NOP Count: 10
	
	

---------------------------------------------------------------------
