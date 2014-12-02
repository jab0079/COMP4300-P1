/*
 * 
 *      Instruction.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the provided
 *          methods that go along with the abstract Instruction interface.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Instruction.hh"

Instruction::Instruction(inst the_instruction)
: m_instruction(the_instruction)
{}

Instruction::~Instruction() {}

inst Instruction::getInstruction() const
{return m_instruction; }

int32_t Instruction::decodeInstr(const u_int32_t& instr, const u_int8_t& num_bits)
{
    std::bitset<32> val32(instr);
    std::bitset<32> val;
    
    for (int i = 0; i < num_bits - 1; i++)      // Copy all bits up to msb
        val.set(i, val32[i]);
      
    for (int i = num_bits - 1; i < 32; i++)     // Sign extend msb
        val.set(i, val32[num_bits - 1]);
    
    return val.to_ulong();
}

