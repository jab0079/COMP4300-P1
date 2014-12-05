/*
 * 
 *      Inst_LD.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for LD is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_LD.hh"

Inst_LD::Inst_LD(ScoreboardSimulator* simu, inst the_instruction)
: Instruction(simu, the_instruction)
{}

Inst_LD::~Inst_LD() {}

Inst_LD::Inst_LD(const Inst_LD& other)
: Instruction(other)
{}

Instruction* Inst_LD::clone() const { return new Inst_LD(*this); }

/* Stage Methods ------------------------------------------------------------*/
void Inst_LD::decode()
{
    sim->setInstructionCount(sim->getInstructionCount() + 1);
    inst curr_inst = this->getInstruction();

    // Get r_dest number
    m_dest = (curr_inst & 0x00F80000) >> 19;
    // Get r_src1 number
    m_rsrc1 = (curr_inst & 0x0007C000) >> 14;
    // Get signed offset value
    m_value = decodeInstr(curr_inst, 14);
}

void Inst_LD::fetch_operands()
{
    m_opA = (int32_t)sim->getRegister(m_rsrc1);
}

void Inst_LD::execute()
{
    // Correct target address and push to ALU_out
    m_aluout = (MemSys::BaseUserDataSegmentAddress | m_opA) + m_value;
}

void Inst_LD::memory()
{
    // Read from memory at corrected target address into MDR
    m_mdr_fp = *((float*)sim->getMemorySystem()->read(m_aluout, sizeof(float)));
}

void Inst_LD::write_back()
{
    // Write MDR to r_dest
    sim->setFPRegister(m_dest, m_mdr_fp);
}


