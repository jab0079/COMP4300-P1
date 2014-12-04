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

#include "scoSim.hh"
#include "MemSys.hh"
#include "Utilities.hh"
#include <bitset>

class ScoreboardSimulator;

class Instruction
{
    public:
        Instruction(inst the_instruction);
        Instruction(const Instruction& other);
        virtual ~Instruction();
        
        //Pure virtual stage methods
        virtual void decode(ScoreboardSimulator& sim) = 0;
        virtual void fetch_operands(ScoreboardSimulator& sim) = 0;
        virtual void execute(ScoreboardSimulator& sim) = 0;
        virtual void memory(ScoreboardSimulator& sim) = 0;
        virtual void write_back(ScoreboardSimulator& sim) = 0;
        
        virtual inst getInstruction() const;
        virtual u_int8_t getDestinationRegister() const;
        virtual u_int8_t getSourceRegister1() const;
        virtual u_int8_t getSourceRegister2() const;
        virtual u_int8_t getMDR() const;
        virtual float getMDR_FP() const;
        virtual int32_t getALUOUT() const;
        virtual float getALUOUT_FP() const;
        virtual int32_t getOPA() const;
        virtual float getOPA_FP() const;
        virtual int32_t getOPB() const;
        virtual float getOPB_FP() const;
        virtual int32_t getValue() const;
        
    protected:
        int32_t decodeInstr(const u_int32_t& instr, const u_int8_t& num_bits);
        
        //Easier to just put these as protected members rather than have derived
        //classes call accessor functions to get to these...
        u_int8_t m_dest;
        u_int8_t m_rsrc1;
        u_int8_t m_rsrc2;
        u_int8_t m_mdr;
        float m_mdr_fp;
        
        int32_t m_aluout, m_opA, m_opB, m_value;
        float m_aluout_fp, m_opA_fp, m_opB_fp;
        
    private:
        inst m_instruction;
        
};


#endif //INSTRUCTION_HH
