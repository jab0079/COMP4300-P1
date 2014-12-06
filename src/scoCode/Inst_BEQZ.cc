/*
 * 
 *      Inst_BEQZ.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for BEQZ is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_BEQZ.hh"

Inst_BEQZ::Inst_BEQZ(ScoreboardSimulator* simu, inst the_instruction)
: Instruction(simu, the_instruction)
{}

Inst_BEQZ::~Inst_BEQZ() {}

Inst_BEQZ::Inst_BEQZ(const Inst_BEQZ& other)
: Instruction(other)
{}

Instruction* Inst_BEQZ::clone() const { return new Inst_BEQZ(*this); }

/* Stage Methods ------------------------------------------------------------*/
void Inst_BEQZ::decode()
{
    sim->setInstructionCount(sim->getInstructionCount() + 1);
    inst curr_inst = this->getInstruction();
    
    // Get source 1 register number
    m_rsrc1 = (curr_inst & 0x00F80000) >> 19;
    // Get signed label offset value and calculate newpc
    m_value = (int32_t)decodeInstr(curr_inst, 19);

}

void Inst_BEQZ::fetch_operands()
{
    m_opA = (int32_t)sim->getRegister(m_rsrc1);
}

void Inst_BEQZ::execute()
{
    m_aluout = sim->getProgramCounter() + m_value * 4;
    if (m_opA == 0)
    { // Branch (update PC), if equals zero
        sim->setProgramCounter(m_aluout);
    }
}

void Inst_BEQZ::memory()
{
    //blank for beqz
}

void Inst_BEQZ::write_back()
{
    //blank for beqz
}


