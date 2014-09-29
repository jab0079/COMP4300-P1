/*
 * 
 *      GeneralPurposeRegister.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the GeneralPurposeRegister Simulator
 * 
 *      Change Log:
 *          9/29/14 - Initial Creation
 * 
 * 
 */
#include "GeneralPurposeRegister.hh"

GeneralPurposeRegister::GeneralPurposeRegister(MemSys* mem) 
: Simulator(mem)
{
}

GeneralPurposeRegister::~GeneralPurposeRegister()
{}

void GeneralPurposeRegister::run()
{
    std::cout << "\tStarting GPR..." << std::endl;
    
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
        case GPR_ADDI:
            // stubbed out...
            break;
        case GPR_B:
            // stubbed out...
            break;
        case GPR_BEGZ:
            // stubbed out...
            break;
        case GPR_BGE:
            // stubbed out...
            break;
        case GPR_BNE:
            // stubbed out...
            break;
        case GPR_LA:
            // stubbed out...
            break;
        case GPR_LB:
            // stubbed out...
            break;
        case GPR_LI:
            // stubbed out...
            break;
        case GPR_SUBI:
            // stubbed out...
            break;
        case GPR_SYSCALL:
            // stubbed out...
            break;
	default:
	  break;
      }
    }
    
    std::cout << "\tEnding GPR..." << std::endl;
}

