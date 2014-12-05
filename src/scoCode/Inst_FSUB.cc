/*
 * 
 *      Inst_FSUB.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for FSUB is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_FSUB.hh"

Inst_FSUB::Inst_FSUB(inst the_instruction)
: Instruction(the_instruction)
{}

Inst_FSUB::~Inst_FSUB() {}

Inst_FSUB::Inst_FSUB(const Inst_FSUB& other)
: Instruction(other)
{}

Instruction* Inst_FSUB::clone() const { return new Inst_FSUB(*this); }

/* Stage Methods ------------------------------------------------------------*/
void Inst_FSUB::decode(ScoreboardSimulator& sim)
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

void Inst_FSUB::fetch_operands(ScoreboardSimulator& sim)
{
    m_opA_fp = (float)sim.getFPRegister(m_rsrc1);
    m_opB_fp = (float)sim.getFPRegister(m_rsrc2);
}

void Inst_FSUB::execute(ScoreboardSimulator& sim)
{
    m_aluout_fp = m_opA_fp - m_opB_fp;
}

void Inst_FSUB::memory(ScoreboardSimulator& sim)
{
    //blank for FSUB
}

void Inst_FSUB::write_back(ScoreboardSimulator& sim)
{
    sim.setFPRegister(m_dest, m_aluout_fp);
}


