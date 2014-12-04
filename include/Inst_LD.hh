#ifndef INST_LD_HH
#define INST_LD_HH
/*
 * 
 *      Inst_LD.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the interface for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for LD is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Instruction.hh"
#include "Utilities.hh"
#include "scoSim.hh" //ScoreboardSimulator.hh

class Inst_LD : public Instruction
{
    public:
        Inst_LD(inst the_instruction);
        virtual ~Inst_LD();
        
        //Implemented stage methods
        virtual void decode(ScoreboardSimulator& sim);
        virtual void fetch_operands(ScoreboardSimulator& sim);
        virtual void execute(ScoreboardSimulator& sim);
        virtual void memory(ScoreboardSimulator& sim);
        virtual void write_back(ScoreboardSimulator& sim);
                
    protected:
        
    private:
        u_int8_t m_rdest, m_rsrc1;
        int32_t m_aluout, m_opA;
        int32_t m_value;
        float m_mdr;
        
};


#endif //INST_LD_HH

