#ifndef INST_BEQZ_HH
#define INST_BEQZ_HH
/*
 * 
 *      Inst_BEQZ.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the interface for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for BEQZ is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Instruction.hh"
#include "Utilities.hh"

class Inst_BEQZ : public Instruction
{
    public:
        Inst_BEQZ(ScoreboardSimulator* simu, inst the_instruction);
        Inst_BEQZ(const Inst_BEQZ& other);
        virtual ~Inst_BEQZ();
        
        virtual Instruction* clone() const;
        
        //Implemented stage methods
        virtual void decode();
        virtual void fetch_operands();
        virtual void execute();
        virtual void memory();
        virtual void write_back();
                
    protected:
        
    private:
        
};


#endif //INST_BEQZ_HH

