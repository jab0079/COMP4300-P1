/*
 * 
 *      Latch_MEM_WB.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the Latch_MEM_WB
 *          object between the instruction fetch and the instruction decode
 *          cycles.
 * 
 *      Change Log:
 *          10/20/14 - Added operand B
 *          10/18/14 - Implemented pulls/pushes/update methods
 *          10/14/14 - Initial Creation
 * 
 * 
 */

#include "Latch_MEM_WB.hh"

Latch_MEM_WB::Latch_MEM_WB() {}

Latch_MEM_WB::~Latch_MEM_WB() {}

void Latch_MEM_WB::update()
{
  m_opcode_old = m_opcode_new;
  m_mdr_old = m_mdr_new;
  m_aluout_old = m_aluout_new;
  m_opB_old = m_opB_new;
  m_rd_old = m_rd_new;
}

void Latch_MEM_WB::push_opcode(const inst& opcode)
{ m_opcode_new = opcode; }
void Latch_MEM_WB::push_mdr(const u_int32_t& mdr)
{ m_mdr_new = mdr; }
void Latch_MEM_WB::push_aluout(const u_int32_t& aluout)
{ m_aluout_new = aluout; }
void Latch_MEM_WB::push_opB(const u_int32_t& opB)
{ m_opB_new = opB; }
void Latch_MEM_WB::push_rd(const u_int32_t& rd)
{ m_rd_new = rd; }

inst Latch_MEM_WB::pull_opcode() const
{ return m_opcode_old; }
u_int32_t Latch_MEM_WB::pull_mdr() const
{ return m_mdr_old; }
u_int32_t Latch_MEM_WB::pull_aluout() const
{ return m_aluout_old; }
u_int32_t Latch_MEM_WB::pull_opB() const
{ return m_opB_old; }
u_int32_t Latch_MEM_WB::pull_rd() const
{ return m_rd_old; }
