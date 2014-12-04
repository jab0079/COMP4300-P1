/*
 * 
 *      Inst_BNE.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for BNE is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_BNE.hh"

Inst_BNE::Inst_BNE(inst the_instruction)
: Instruction(the_instruction)
{}

Inst_BNE::~Inst_BNE() {}

/* Stage Methods ------------------------------------------------------------*/
void Inst_BNE::decode(ScoreboardSimulator& sim)
{
    sim.setInstructionCount(sim.getInstructionCount() + 1);
    inst curr_inst = this->getInstruction();
    // Get source 1 register number
    m_rsrc1 = (curr_inst & 0x00F80000) >> 19;
    // Get source 2 register number
    m_rsrc2 = (curr_inst & 0x0007C000) >> 14;
    // Get signed label offset value and calculate newpc
    m_value = decodeInstr(curr_inst, 14);
}

void Inst_BNE::fetch_operands(ScoreboardSimulator& sim)
{
    m_opA = (int32_t)sim.getRegister(m_rsrc1);
    m_opB = (int32_t)sim.getRegister(m_rsrc2);
}

void Inst_BNE::execute(ScoreboardSimulator& sim)
{
    int32_t aluout = sim.getProgramCounter() + m_value * 4;
    if (m_opA != m_opB)
    { // Branch (update PC), if value of r_src1(op_A) != r_src2(op_B)
        sim.setProgramCounter(aluout);
    }
}

void Inst_BNE::memory(ScoreboardSimulator& sim)
{
    //blank for bne
}

void Inst_BNE::write_back(ScoreboardSimulator& sim)
{
    //blank for bne
}


