/*
 * 
 *      Inst_SD.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for SD is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_SD.hh"

Inst_SD::Inst_SD(inst the_instruction)
: Instruction(the_instruction)
{}

Inst_SD::~Inst_SD() {}

/* Stage Methods ------------------------------------------------------------*/
void Inst_SD::decode(ScoreboardSimulator& sim)
{
    sim.setInstructionCount(sim.getInstructionCount() + 1);
    inst curr_inst = this->getInstruction();

    // Get r_dest number
    m_rsrc1 = (curr_inst & 0x00F80000) >> 19;
    m_rsrc1 -= 16;
    // Get r_src1 number
    m_rsrc2 = (curr_inst & 0x0007C000) >> 14;
    // Get signed offset value
    m_value = decodeInstr(curr_inst, 14);
}

void Inst_SD::fetch_operands(ScoreboardSimulator& sim)
{
    m_opA = (float)sim.getFPRegister(m_rsrc1);
    m_opB = (int32_t)sim.getRegister(m_rsrc2);
}

void Inst_SD::execute(ScoreboardSimulator& sim)
{
    // Correct target address and push to ALU_out
    m_aluout = (MemSys::BaseUserDataSegmentAddress | m_opB) + m_value;
}

void Inst_SD::memory(ScoreboardSimulator& sim)
{
    // Write memory at corrected target address into MDR
    bool result = *((float*)sim.getMemorySystem()->write(m_aluout, &m_opA ,sizeof(float)));
}

void Inst_SD::write_back(ScoreboardSimulator& sim)
{
    //Blank for SD
}


