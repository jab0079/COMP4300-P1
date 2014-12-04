/*
 * 
 *      Inst_ADD.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for ADD is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_ADD.hh"

Inst_ADD::Inst_ADD(inst the_instruction)
: Instruction(the_instruction)
{}

Inst_ADD::~Inst_ADD() {}

/* Stage Methods ------------------------------------------------------------*/
void Inst_ADD::decode(ScoreboardSimulator& sim)
{
    sim.setInstructionCount(sim.getInstructionCount() + 1);
    
    inst curr_inst = this->getInstruction();
    
    // Get r_dest number
    m_dest = (curr_inst & 0x00F80000) >> 19;
    // Get r_src1 number
    m_rsrc1 = (curr_inst & 0x0007C000) >> 14;
    // Get r_src2 number
    m_rsrc2 = (curr_inst & 0x00003E00) >> 9;
}

void Inst_ADD::fetch_operands(ScoreboardSimulator& sim)
{
    m_opA = sim.getRegister(m_rsrc1);
    m_opB = sim.getRegister(m_rsrc2);
}

void Inst_ADD::execute(ScoreboardSimulator& sim)
{
    // Add op A & B
    m_aluout =  m_opA + m_opB;
}

void Inst_ADD::memory(ScoreboardSimulator& sim)
{
    //blank for ADD
}

void Inst_ADD::write_back(ScoreboardSimulator& sim)
{
    // Write to r_dest
    sim.setRegister(m_dest, m_aluout);
}



