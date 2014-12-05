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
{
    //decode opcode for ease of usage
    //(not technically decoded here, we just the instruction
    //to have it so we can retrieve it later in other components)
    m_opcode = ((the_instruction & 0xFF000000) >> 24);
}

Instruction::~Instruction() {}

Instruction::Instruction(const Instruction& other)
{
    m_dest = other.m_dest;
    m_rsrc1 = other.m_rsrc1;
    m_rsrc2 = other.m_rsrc2;
    m_mdr = other.m_mdr;
    m_mdr_fp = other.m_mdr_fp;
    m_aluout = other.m_aluout;
    m_opA = other.m_opA;
    m_opB = other.m_opB;
    m_value = other.m_value;
    m_aluout_fp = other.m_aluout_fp;
    m_opA_fp = other.m_opA_fp;
    m_opB_fp = other.m_opB_fp;
    m_instruction = other.m_instruction;
    m_opcode = other.m_opcode;
}

inst Instruction::getInstruction() const
{ return m_instruction; }
u_int8_t Instruction::getOpCode() const
{ return m_opcode; }

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

u_int8_t Instruction::getDestinationRegister() const
{ return m_dest; }
u_int8_t Instruction::getSourceRegister1() const
{ return m_rsrc1; }
u_int8_t Instruction::getSourceRegister2() const
{ return m_rsrc2; }
u_int8_t Instruction::getMDR() const
{ return m_mdr; }
float Instruction::getMDR_FP() const
{ return m_mdr_fp; }
int32_t Instruction::getALUOUT() const
{ return m_aluout; }
float Instruction::getALUOUT_FP() const
{ return m_aluout_fp; }
int32_t Instruction::getOPA() const
{ return m_opA; }
float Instruction::getOPA_FP() const
{ return m_opA_fp; }
int32_t Instruction::getOPB() const
{ return m_opB; }
float Instruction::getOPB_FP() const
{ return m_opB_fp; }
int32_t Instruction::getValue() const
{ return m_value; }
u_int32_t Instruction::getInstr_id() const
{ return m_instr_id; }
bool Instruction::getIsFP() const
{ return m_is_fp; }



