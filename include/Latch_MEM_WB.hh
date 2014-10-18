#ifndef LATCH_MEM_WB_HH
#define LATCH_MEM_WB_HH
/*
 * 
 *      Latch_MEM_WB.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          Class defines the specific structure for the
 *          Latch object found between the memory and the
 *          write-back cycles of a pipelined simulator
 * 
 *      Change Log:
 *          10/18/14 - Added definitions for opcode, rd,
 *                      aluout, mdr and corresponding push/pulls
 *          10/14/14 - Initial creation
 * 
 * 
 */

#include <iostream>

#include "Utilities.hh"
#include "Latch.hh"

class Latch_MEM_WB : public Latch
{
    public:
      Latch_MEM_WB();
      virtual ~Latch_MEM_WB();
      
      virtual void update();
      
      virtual void push_opcode(const inst& opcode);
      virtual void push_mdr(const u_int32_t& mdr);
      virtual void push_aluout(const u_int32_t& aluout);
      virtual void push_rd(const u_int32_t& rd);
      
      virtual inst pull_opcode() const;
      virtual u_int32_t pull_mdr() const;
      virtual u_int32_t pull_aluout() const;
      virtual u_int32_t pull_rd() const;
      
    protected:
      
    private:
      //opcode
      inst m_opcode_old;
      inst m_opcode_new;
      //mdr
      u_int32_t m_mdr_old;
      u_int32_t m_mdr_new;
      //operand B?
      //ALUout
      u_int32_t m_aluout_old;
      u_int32_t m_aluout_new;
      //rd
      u_int32_t m_rd_old;
      u_int32_t m_rd_new;
      
};

#endif
