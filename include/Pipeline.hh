#ifndef PIPELINE_HH
#define PIPELINE_HH
/*
 * 
 *      Pipeline.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This class defines the interface for the Pipeline Simulator
 * 
 *      Change Log:
 *          10/26/14 - Added trapped member for exceptions like syscalls
 *          10/24/14 - Added methods to reset latches and start pipeline
 *          10/18/14 - Added sepearate methods for each instruction and
 *                      for fetch and decode (to assist with pipelining).
 *                      Also moved decodeInstr to the 'private' field.
 *          10/14/14 - Added latches to prepare for pipelining
 *          10/3/14 - Added Register Constants and decodeInstr method
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

class Pipeline : public Simulator
{
    public:
        Pipeline(MemSys* mem);
        virtual ~Pipeline();
        
        virtual void run();
        
                
    protected:
        reg m_register[REGISTER_COUNT]; //Utilities.hh
        bool m_usermode;
        bool m_trapped;
        Latch_IF_ID* m_if_id;
        Latch_ID_EXE* m_id_exe;
        Latch_EXE_MEM* m_exe_mem;
        Latch_MEM_WB* m_mem_wb;
        
        
        virtual void gpr_fetch();
        virtual void gpr_decode();
        
        virtual void gpr_add(const CYCLE_DESCRIPTOR& c);
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
        virtual void gpr_nop(const CYCLE_DESCRIPTOR& c);
        
        virtual void syscall_exception();
        
        virtual void resetLatches();
        virtual void runPipeline();
        virtual void updateLatches();
        
        
    private:
        virtual bool isRtype(const u_int8_t& opcode);
        virtual void delegateCycle(const u_int8_t& opcode,
                                   const CYCLE_DESCRIPTOR& c_desc);
        virtual void helpUnexpDescr(const std::string& method, 
                                    const CYCLE_DESCRIPTOR& desc);
        virtual int32_t decodeInstr(const u_int32_t& instr, 
                                    const u_int8_t& num_bits);

};


#endif //PIPELINE_HH
