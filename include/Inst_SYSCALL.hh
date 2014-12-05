#ifndef INST_SYSCALL_HH
#define INST_SYSCALL_HH
/*
 * 
 *      Inst_SYSCALL.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the interface for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for SYSCALL is described in the MIPS architecture.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Instruction.hh"
#include "Utilities.hh"

class Inst_SYSCALL : public Instruction
{
    public:
        Inst_SYSCALL(inst the_instruction);
        Inst_SYSCALL(const Inst_SYSCALL& other);
        virtual ~Inst_SYSCALL();
        
        virtual Instruction* clone() const;
        
        //Implemented stage methods
        virtual void decode(ScoreboardSimulator& sim);
        virtual void fetch_operands(ScoreboardSimulator& sim);
        virtual void execute(ScoreboardSimulator& sim);
        virtual void memory(ScoreboardSimulator& sim);
        virtual void write_back(ScoreboardSimulator& sim);
                
    protected:
        
    private:
        
};


#endif //INST_SYSCALL_HH


