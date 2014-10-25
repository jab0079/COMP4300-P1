#ifndef LATCH_ID_EXE_HH
#define LATCH_ID_EXE_HH
/*
 * 
 *      Latch_ID_EXE.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          Class defines the specific structure for the
 *          Latch object found between the decode and the
 *          execution cycles of a pipelined simulator
 * 
 *      Change Log:
 *          10/24/14 - Added reset method
 *          10/20/14 - Added operand A, B
 *          10/18/14 - Created initial implementation for
 *                      latch with corresponding push/pull methods
 *          10/14/14 - Initial creation
 * 
 * 
 */

#include <iostream>

#include "Latch.hh"

class Latch_ID_EXE : public Latch
{
    public:
      Latch_ID_EXE();
      virtual ~Latch_ID_EXE();
      
      virtual void update();
      virtual void reset();
      
      virtual void push_opcode(const inst& i);
      virtual void push_rs(const u_int32_t& rs);
      virtual void push_rt(const u_int32_t& rt);
      virtual void push_rd(const u_int32_t& rd);
      virtual void push_opA(const u_int32_t& opA);
      virtual void push_opB(const u_int32_t& opB);
      virtual void push_val(const u_int32_t& val);
      virtual void push_newpc(const u_int32_t& newpc);
      
      virtual inst pull_opcode() const;
      virtual u_int32_t pull_rs() const;
      virtual u_int32_t pull_rt() const;
      virtual u_int32_t pull_rd() const;
      virtual u_int32_t pull_opA() const;
      virtual u_int32_t pull_opB() const;
      virtual u_int32_t pull_val() const;
      virtual u_int32_t pull_newpc() const;
      
      
      
    protected:
      
      
    private:
      //opcode
      inst m_opcode_old;
      inst m_opcode_new;
      //rs, rt, rd
      u_int32_t m_rs_old, m_rt_old, m_rd_old;
      u_int32_t m_rs_new, m_rt_new, m_rd_new;
      //Operand A, B?
      u_int32_t m_opA_old, m_opB_old;
      u_int32_t m_opA_new, m_opB_new;
      //immediate or offset
      u_int32_t m_val_old;
      u_int32_t m_val_new;
      //new PC
      u_int32_t m_newpc_old;
      u_int32_t m_newpc_new;
      
};

#endif
