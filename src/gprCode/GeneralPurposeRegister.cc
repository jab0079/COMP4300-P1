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
    reg r_dest = 0, r_src1 = 0, r_src2 = 0;
    int32_t value = 0;
    
    bool user_mode = true;
    while (user_mode) 
    {
      // Read memory at PC  
      curr_inst = *((inst*)m_memory->read(m_pc,sizeof(inst)));
      
      // Get opcode and address
      opcode = curr_inst & 0xFF000000;
      opcode = opcode >> 24; 	// Bitwise shift opcode down
      
      // Increment PC
      m_pc += sizeof(inst);
      
      switch (opcode)
      {
        case GPR_ADDI:
	    r_dest = curr_inst & 0x00F80000;			// Get destination register number
	    r_dest = r_dest >> 19;
	    r_src1 = curr_inst & 0x0007C000;			// Get source 1 register number
	    r_src1 = r_src1 >> 14;
	    value = decodeInstr(curr_inst, 14);			// Get signed immediate value
	    
	    m_register[r_dest] = m_register[r_src1] + value;	// Add r_src1 and immediate value, store in r_dest
            break;
	    
        case GPR_B:
            value = decodeInstr(curr_inst, 24) * 4;	// Get signed label offset value
            
            m_pc += value;				// Branch
            break;
	    
        case GPR_BEGZ:
            r_src1 = curr_inst & 0x00F80000;		// Get source 1 register number
	    r_src1 = r_src1 >> 19;
	    value = decodeInstr(curr_inst, 19) * 4;	// Get signed label offset value			
	    
	    if (m_register[r_src1] == 0)		// Branch if equals zero
	    {
	      m_pc += value;
	    }
            break;
	    
        case GPR_BGE:
            r_src1 = curr_inst & 0x00F80000;			// Get source 1 register number
	    r_src1 = r_src1 >> 19;
	    r_src2 = curr_inst & 0x0007C000;			// Get source 2 register number
	    r_src2 = r_src2 >> 14;
	    value = decodeInstr(curr_inst, 14) * 4;		// Get signed label offset value			
	    
	    if (m_register[r_src1] >= m_register[r_src2])	// Branch if greater than or equal
	    {
	      m_pc += value;
	    }
            break;
	    
        case GPR_BNE:
            r_src1 = curr_inst & 0x00F80000;			// Get source 1 register number
	    r_src1 = r_src1 >> 19;
	    r_src2 = curr_inst & 0x0007C000;			// Get source 2 register number
	    r_src2 = r_src2 >> 14;
	    value = decodeInstr(curr_inst, 14) * 4;		// Get label offset value			
	    
	    if (m_register[r_src1] != m_register[r_src2])	// Branch if not equal	
	    {
	      m_pc += value;
	    }
            break;
	    
        case GPR_LA:
            r_dest = curr_inst & 0x00F80000;		// Get destination register number
	    r_dest = r_dest >> 19;
	    value = decodeInstr(curr_inst, 19) * 4;	// Get signed label offset value 			
	    
	    m_register[r_dest] = value;			// Load signed label offset address into r_dest
            break;
	    
        case GPR_LB:
            r_dest = curr_inst & 0x00F80000;			// Get destination register number
	    r_dest = r_dest >> 19;
	    r_src1 = curr_inst & 0x0007C000;			// Get source 1 register number
	    r_src1 = r_src1 >> 14;
	    value = decodeInstr(curr_inst, 14);			// Get signed offset value
	    
	    m_register[r_dest] = m_register[r_src1] + value;
            break;
	    
        case GPR_LI:
            r_dest = curr_inst & 0x00F80000;		// Get destination register number
	    r_dest = r_dest >> 19;
	    value = decodeInstr(curr_inst, 19) * 4;	// Get signed immediate value 			
	    
	    m_register[r_dest] = value;			// Load signed label offset address into r_dest
            break;
	    
        case GPR_SUBI:
            r_dest = curr_inst & 0x00F80000;			// Get destination register number
	    r_dest = r_dest >> 19;
	    r_src1 = curr_inst & 0x0007C000;			// Get source 1 register number
	    r_src1 = r_src1 >> 14;
	    imm = decodeInstr(curr_inst, 14);			// Get signed immediate value
	    
	    m_register[r_dest] = m_register[r_src1] - imm;	// Subtract r_src1 and immediate value, store in r_dest
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

int32_t GeneralPurposeRegister::decodeInstr(const u_int32_t& instr, const u_int8_t& num_bits)
{
    std::bitset<32> val32(instr);
    std::bitset<32> val;
    
    for (int i = 0; i < num_bits - 1; i++)
	val.set(i, val32[i]);
      
    for (int i = num_bits; i < 32; i++)
        val.set(i, val32[num_bits]);
    
    return val.to_ulong();
}

