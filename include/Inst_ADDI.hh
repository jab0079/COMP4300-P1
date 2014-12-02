#ifndef INST_ADDI_HH
#define INST_ADDI_HH
/*
 * 
 *      Inst_ADDI.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the interface for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for ADDI is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Instruction.hh"
#include "Utilities.hh"
#include "scoSim.hh" //ScoreboardSimulator.hh

class Inst_ADDI : public Instruction
{
    public:
        Inst_ADDI(inst the_instruction);
        virtual ~Inst_ADDI();
        
        //Implemented stage methods
        virtual void decode(ScoreboardSimulator& sim);
        virtual void execute(ScoreboardSimulator& sim);
        virtual void memory(ScoreboardSimulator& sim);
        virtual void write_back(ScoreboardSimulator& sim);
                
    protected:
        
    private:
        u_int8_t m_rdest, m_rsrc1;
        int32_t m_value;
        int32_t m_aluout;
        
};


#endif //INST_ADDI_HH

