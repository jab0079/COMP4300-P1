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
  // initialize fu_status & reg_status 
  u_int32_t i;
  for(i = 0; i < FU_COUNT; i++)
  {
    FunctionalUnitStatus fu_stat;
    fu_stat.busy = false;
    fu_stat.src1_rdy = false;
    fu_stat.src2_rdy = false;
    fu_stat.instr_id = -1;
    fu_stat.dest = 0;
    fu_stat.src1 = 0;
    fu_stat.src2 = 0;
    fu_status[i] = fu_stat;
  }
  
  for(i = 0; i < REGISTER_COUNT + FLOATING_POINT_REGISTERS; i++)
  {
    reg_status[i] = FU_UNDEFINED;
  }
}

Scoreboard::~Scoreboard()
{
    
}

void Scoreboard::add_instr_status(const u_int32_t& id, const int32_t& cycle)
{
  InstructionStatus instr_stat;
  
  instr_stat.instr_id = id;
  instr_stat.curr_status = SCO_ISSUE;
  instr_stat.issue = cycle;
  instr_stat.read_op = -1;
  instr_stat.exe_complete = -1;
  instr_stat.write_result = -1;
  
  instr_status.push_back(instr_stat);
}

bool Scoreboard::check_FU_busy(FU_ID fu_id)
{
  return fu_status[fu_id].busy;
}

bool Scoreboard::check_WAW(u_int8_t r_dest)
{
  // check if any other funct unit has the same r_dest
  if (reg_status[r_dest] != FU_UNDEFINED)
    return true;
  
  // otherwise return false for no hazard
  return false;
}

bool Scoreboard::check_WAR(FU_ID fu_id, u_int8_t r_dest)
{
  // check if any other funct unit has the same r_dest as a src reg
  u_int32_t i;
  for(i = 0; i < FU_COUNT; i++)
  {
    if (fu_status[i].src1 == r_dest || fu_status[i].src2 == r_dest)
      if (i != fu_id)
        return true;
  }
  
  // otherwise return false for no hazard
  return false;
}

bool Scoreboard::check_reg_result(u_int8_t r_dest_num)
{
  // if reg_status not set, return true since reg is available
  if (reg_status[r_dest_num] == FU_UNDEFINED)
    return true;
  
  // otherwise it is being used by a fu, so return false
  return false;
}


void Scoreboard::set_instr_status(const u_int32_t& id, const SCO_CYCLE& new_status, const int32_t& cycle)
{
  switch(new_status)
  {
    case SCO_ISSUE:
      instr_status.at(id).issue = cycle;
      break;
    case SCO_READ_OP:
      instr_status.at(id).read_op = cycle;
      break;
    case SCO_EXE_COMPLETE:
      instr_status.at(id).exe_complete = cycle;
      break;
    case SCO_WRITE_RESULT:
      instr_status.at(id).write_result = cycle;
      break;
    default:
      break;
  }
  
  instr_status.at(id).curr_status = new_status;
}

void Scoreboard::set_fu_status(const FU_ID& fu_id, const Instruction& instr)
{
  FunctionalUnitStatus fu_stat = fu_status[fu_id];
  
  // get opcode & check if corresponding fu is busy
  fu_stat.instr_id = instr.getInstr_id();
  fu_stat.busy = true;
  
  // set dest & src reg numbers
  fu_stat.dest = instr.getDestinationRegister();
  fu_stat.src1 = instr.getSourceRegister1();
  fu_stat.src2 = instr.getSourceRegister2();
  
  // update fu src reg flags
  update_fu_status_flags(fu_id);
  
  fu_status[fu_id] = fu_stat;
}

void Scoreboard::update_fu_status_flags(const FU_ID& fu_id)
{
  FunctionalUnitStatus fu_stat = fu_status[fu_id];

  // check src reg results & set fu if not ready
  fu_stat.src1_rdy = check_reg_result(fu_stat.src1);
  if (!fu_stat.src1_rdy)
    fu_stat.fu_src1 = get_reg_result(fu_stat.src1);
    
  fu_stat.src2_rdy = check_reg_result(fu_stat.src2);
  if (!fu_stat.src2_rdy)
    fu_stat.fu_src2 = get_reg_result(fu_stat.src2);
  
  fu_status[fu_id] = fu_stat;
}

void Scoreboard::set_reg_result(const u_int8_t& r_dest_num, const FU_ID& fu_id)
{
  reg_status[r_dest_num] = fu_id;
}


InstructionStatus Scoreboard::get_instr_status(const Instruction& instr) const
{
  return instr_status[instr.getInstr_id()];
}

FunctionalUnitStatus Scoreboard::get_fu_status(const FU_ID& fu_id) const
{
  return fu_status[fu_id];
}

FU_ID Scoreboard::get_reg_result(const u_int8_t& r_dest_num) const
{
  return reg_status[r_dest_num];
}



