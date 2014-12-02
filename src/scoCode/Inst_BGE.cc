/*
 * 
 *      Inst_BGE.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for BGE is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Inst_BGE.hh"

Inst_BGE::Inst_BGE(inst the_instruction)
: Instruction(the_instruction)
{}

Inst_BGE::~Inst_BGE() {}

/* Stage Methods ------------------------------------------------------------*/
void Inst_BGE::decode(ScoreboardSimulator& sim)
{
    sim.setInstructionCount(sim.getInstructionCount() + 1);
    inst curr_inst = this->getInstruction();
    // Get source 1 register number
    u_int8_t r_src1 = (curr_inst & 0x00F80000) >> 19;
    // Get source 2 register number
    u_int8_t r_src2 = (curr_inst & 0x0007C000) >> 14;
    // Get signed label offset value and calculate newpc
    int32_t value = decodeInstr(curr_inst, 14);
    int32_t aluout = sim.getProgramCounter() + value * 4;
            
    // Get op A & B (checking for data hazards)
    int32_t op_A = (int32_t)sim.getRegister(r_src1);
    int32_t op_B = (int32_t)sim.getRegister(r_src2);
    
    if (op_A >= op_B)
    { // Branch (update PC), if value of r_src1(op_A) >= r_src2(op_B)
        sim.setProgramCounter(aluout);
    }
}

void Inst_BGE::execute(ScoreboardSimulator& sim)
{
    //blank for bge
}

void Inst_BGE::memory(ScoreboardSimulator& sim)
{
    //blank for bge
}

void Inst_BGE::write_back(ScoreboardSimulator& sim)
{
    //blank for bge
}


