COMP4300 - Computer Architecture - Project 4

===============================================================================


Authors --------------------------------------------------------------------
	
	Adam Eichelkraut - ake0005@tigermail.auburn.edu
	Jared Brown - jab0079@tigermail.auburn.edu



Synopsis--------------------------------------------------------------------
    
	This project extended the previous General Purpose Register (GPR) 
	multi-cycle machine with a scalar piped architecture into a 
	Scoreboard-based controller. Instead of the single pipeline of the
	previous simulator, the scoreboard manages four independent functional
	units (FUs). The Scoreboard takes care of any potential hazards as well.
	For this project, the Scoreboard can be set to either reserve the entire
	Functional Unit for each instruction or only the very first stage.
	Each instruction has 4 stages: Issue, Fetch Operands, Execution, and Write 
	Back. Each specific instruction is encapsulated in its own object that is 
	derived from the Instruction class. They take in a Simulator object as 
	a context to manipulate. From here the FUs can use these Instructions 
	to change properties of the Simulator without having to know the specific 		implementation details.

	GENERAL PURPOSE REGISTER MACHINE INSTRUCTION SET (from previous project) 
		
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
 
	ADDITIONAL FLOATING POINT REGISTERS (new)

		FADD -  | 0x0D | 5-bit dest | 5-bit src1 | 5-bit src2 | 9-bit unused |
		FMUL -  | 0x0E | 5-bit dest | 5-bit src1 | 5-bit src2 | 9-bit unused |
		FSUB -  | 0x0F | 5-bit dest | 5-bit src1 | 5-bit src2 | 9-bit unused |
		LD   -  | 0x10 | 5-bit dest | 19-bit relative offset ............... |
		SD   -  | 0x11 | 5-bit dest | 19-bit relative offset ............... |

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

	src/scoCode - contains all source files for the scoSim
    
	src/utils     - contains all utility source files 
			            used by all executables

Testing -----------------------------------------------------------------------
  
  The sample code can be ran using the executables in the bin/ directory
  by passing the path name as a command line argument and "N" or "P" to indicate
  not-pipelined or pipelined, respectively. 
	For example: 	"./scoSim ../docs/lab4a.s N" or
		   	"./scoSim ../docs/lab4c.s P"

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

	Results from lab4c.s (not-pipelined)
	Instruction Count: 1331
	Cycle Count: 4703
	NOP Count: 306

	Results from lab4c.s (pipelined)
	Instruction Count: 1331
	Cycle Count: 1674
	NOP Count: 306


---------------------------------------------------------------------
