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
  m_rd_old = m_rd_new;
}

void Latch_EXE_MEM::push_opcode(const inst& op)
{ m_opcode_new = op; }
void Latch_EXE_MEM::push_aluout(const u_int32_t& aluout)
{ m_aluout_new = aluout; }
void Latch_EXE_MEM::push_rd(const u_int32_t& rd)
{ m_rd_new = rd; }

inst Latch_EXE_MEM::pull_opcode() const
{ return m_opcode_old; }
u_int32_t Latch_EXE_MEM::pull_aluout() const
{ return m_aluout_old; }
u_int32_t Latch_EXE_MEM::pull_rd() const
{ return m_rd_old; }








