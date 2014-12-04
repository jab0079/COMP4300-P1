/*
 * 
 *      Inst_LA.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for LA is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_LA.hh"

Inst_LA::Inst_LA(inst the_instruction)
: Instruction(the_instruction)
{}

Inst_LA::~Inst_LA() {}

/* Stage Methods ------------------------------------------------------------*/
void Inst_LA::decode(ScoreboardSimulator& sim)
{
    sim.setInstructionCount(sim.getInstructionCount() + 1);
    inst curr_inst = this->getInstruction();

    // Get r_dest number
    m_dest = (curr_inst & 0x00F80000) >> 19;
    // Get signed label offset value
    m_value = decodeInstr(curr_inst, 19);
}

void Inst_LA::fetch_operands(ScoreboardSimulator& sim)
{
    //blank for la
}

void Inst_LA::execute(ScoreboardSimulator& sim)
{
    //blank for la
}

void Inst_LA::memory(ScoreboardSimulator& sim)
{
    //blank for la
}

void Inst_LA::write_back(ScoreboardSimulator& sim)
{
    // Load signed label offset address into r_dest
    sim.setRegister(m_dest, m_value);
}


