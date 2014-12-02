/*
 * 
 *      Inst_NOP.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for NOP is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_NOP.hh"

Inst_NOP::Inst_NOP(inst the_instruction)
: Instruction(the_instruction)
{}

Inst_NOP::~Inst_NOP() {}

/* Stage Methods ------------------------------------------------------------*/
void Inst_NOP::decode(ScoreboardSimulator& sim)
{
    sim.setInstructionCount(sim.getInstructionCount() + 1);
    sim.setNOPCount(sim.getNOPCount() + 1);
}

void Inst_NOP::execute(ScoreboardSimulator& sim)
{
    //blank for NOP
}

void Inst_NOP::memory(ScoreboardSimulator& sim)
{
    //blank for NOP
}

void Inst_NOP::write_back(ScoreboardSimulator& sim)
{
    //blank for NOP
}


