/*
 * 
 *      Inst_LB.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for LB is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_LB.hh"

Inst_LB::Inst_LB(inst the_instruction)
: Instruction(the_instruction)
{}

Inst_LB::~Inst_LB() {}

/* Stage Methods ------------------------------------------------------------*/
void Inst_LB::decode(ScoreboardSimulator& sim)
{
    sim.setInstructionCount(sim.getInstructionCount() + 1);
    inst curr_inst = this->getInstruction();

    // Get r_dest number
    m_rdest = (curr_inst & 0x00F80000) >> 19;
    // Get r_src1 number
    m_rsrc1 = (curr_inst & 0x0007C000) >> 14;
    // Get signed offset value
    m_value = decodeInstr(curr_inst, 14);
}

void Inst_LB::execute(ScoreboardSimulator& sim)
{
    int32_t op_A = (int32_t)sim.getRegister(m_rsrc1);
    // Correct target address and push to ALU_out
    m_aluout = (MemSys::BaseUserDataSegmentAddress | op_A) + m_value;
}

void Inst_LB::memory(ScoreboardSimulator& sim)
{
    // Read from memory at corrected target address into MDR
    //m_mdr = *((u_int8_t*)m_memory->read(m_exe_mem->pull_aluout(), sizeof(u_int8_t)));
}

void Inst_LB::write_back(ScoreboardSimulator& sim)
{
    // Write MDR to r_dest
    sim.setRegister(m_rdest, m_mdr);
}


