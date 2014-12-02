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

Inst_BEQZ::Inst_BEQZ(inst the_instruction)
: Instruction(the_instruction)
{}

Inst_BEQZ::~Inst_BEQZ() {}

/* Stage Methods ------------------------------------------------------------*/
void Inst_BEQZ::decode(ScoreboardSimulator& sim)
{
    sim.setInstructionCount(sim.getInstructionCount() + 1);
    inst curr_inst = this->getInstruction();
    
    // Get source 1 register number
    u_int8_t r_src1 = (curr_inst & 0x00F80000) >> 19;
    // Get signed label offset value and calculate newpc
    int32_t value = decodeInstr(curr_inst, 19);
    int32_t aluout = sim.getProgramCounter() + value * 4;
            
    // Get op A (checking for data hazards)
    int32_t op_A = (int32_t)sim.getRegister(r_src1);

    if (op_A == 0)
    { // Branch (update PC), if equals zero
        sim.setProgramCounter(aluout);
    }
}

void Inst_BEQZ::execute(ScoreboardSimulator& sim)
{
    //blank for beqz
}

void Inst_BEQZ::memory(ScoreboardSimulator& sim)
{
    //blank for beqz
}

void Inst_BEQZ::write_back(ScoreboardSimulator& sim)
{
    //blank for beqz
}


