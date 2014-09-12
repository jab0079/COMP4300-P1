/*
 * 
 *      Accumulator.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the Accumulator Simulator
 * 
 *      Change Log:
 * 	    9/11/14 - Finished Implementation and fixed bugs
 *          9/10/14 - Added instruction set constants
 *          9/9/14 - Initial creation
 * 
 * 
 */
#include "Accumulator.hh"

Accumulator::Accumulator(MemSys* mem) 
: Simulator(mem)
{
}

Accumulator::~Accumulator()
{}

void Accumulator::run()
{
    std::cout << "\tStarting Accumulator..." << std::endl;
    
    inst curr_inst = 0, opcode = 0;
    addr address = 0x0;
    u_int32_t value = 0;
    
    bool user_mode = true;
    while (user_mode) 
    {
      // Read memory at PC  
      curr_inst = *((inst*)m_memory->read(m_pc,sizeof(inst)));
      
      // Get opcode and address
      opcode = curr_inst & 0xFF000000;
      opcode = opcode >> 24; 	// Bitwise shift opcode down
      address = curr_inst & 0x00FFFFFF;
      
      // Increment PC
      m_pc += sizeof(inst);
      
      switch (opcode)
      {
	case ACC_INST_LOAD:	// LOAD
	  m_register = *((reg*)m_memory->read(address, sizeof(reg)));		// read contents of memory at address into accumulator
	  break;
	  
	case ACC_INST_STO:	// STO
	  m_memory->write(address, &m_register, sizeof(reg));			// write value of accumulator to memory at address
	  break;
	    
	case ACC_INST_MULT:	// MULT
	  value = *((u_int32_t*)m_memory->read(address, sizeof(u_int32_t)));	// read contents of memory at address
	  m_register *= value;							// multiply the value with the accumulator 
	  break;
	  
	case ACC_INST_ADD:	// ADD
	  value = *((u_int32_t*)m_memory->read(address, sizeof(u_int32_t)));	// read contents of memory at address
	  m_register += value;							// add value to accumulator
	  break;
	  
	case ACC_INST_END:	// END
	  user_mode = false;
	  break;
	  
	default:
	  break;
      }
    }
    
    std::cout << "\tEnding Accumulator..." << std::endl;
}

