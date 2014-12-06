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
#include "Utilities.hh"
#include "Instruction.hh"
#include "FunctionalUnit.hh"

class Instruction;

struct InstructionStatus
{
    u_int32_t instr_id;
    SCO_CYCLE curr_status; // current SCO_CYCL
    int32_t issue,         // store cycle# for each stage
            read_op, 
            exe_complete, 
            write_result;
};

struct FunctionalUnitStatus
{
    bool busy,
         src1_rdy,
         src2_rdy;
    u_int32_t instr_id;  // instead of opcode?
    u_int8_t dest,
             src1,
             src2;
    FU_ID fu_src1,
          fu_src2;
};

class Scoreboard 
{
    public:
        
        //Constructors / Destructor -------------------------------------------
        Scoreboard();
        Scoreboard(const Scoreboard& other);
        virtual ~Scoreboard();
        
        // Methods ------------------------------------------------------------
        virtual void print_scoreboard();
        
        virtual void add_instr_status(const u_int32_t& id, const int32_t& cycle); 
        
        virtual bool check_FU_busy(FU_ID fu_id);
        virtual bool check_WAW(u_int8_t r_dest);
        virtual bool check_WAR(FU_ID fu_id, u_int8_t r_dest);
        virtual bool check_reg_result(u_int8_t r_dest_num, const FU_ID& fu_id);
        virtual bool check_range(u_int8_t r_num) const;
        virtual void update_fu_status_flags(const FU_ID& fu_id);
        virtual void reset_fu_status(const FU_ID& fu_id);
        
        // Gets and Sets-------------------------------------------------------
        virtual void set_instr_status(const u_int32_t& id, const SCO_CYCLE& new_status, const int32_t& cycle);
        virtual void set_fu_status(const FU_ID& fu_id, const Instruction& instr);
        virtual void set_reg_result(const u_int8_t& r_dest_num, const FU_ID& fu_id);
        
        virtual InstructionStatus get_instr_status(const u_int32_t& inst_id) const;
        virtual FunctionalUnitStatus get_fu_status(const FU_ID& fu_id) const;
        virtual FU_ID get_reg_result(const u_int8_t& r_dest_num) const;
        
    protected:
        
    private:
        //std::vector<FunctionalUnit*> funct_units;
      
        std::vector<InstructionStatus> instr_status;
        FunctionalUnitStatus fu_status[FU_COUNT];
        FU_ID reg_status[REGISTER_COUNT + FLOATING_POINT_REGISTERS];
        
};




#endif