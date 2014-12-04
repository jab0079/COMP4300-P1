/*
 * 
 *      Inst_FMUL.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for FMUL is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_FMUL.hh"

Inst_FMUL::Inst_FMUL(inst the_instruction)
: Instruction(the_instruction)
{}

Inst_FMUL::~Inst_FMUL() {}

/* Stage Methods ------------------------------------------------------------*/
void Inst_FMUL::decode(ScoreboardSimulator& sim)
{
    sim.setInstructionCount(sim.getInstructionCount() + 1);
    
    inst curr_inst = this->getInstruction();
    
    // Get r_dest number
    m_dest = (curr_inst & 0x00F80000) >> 19;
    // Get r_src1 number
    m_rsrc1 = (curr_inst & 0x0007C000) >> 14;
    m_rsrc1 -= 16;
    // Get r_src2 number
    m_rsrc2 = (curr_inst & 0x00003E00) >> 9;
    m_rsrc2 -= 16;
}

void Inst_FMUL::fetch_operands(ScoreboardSimulator& sim)
{
    m_opA = (float)sim.getFPRegister(m_rsrc1);
    m_opB = (float)sim.getFPRegister(m_rsrc2);
}

void Inst_FMUL::execute(ScoreboardSimulator& sim)
{
    m_aluout = m_opA * m_opB;
}

void Inst_FMUL::memory(ScoreboardSimulator& sim)
{
    //blank for FMUL
}

void Inst_FMUL::write_back(ScoreboardSimulator& sim)
{
    sim.setFPRegister(m_dest, m_aluout);
}


