#ifndef SCOREBOARD_HH
#define SCOREBOARD_HH
/*
 * 
 *      Scoreboard.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This class defines the interface for the Scoreboard used 
 *          in the scoSim Simulator.
 * 
 *      Change Log:
 *          12/3/14 - Initial Creation
 * 
 * 
 */

#include <iostream>
#include <vector>
#include "scoSim.hh"
#include "Utilities.hh"
#include "Instruction.hh"
#include "FunctionalUnit.hh"

static const u_int32_t FU_COUNT = 4;

struct InstructionStatus
{
    u_int32_t curr_status,    // current SCO_CYCL
              issue,          // store cycle# for each stage
              read_op, 
              exe_complete, 
              write_result;
};

struct FunctionalUnitStatus
{
    bool busy,
         src1_rdy,
         src2_rdy;
    u_int32_t instr_id;        // instead of opcode?
    u_int8_t dest,
             src1,
             src2;
    int8_t fu_src1,
           fu_src2;
};

class Scoreboard 
{
    public:
        
        //Constructors / Destructor -------------------------------------------
        Scoreboard();
        virtual ~Scoreboard();
        
        // Methods ------------------------------------------------------------
        virtual void add_instr_status(const Instruction& instr); 
        
        virtual bool check_FU_busy(int8_t fu_id, Instruction& instr);
        virtual bool check_WAW(int8_t fu_id, u_int8_t r_dest);
        virtual bool check_reg_result(u_int8_t r_dest_num);
        virtual bool check_reg_d_result(u_int8_t r_dest_num);
        
        // Gets and Sets-------------------------------------------------------
        virtual void set_instr_status(const u_int32_t& new_status, const u_int32_t& cycle);
        virtual void set_fu_status(const int8_t& fu_id, const Instruction& instr);
        virtual void set_reg_result(const u_int8_t& r_dest_num, const int8_t& fu_id);
        virtual void set_reg_d_result(const u_int8_t& r_dest_num, const int8_t& fu_id);
        
        virtual InstructionStatus get_instr_status(const Instruction& instr) const;
        virtual FunctionalUnitStatus get_fu_status(const int8_t& fu_id) const;
        virtual int8_t get_reg_result(const u_int8_t& r_dest_num) const;
        virtual int8_t get_reg_d_result(const u_int8_t& r_dest_num) const;
        
    protected:
       
        //Members -------------------------------------------------------------
       
      enum SCO_CYCLE
        {
          SCO_ISSUE,
          SCO_READ_OP,
          SCO_EXE_COMPLETE,
          SCO_WRITE_RESULT,
        };
        
    private:
        //std::vector<FunctionalUnit*> funct_units;
      
        std::vector<InstructionStatus> instr_status;
        FunctionalUnitStatus fu_status[FU_COUNT];
        int8_t reg_status[REGISTER_COUNT];
        int8_t reg_d_status[FLOATING_POINT_REGISTERS];
        
};




#endif