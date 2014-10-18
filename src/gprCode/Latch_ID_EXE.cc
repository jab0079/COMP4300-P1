/*
 * 
 *      Latch_ID_EXE.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the Latch_ID_EXE
 *          object between the instruction fetch and the instruction decode
 *          cycles.
 * 
 *      Change Log:
 *          10/14/14 - Initial Creation
 * 
 * 
 */

#include "Latch_ID_EXE.hh"

Latch_ID_EXE::Latch_ID_EXE() {}

Latch_ID_EXE::~Latch_ID_EXE() {}

void Latch_ID_EXE::update()
{
  m_newpc_old = m_newpc_new;
  m_rs_old = m_rs_new;
  m_rt_old = m_rt_new;
  m_rd_old = m_rd_new;
  m_opcode_old = m_opcode_new;
  m_val_old = m_val_new;
}

void Latch_ID_EXE::push_opcode(const inst& i)
{ m_opcode_new = i; }
void Latch_ID_EXE::push_rs(const u_int32_t& rs)
{ m_rs_new = rs; }
void Latch_ID_EXE::push_rt(const u_int32_t& rt)
{ m_rt_new = rt; }
void Latch_ID_EXE::push_rd(const u_int32_t& rd)
{ m_rd_new = rd; }
void Latch_ID_EXE::push_val(const u_int32_t& val)
{ m_val_new = val; }
void Latch_ID_EXE::push_newpc(const u_int32_t& newpc)
{ m_newpc_new = newpc; }

inst Latch_ID_EXE::pull_opcode() const
{ return m_opcode_old; }
u_int32_t Latch_ID_EXE::pull_rs() const
{ return m_rs_old; }
u_int32_t Latch_ID_EXE::pull_rt() const
{ return m_rt_old; }
u_int32_t Latch_ID_EXE::pull_rd() const
{ return m_rd_old; }
u_int32_t Latch_ID_EXE::pull_val() const
{ return m_val_old; }
u_int32_t Latch_ID_EXE::pull_newpc() const
{ return m_newpc_old; }

