/*
 * 
 *      Scoreboard.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the Scoreboard interface
 * 
 *      Change Log:
 *          12/3/14 - Initial creation
 * 
 * 
 */

#include "Scoreboard.hh"

Scoreboard::Scoreboard()
{
  // TODO initialize instr_status, fu_status, & reg_status 
  u_int32_t i;
  for(i = 0; i < FU_COUNT; i++)
  {
    FunctionalUnitStatus fu_stat;
    fu_stat.busy = false;
    fu_stat.busy = false;
    fu_stat.busy = false;
    fu_stat.instr_id = -1;
    
    fu_status[i] = fu_stat;
  }
  
  for(i = 0; i < REGISTER_COUNT; i++)
  {
    reg_status[i] = -1;
  }
  
  for(i = 0; i < FLOATING_POINT_REGISTERS; i++)
  {
    reg_d_status[i] = -1;
  }
}

Scoreboard::~Scoreboard()
{
    
}

void Scoreboard::add_instr_status(const Instruction& instr)
{
  InstructionStatus instr_stat;
  
  
}

bool Scoreboard::check_FU_busy(int8_t fu_id, Instruction& instr)
{
  return false;
}

bool Scoreboard::check_WAW(int8_t fu_id, u_int8_t r_dest)
{
  return false;
}

bool Scoreboard::check_reg_result(u_int8_t r_dest_num)
{
  // if reg_status not set, return true since reg is available
  if (reg_status[r_dest_num] == -1)
    return true;
  // otherwise it is being used by a fu, so return false
  return false;
}

bool Scoreboard::check_reg_d_result(u_int8_t r_dest_num)
{
  // if reg_status not set, return true since reg is available
  if (reg_d_status[r_dest_num] == -1)
    return true;
  // otherwise it is being used by a fu, so return false
  return false;
}


void Scoreboard::set_instr_status(const u_int32_t& new_status, const u_int32_t& cycle)
{
  
}

void Scoreboard::set_fu_status(const int8_t& fu_id, const Instruction& instr)
{
  FunctionalUnitStatus fu_stat = fu_status[fu_id];
  
  // get opcode & check if corresponding fu is busy
  fu_stat.instr_id = instr.getInstr_id();
  fu_stat.busy = true;
  
  // set dest & src reg numbers
  fu_stat.dest = instr.getDestinationRegister();
  fu_stat.src1 = instr.getSourceRegister1();
  fu_stat.src2 = instr.getSourceRegister2();
  
  // check src reg results & set fu if not ready
  fu_stat.src1_rdy = check_reg_result(fu_stat.src1);
  if (!fu_stat.src1_rdy)
  {
    if (instr.getIsFP())
      fu_stat.fu_src1 = get_reg_d_result(fu_stat.src1);
    else 
      fu_stat.fu_src1 = get_reg_result(fu_stat.src1);
  }
    
  fu_stat.src2_rdy = check_reg_result(fu_stat.src2);
  if (!fu_stat.src2_rdy)
  {
    if (instr.getIsFP())
      fu_stat.fu_src2 = get_reg_d_result(fu_stat.src2);
    else 
      fu_stat.fu_src2 = get_reg_result(fu_stat.src2);
  }
}

void Scoreboard::set_reg_result(const u_int8_t& r_dest_num, const int8_t& fu_id)
{
  reg_status[r_dest_num] = fu_id;
}

void Scoreboard::set_reg_d_result(const u_int8_t& r_dest_num, const int8_t& fu_id)
{
  reg_d_status[r_dest_num] = fu_id;
}
 

InstructionStatus Scoreboard::get_instr_status(const Instruction& instr) const
{
  return instr_status[instr.getInstr_id()];
}

FunctionalUnitStatus Scoreboard::get_fu_status(const int8_t& fu_id) const
{
  return fu_status[fu_id];
}

int8_t Scoreboard::get_reg_result(const u_int8_t& r_dest_num) const
{
  return reg_status[r_dest_num];
}

int8_t Scoreboard::get_reg_d_result(const u_int8_t& r_dest_num) const
{
  return reg_d_status[r_dest_num];
}


