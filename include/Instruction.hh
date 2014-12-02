#ifndef INSTRUCTION_HH
#define INSTRUCTION_HH
/*
 * 
 *      Instruction.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This class defines the interface for all instructions
 *          that are used in a simulator. The simulator will contain
 *          a list of these objects and these objects will manipulate
 *          the simulator's properties based on how  they have implemented
 *          each of the stages. (For now only used for Scoreboard Simulator).
 * 
 *      Change Log:
 *          12/2/14 - Initial creation
 * 
 * 
 */
#include "Utilities.hh"

class Instruction
{
    public:
        Instruction(inst the_instruction);
        virtual ~Instruction();
        
        //Pure virtual stage methods
        virtual void decode() = 0;
        virtual void execute() = 0;
        virtual void memory() = 0;
        virtual void write_back() = 0;
        
        virtual inst getInstruction() const;
        
    protected:
        
    private:
        inst m_instruction;
        
};


#endif //INSTRUCTION_HH
