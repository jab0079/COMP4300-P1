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
 *          10/24/14 - Added reset method
 *          10/20/14 - Added operand A, B
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
    m_opA_old = m_opA_new;
    m_opB_old = m_opB_new;
}

void Latch_ID_EXE::reset()
{
    reset_old();
    reset_new();
}

void Latch_ID_EXE::reset_new()
{
    m_newpc_new = 0;
    m_rs_new = 0;
    m_rt_new = 0;
    m_rd_new = 0;
    m_opcode_new = 0;
    m_val_new = 0;
    m_opA_new = 0;
    m_opB_new = 0; 
}

void Latch_ID_EXE::reset_old()
{
    m_newpc_old = 0;
    m_rs_old = 0;
    m_rt_old = 0;
    m_rd_old = 0;
    m_opcode_old = 0;
    m_val_old = 0;
    m_opA_old = 0;
    m_opB_old = 0;  
}

void Latch_ID_EXE::push_opcode(const inst& i)
{ m_opcode_new = i; }
void Latch_ID_EXE::push_rs(const u_int32_t& rs)
{ m_rs_new = rs; }
void Latch_ID_EXE::push_rt(const u_int32_t& rt)
{ m_rt_new = rt; }
void Latch_ID_EXE::push_rd(const u_int32_t& rd)
{ m_rd_new = rd; }
void Latch_ID_EXE::push_opA(const u_int32_t& opA)
{ m_opA_new = opA; }
void Latch_ID_EXE::push_opB(const u_int32_t& opB)
{ m_opB_new = opB; }
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
u_int32_t Latch_ID_EXE::pull_opA() const
{ return m_opA_old; }
u_int32_t Latch_ID_EXE::pull_opB() const
{ return m_opB_old; }
u_int32_t Latch_ID_EXE::pull_val() const
{ return m_val_old; }
u_int32_t Latch_ID_EXE::pull_newpc() const
{ return m_newpc_old; }

