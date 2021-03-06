/*
 * 
 *      Latch_EXE_MEM.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the Latch_EXE_MEM
 *          object between the instruction fetch and the instruction decode
 *          cycles.
 * 
 *      Change Log:
 *          10/24/14 - Added reset method
 *          10/20/14 - Added operand B
 *          10/18/14 - Added pushes/pulls/update method impl
 *          10/14/14 - Initial Creation
 * 
 * 
 */

#include "Latch_EXE_MEM.hh"

Latch_EXE_MEM::Latch_EXE_MEM() {}

Latch_EXE_MEM::~Latch_EXE_MEM() {}

void Latch_EXE_MEM::update()
{
    m_opcode_old = m_opcode_new;
    m_aluout_old = m_aluout_new;
    m_opB_old = m_opB_new;
    m_rd_old = m_rd_new;
}

void Latch_EXE_MEM::reset()
{
    reset_old();
    reset_new();
}

void Latch_EXE_MEM::reset_new()
{
    m_opcode_new = 0;
    m_aluout_new = 0;
    m_opB_new = 0;
    m_rd_new = 0;
}

void Latch_EXE_MEM::reset_old()
{
    m_opcode_old = 0;
    m_aluout_old = 0;
    m_opB_old = 0;
    m_rd_old = 0;
}

void Latch_EXE_MEM::push_opcode(const inst& op)
{ m_opcode_new = op; }
void Latch_EXE_MEM::push_aluout(const int32_t& aluout)
{ m_aluout_new = aluout; }
void Latch_EXE_MEM::push_opB(const int32_t& opB)
{ m_opB_new = opB; }
void Latch_EXE_MEM::push_rd(const u_int32_t& rd)
{ m_rd_new = rd; }

inst Latch_EXE_MEM::pull_opcode() const
{ return m_opcode_old; }
int32_t Latch_EXE_MEM::pull_aluout() const
{ return m_aluout_old; }
int32_t Latch_EXE_MEM::pull_opB() const
{ return m_opB_old; }
u_int32_t Latch_EXE_MEM::pull_rd() const
{ return m_rd_old; }








