/*
 * 
 *      Inst_LI.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for LI is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_LI.hh"

Inst_LI::Inst_LI(ScoreboardSimulator* simu, inst the_instruction)
: Instruction(simu, the_instruction)
{}

Inst_LI::~Inst_LI() {}

Inst_LI::Inst_LI(const Inst_LI& other)
: Instruction(other)
{}

Instruction* Inst_LI::clone() const { return new Inst_LI(*this); }

/* Stage Methods ------------------------------------------------------------*/
void Inst_LI::decode()
{
    sim->setInstructionCount(sim->getInstructionCount() + 1);
    inst curr_inst = this->getInstruction();

    // Get r_dest number
    m_dest = (curr_inst & 0x00F80000) >> 19;
    // Get signed immediate value
    m_value = decodeInstr(curr_inst, 19);
}

void Inst_LI::fetch_operands()
{
    //blank for li
}

void Inst_LI::execute()
{
    //blank for li
}

void Inst_LI::memory()
{
    //blank for li
}

void Inst_LI::write_back()
{
    // Load signed label offset address into r_dest
    sim->setRegister(m_dest, m_value);
}


