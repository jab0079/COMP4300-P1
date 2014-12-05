/*
 * 
 *      Inst_FADD.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for FADD is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_FADD.hh"

Inst_FADD::Inst_FADD(inst the_instruction)
: Instruction(the_instruction)
{}

Inst_FADD::~Inst_FADD() {}

Inst_FADD::Inst_FADD(const Inst_FADD& other)
: Instruction(other)
{}

Instruction* Inst_FADD::clone() const { return new Inst_FADD(*this); }

/* Stage Methods ------------------------------------------------------------*/
void Inst_FADD::decode(ScoreboardSimulator& sim)
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

void Inst_FADD::fetch_operands(ScoreboardSimulator& sim)
{
    m_opA_fp = (float)sim.getFPRegister(m_rsrc1);
    m_opB_fp = (float)sim.getFPRegister(m_rsrc2);
}

void Inst_FADD::execute(ScoreboardSimulator& sim)
{
    m_aluout_fp = m_opA_fp + m_opB_fp;
}

void Inst_FADD::memory(ScoreboardSimulator& sim)
{
    //blank for FADD
}

void Inst_FADD::write_back(ScoreboardSimulator& sim)
{
    sim.setFPRegister(m_dest, m_aluout_fp);
}


