/*
 * 
 *      Inst_B.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for B is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_B.hh"

Inst_B::Inst_B(inst the_instruction)
: Instruction(the_instruction)
{}

Inst_B::~Inst_B() {}

Inst_B::Inst_B(const Inst_B& other)
: Instruction(other)
{}

Instruction* Inst_B::clone() const { return new Inst_B(*this); }

/* Stage Methods ------------------------------------------------------------*/
void Inst_B::decode(ScoreboardSimulator& sim)
{
    sim.setInstructionCount(sim.getInstructionCount() + 1);
    
    inst curr_inst = this->getInstruction();
    // Get signed label offset value and calculate newpc
    m_value = decodeInstr(curr_inst, 24);

}

void Inst_B::fetch_operands(ScoreboardSimulator& sim)
{
    //blank for B
}

void Inst_B::execute(ScoreboardSimulator& sim)
{
    m_aluout = sim.getProgramCounter() + m_value * 4;
    // Branch (update PC)
    sim.setProgramCounter(m_aluout);
}

void Inst_B::memory(ScoreboardSimulator& sim)
{
    //blank for B
}

void Inst_B::write_back(ScoreboardSimulator& sim)
{
    //blank for B
}


