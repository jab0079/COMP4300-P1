/*
 *
 *      Stack.cc
 *
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 *      Description:
 *          This class defines the implementation for the stack-based simulator.
 *
 *      Change Log:
 * 	    9/10/14 - Finished implementation
 *          9/8/14 - Initial implementation created
 *
 *
 */
#include "Stack.hh"

Stack::Stack(MemSys* mem)
: Simulator(mem)
{
}

Stack::~Stack()
{}

void Stack::run()
{
    std::cout << "\tStarting Stack..." << std::endl;
    
    inst curr_inst = 0, opcode = 0;
    addr address = 0x0;
    u_int32_t value1 = 0, value2 = 0, result = 0;
    
    bool user_mode = true;
    while (user_mode) 
    {
      // Read memory at PC  
      curr_inst = *((inst*)m_memory->read(m_pc,sizeof(inst))); 	// *** Causes a Segmentation Fault (core dumped) error when running 
      
      // Get opcode and address
      opcode = curr_inst & 0xFF000000;
      opcode >> 24; 	// Bitwise shift opcode down
      address = curr_inst & 0x00FFFFFF;
      
      // Increment PC
      m_pc += sizeof(inst);
      
      switch (opcode)
      {
	case PUSH:
	  value1 = *((u_int32_t*)m_memory->read(address, sizeof(u_int32_t)));	// read contents of memory at address
	  m_memory->write(m_sp, (void*)value1, sizeof(u_int32_t));		// write value onto top of stack
	  m_sp += sizeof(u_int32_t);						// increment stack pointer
	  break;
	  
	case POP:
	  value1 = *((u_int32_t*)m_memory->read(m_sp, sizeof(u_int32_t)));	// read one word off the top of the stack
	  m_sp -= sizeof(u_int32_t);						// decrement stack pointer
	  m_memory->write(address, (void*)value1, sizeof(u_int32_t));		// write value to memory at address
	  break;
	  
	case ADD:
	  value1 = *((u_int32_t*)m_memory->read(m_sp, sizeof(u_int32_t)));	// read first word off the top of the stack
	  m_sp -= sizeof(u_int32_t);						// decrement stack pointer
	  value2 = *((u_int32_t*)m_memory->read(m_sp, sizeof(u_int32_t)));	// read second word off the top of the stack
	  result = value1 + value2;
	  m_memory->write(m_sp, (void*)result, sizeof(u_int32_t));		// write value to memory at address 
	  break;
	  
	case MULT:
	  value1 = *((u_int32_t*)m_memory->read(m_sp, sizeof(u_int32_t)));	// read first word off the top of the stack
	  m_sp -= sizeof(u_int32_t);						// decrement stack pointer
	  value2 = *((u_int32_t*)m_memory->read(m_sp, sizeof(u_int32_t)));	// read second word off the top of the stack
	  result = value1 * value2;
	  m_memory->write(m_sp, (void*)result, sizeof(u_int32_t));		// write value to memory at address 
	  break;
	  
	case END:
	  user_mode = false;
	  break;
	  
	default:
	  break;
      }
    }
    
    std::cout << "\tEnding Stack..." << std::endl;
}
