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
#include <queue>
#include "Instruction.hh"

class Instruction;

class FunctionalUnit
{
    public:
        FunctionalUnit(FU_ID fu_type, u_int32_t stages);
        FunctionalUnit(const FunctionalUnit& other);
        virtual ~FunctionalUnit();
        
        virtual void issue(const Instruction& i);
        virtual u_int32_t read_operands();
        virtual u_int32_t execute(bool pushExecuteBuffer);
        virtual u_int32_t write_back();
        
        virtual void setFU_ID(FU_ID fu_type);
        virtual FU_ID getFU_ID() const;
        
        virtual u_int32_t getInstr_id() const;
        virtual u_int32_t getInstr_id_issued() const;
        virtual u_int32_t getInstr_id_executebuffer() const;
        virtual u_int32_t getInstr_id_writeback() const;
        virtual u_int8_t getInstr_writeback_dest() const;
        
    protected:
        
    private:
        
        FU_ID m_id;
        Instruction* m_issued_inst;
        u_int32_t m_stagesLeft;
        u_int32_t m_numstages;
        Instruction* m_execute_buffer;
        std::queue<Instruction*> m_stage_queue;
        Instruction* m_write_back;
        
        
};

#endif //FUNCTIONAL_UNIT_HH