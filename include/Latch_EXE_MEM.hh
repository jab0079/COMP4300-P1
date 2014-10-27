#ifndef LATCH_EXE_MEM_HH
#define LATCH_EXE_MEM_HH
/*
 * 
 *      Latch_EXE_MEM.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          Class defines the specific structure for the
 *          Latch object found between the execution and the
 *          memory cycles of a pipelined simulator
 * 
 *      Change Log:
 *          10/24/14 - Added reset method
 *          10/20/14 - Added operand B
 *          10/18/14 - Created initial implementation for
 *                      latch with corresponding push/pull methods
 *          10/14/14 - Initial creation
 * 
 * 
 */

#include <iostream>

#include "Latch.hh"

class Latch_EXE_MEM : public Latch
{
    public:
      Latch_EXE_MEM();
      virtual ~Latch_EXE_MEM();
      
      virtual void update();
      virtual void reset();
      virtual void reset_old();
      virtual void reset_new();

      
      virtual void push_opcode(const inst& op);
      virtual void push_aluout(const u_int32_t& aluout);
      virtual void push_opB(const u_int32_t& opB);
      virtual void push_rd(const u_int32_t& rd);
      
      virtual inst pull_opcode() const;
      virtual u_int32_t pull_aluout() const;
      virtual u_int32_t pull_opB() const;
      virtual u_int32_t pull_rd() const;
      
    protected:
      
    private:
      //opcode
      inst m_opcode_old;
      inst m_opcode_new;
      //ALUout
      u_int32_t m_aluout_old;
      u_int32_t m_aluout_new;
      //OperandB
      u_int32_t m_opB_old;
      u_int32_t m_opB_new;
      //rd
      u_int32_t m_rd_old;
      u_int32_t m_rd_new;
      
};

#endif
