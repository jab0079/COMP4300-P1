#ifndef SCOSIM_HH
#define SCOSIM_HH
/*
 * 
 *      scoSim.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This class defines the interface for the Scoreboard Simulator
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */

#include<iostream>

#include "Simulator.hh"
#include "Utilities.hh"
#include "Instruction.hh"
#include "FunctionalUnit.hh"
#include "Scoreboard.hh"


class FunctionalUnit;
class Instruction;
class Scoreboard;

class ScoreboardSimulator : public Simulator
{
    public:
        ScoreboardSimulator(MemSys* mem);
        virtual ~ScoreboardSimulator();
        
        virtual void run();
        virtual void issue();
        virtual void read_operands();
        
        //Method to set the value of a register
        virtual void setRegister(const u_int8_t& regnum, const reg& val);
        //Method for setting a floating point register
        virtual void setFPRegister(const u_int8_t& regnum, const reg_d& val);
        //Method for setting usermode flag
        virtual void setUserMode(const bool& isInUserMode);
        
        //Method to get the value of a register
        virtual reg getRegister(const u_int8_t& regnum) const;
        //Method to get the value of a floating point register
        virtual reg_d getFPRegister(const u_int8_t& regnum) const;
        //Method to determine whether or not simulator is in user mode
        virtual bool isInUserMode() const;
        
    protected:
        
    private:
        FU_ID getRespectiveFU(const Instruction& i) const;
        void read_operands_helper(FunctionalUnit* fu);

        //Registers
        reg m_register[REGISTER_COUNT]; //Utilities.hh
        reg_d m_register_d[FLOATING_POINT_REGISTERS]; //Utilities.hh

        Scoreboard* m_scob;
        
        FunctionalUnit* m_integer_fu;
        FunctionalUnit* m_fpadd_fu;
        FunctionalUnit* m_fpmult_fu;
        FunctionalUnit* m_mem_fu;
        
        bool m_usermode;
        Instruction* m_fetch_buffer;

};


#endif //SCOSIM_HH
