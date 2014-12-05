#ifndef FUNCTIONAL_UNIT_HH
#define FUNCTIONAL_UNIT_HH
/*
 * 
 *      FunctionalUnit.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This class defines the interface for all instructions
 *          that are used in a functional unit. The functional units
 *          are the objects that are issued instructions in the
 *          ScoreboardSimulator. It contains an internal pipeline
 *          as well as statuses describing properties about the
 *          current instruction it is executing.
 * 
 *      Change Log:
 *          12/2/14 - Initial creation
 * 
 * 
 */
#include <iostream>
#include "Instruction.hh"

class Instruction;

class FunctionalUnit
{
    public:
        FunctionalUnit(FU_ID fu_type, u_int32_t stages);
        FunctionalUnit(const FunctionalUnit& other);
        virtual ~FunctionalUnit();
        
        virtual void issue(const Instruction& i);
        virtual void read_operands();
        virtual bool execute();
        virtual void write_back();
        virtual void setFU_ID(FU_ID fu_type);
        virtual FU_ID getFU_ID() const;
        virtual u_int32_t getInstr_id() const;
        
    protected:
        
    private:
        
        FU_ID m_id;
        Instruction* m_instruction;
        u_int32_t m_stagesLeft;
        u_int32_t m_numstages;
        
};

#endif //FUNCTIONAL_UNIT_HH