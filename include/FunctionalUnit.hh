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

enum FU_ID
{
    FU_INTEGER,
    FU_FP_ADDER,
    FU_FP_MULT,
    FU_MEMORY,
    FU_UNDEFINED
};

class Instruction;

class FunctionalUnit
{
    public:
        FunctionalUnit(FU_ID fu_type);
        FunctionalUnit(const FunctionalUnit& other);
        virtual ~FunctionalUnit();
        
        virtual void issue(const Instruction& i);
        virtual void setFU_ID(FU_ID fu_type);
        virtual FU_ID getFU_ID() const;
        
    protected:
    private:
        
        Instruction* m_instruction;
        FU_ID m_id;
        
//         //Busy, Op, Fi, Fj, Fk, Qj, Qk, Rj, Rk
//         bool m_busy;    //Is functional unit busy 
//         bool m_rj;      //Is left operand ready   
//         bool m_rk;      //Is right operand ready
//         u_int8_t m_op;  //Operation
//         u_int8_t m_fi;  //Destination
//         u_int8_t m_fj;  //Left Operand
//         u_int8_t m_fk;  //Right Operand
//         FU_ID m_qj;     //Functional Unit producing left operand
//         FU_ID m_qk;     //Functional Unit producing right operand
};

#endif //FUNCTIONAL_UNIT_HH