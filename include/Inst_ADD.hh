#ifndef INST_ADD_HH
#define INST_ADD_HH
/*
 * 
 *      Inst_ADD.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the interface for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for ADD is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Instruction.hh"
#include "Utilities.hh"
#include "scoSim.hh" //ScoreboardSimulator.hh

class Inst_ADD : public Instruction
{
    public:
        Inst_ADD(inst the_instruction);
        virtual ~Inst_ADD();
        
        //Implemented stage methods
        virtual void decode();
        virtual void execute();
        virtual void memory();
        virtual void write_back();
                
    protected:
        
    private:
        inst m_instruction;
        
};


#endif //INST_ADD_HH


