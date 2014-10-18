#ifndef GENERALPURPOSEREGISTER_HH
#define GENERALPURPOSEREGISTER_HH
/*
 * 
 *      GeneralPurposeRegister.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This class defines the interface for the GeneralPurposeRegister Simulator
 * 
 *      Change Log:
 *          10/18/14 - Added sepearate methods for each instruction and
 *                      for fetch and decode (to assist with pipelining).
 *                      Also moved decodeInstr to the 'private' field.
 * 			10/14/14 - Added latches to prepare for pipelining
 * 	    	10/3/14 - Added Register Constants and decodeInstr method
 *          9/29/14 - Initial Creation
 * 
 * 
 */

#include<iostream>
#include<bitset>

#include "Simulator.hh"
#include "Utilities.hh"

#include "Latch_IF_ID.hh"
#include "Latch_ID_EXE.hh"
#include "Latch_EXE_MEM.hh"
#include "Latch_MEM_WB.hh"

static const u_int32_t REGISTER_COUNT = 32;
static const u_int32_t REG_VAL_1 = 2;	// Register $2 = $v0 from MIPS
static const u_int32_t REG_ARG_1 = 4;	// Register $4 = $a0 from MIPS
static const u_int32_t REG_ARG_2 = 5;	// Register $5 = $a1 from MIPS

class GeneralPurposeRegister : public Simulator
{
    public:
        GeneralPurposeRegister(MemSys* mem);
        virtual ~GeneralPurposeRegister();
        
        virtual void run();
                
    protected:
        reg m_register[REGISTER_COUNT]; //Utilities.hh
        Latch_IF_ID* m_if_id;
        Latch_ID_EXE* m_id_exe;
        Latch_EXE_MEM* m_exe_mem;
        Latch_MEM_WB* m_mem_wb;
        
        virtual void gpr_fetch(const CYCLE_DESCRIPTOR& c);
        virtual void gpr_decode(const CYCLE_DESCRIPTOR& c);
        
        virtual void gpr_addi(const CYCLE_DESCRIPTOR& c);
        virtual void gpr_b(const CYCLE_DESCRIPTOR& c);
        virtual void gpr_beqz(const CYCLE_DESCRIPTOR& c);
        virtual void gpr_bge(const CYCLE_DESCRIPTOR& c);
        virtual void gpr_bne(const CYCLE_DESCRIPTOR& c);
        virtual void gpr_la(const CYCLE_DESCRIPTOR& c);
        virtual void gpr_lb(const CYCLE_DESCRIPTOR& c);
        virtual void gpr_li(const CYCLE_DESCRIPTOR& c);
        virtual void gpr_subi(const CYCLE_DESCRIPTOR& c);
        virtual void gpr_syscall(const CYCLE_DESCRIPTOR& c);
        
    private:
      
        virtual int32_t decodeInstr(const u_int32_t& instr, const u_int8_t& num_bits);

};


#endif //GENERALPURPOSEREGISTER_HH
