/*
 * 
 *      Inst_SUBI.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for SUBI is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_SUBI.hh"

Inst_SUBI::Inst_SUBI(ScoreboardSimulator* simu, inst the_instruction)
: Instruction(simu, the_instruction)
{}

Inst_SUBI::~Inst_SUBI() {}

Inst_SUBI::Inst_SUBI(const Inst_SUBI& other)
: Instruction(other)
{}

Instruction* Inst_SUBI::clone() const { return new Inst_SUBI(*this); }

/* Stage Methods ------------------------------------------------------------*/
void Inst_SUBI::decode()
{
    sim->setInstructionCount(sim->getInstructionCount() + 1);
    inst curr_inst = this->getInstruction();

    // Get r_dest number
    m_dest = (curr_inst & 0x00F80000) >> 19;
    // Get r_src1 number
    m_rsrc1 = (curr_inst & 0x0007C000) >> 14;
    // Get signed immediate value
    m_value = decodeInstr(curr_inst, 14);
}

void Inst_SUBI::fetch_operands()
{
    m_opA = sim->getRegister(m_rsrc1);
}

void Inst_SUBI::execute()
{
    // Subtract op A & B
    m_aluout = m_opA - m_value;
}

void Inst_SUBI::memory()
{
    //blank for subi
}

void Inst_SUBI::write_back()
{
    sim->setRegister(m_dest, m_aluout);
}


