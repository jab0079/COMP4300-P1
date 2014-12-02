#ifndef INST_LI_HH
#define INST_LI_HH
/*
 * 
 *      Inst_LI.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the interface for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for LI is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Instruction.hh"
#include "Utilities.hh"
#include "scoSim.hh" //ScoreboardSimulator.hh

class Inst_LI : public Instruction
{
    public:
        Inst_LI(inst the_instruction);
        virtual ~Inst_LI();
        
        //Implemented stage methods
        virtual void decode(ScoreboardSimulator& sim);
        virtual void execute(ScoreboardSimulator& sim);
        virtual void memory(ScoreboardSimulator& sim);
        virtual void write_back(ScoreboardSimulator& sim);
                
    protected:
        
    private:
        
};


#endif //INST_LI_HH

