/*
 * 
 *      Inst_ADDI.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for ADDI is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_ADDI.hh"

Inst_ADDI::Inst_ADDI(inst the_instruction)
: Instruction(the_instruction)
{}

Inst_ADDI::~Inst_ADDI() {}

/* Stage Methods ------------------------------------------------------------*/
void Inst_ADDI::decode(ScoreboardSimulator& sim)
{
    sim.setInstructionCount(sim.getInstructionCount() + 1);
    
    inst curr_inst = this->getInstruction();
    // Get r_dest number
    m_rdest = (curr_inst & 0x00F80000) >> 19;    
    // Get r_src1 number
    m_rsrc1 = (curr_inst & 0x0007C000) >> 14;
    // Get signed immediate
    m_value = decodeInstr(curr_inst, 14);
}

void Inst_ADDI::execute(ScoreboardSimulator& sim)
{
    // Add op A & B
    m_aluout = sim.getRegister(m_rsrc1) + m_value;
}

void Inst_ADDI::memory(ScoreboardSimulator& sim)
{
    //blank for addi
}

void Inst_ADDI::write_back(ScoreboardSimulator& sim)
{
    sim.setRegister(m_rdest, m_aluout);
}


