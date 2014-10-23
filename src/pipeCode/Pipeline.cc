/*
 * 
 *      Pipeline.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the Pipeline Simulator
 * 
 *      Change Log:
 *          10/3/14 - Implemented all instructions
 *          9/29/14 - Initial Creation
 * 
 * 
 */
#include "Pipeline.hh"

Pipeline::Pipeline(MemSys* mem) 
: Simulator(mem)
{
  //instantiate latches
  m_if_id = new Latch_IF_ID();
  m_id_exe = new Latch_ID_EXE();
  m_exe_mem = new Latch_EXE_MEM();
  m_mem_wb = new Latch_MEM_WB();
}

Pipeline::~Pipeline()
{
  //destroy latches (SAFE_DELETE found in utilities.hh)
  SAFE_DELETE(m_if_id);
  SAFE_DELETE(m_id_exe);
  SAFE_DELETE(m_exe_mem);
  SAFE_DELETE(m_mem_wb);
}

void Pipeline::run()
{
    std::cout << "\tStarting GPR..." << std::endl;
    
    inst curr_inst = 0, opcode = 0;
    reg r_dest = 0, r_src1 = 0, r_src2 = 0;
    addr corrected_address;
    int32_t value = 0;
    
    bool user_mode = true;
    while (user_mode) 
    {
      // Read memory at PC  
      curr_inst = *((inst*)m_memory->read(m_pc,sizeof(inst)));
      
      // Get opcode and address
      opcode = curr_inst & 0xFF000000;
      opcode = opcode >> 24;    // Bitwise shift opcode down
      
      // Increment PC and IC
      m_ic++;
      m_pc += sizeof(inst);
      
      switch (opcode)
      {
        case GPR_ADDI:
            r_dest = curr_inst & 0x00F80000;            // Get destination register number
            r_dest = r_dest >> 19;
            r_src1 = curr_inst & 0x0007C000;            // Get source 1 register number
            r_src1 = r_src1 >> 14;
            value = decodeInstr(curr_inst, 14);         // Get signed immediate value
            
            m_register[r_dest] = m_register[r_src1] + value;    // Add r_src1 and immediate value, store in r_dest
            m_cycles += GPR_INST_SET_CYCLES[GPR_ADDI];      // Increment Cycles spent in execution
            break;
        
        case GPR_B:
            value = decodeInstr(curr_inst, 24) * 4;     // Get signed label offset value
            
            m_pc += value;                  // Branch
            m_cycles += GPR_INST_SET_CYCLES[GPR_B];     // Increment Cycles spent in execution
            break;
        
        case GPR_BEQZ:
            r_src1 = curr_inst & 0x00F80000;            // Get source 1 register number
            r_src1 = r_src1 >> 19;
            value = decodeInstr(curr_inst, 19) * 4;     // Get signed label offset value            
            
            if (m_register[r_src1] == 0)            // Branch if equals zero
            {
            m_pc += value;
            }
            m_cycles += GPR_INST_SET_CYCLES[GPR_BEQZ];      // Increment Cycles spent in execution
            break;
        
        case GPR_BGE:
            r_src1 = curr_inst & 0x00F80000;            // Get source 1 register number
            r_src1 = r_src1 >> 19;
            r_src2 = curr_inst & 0x0007C000;            // Get source 2 register number
            r_src2 = r_src2 >> 14;
            value = decodeInstr(curr_inst, 14) * 4;     // Get signed label offset value            
            
            if (m_register[r_src1] >= m_register[r_src2])   // Branch if greater than or equal
            {
            m_pc += value;
            }
            m_cycles += GPR_INST_SET_CYCLES[GPR_BGE];       // Increment Cycles spent in execution
            break;
        
        case GPR_BNE:
            r_src1 = curr_inst & 0x00F80000;            // Get source 1 register number
            r_src1 = r_src1 >> 19;
            r_src2 = curr_inst & 0x0007C000;            // Get source 2 register number
            r_src2 = r_src2 >> 14;
            value = decodeInstr(curr_inst, 14) * 4;     // Get label offset value           
            
            if (m_register[r_src1] != m_register[r_src2])   // Branch if not equal  
            {
            m_pc += value;
            }
            m_cycles += GPR_INST_SET_CYCLES[GPR_BNE];       // Increment Cycles spent in execution
            break;
        
        case GPR_LA:
            r_dest = curr_inst & 0x00F80000;            // Get destination register number
            r_dest = r_dest >> 19;
            value = decodeInstr(curr_inst, 19)  ;       // Get signed label offset value            
            
            m_register[r_dest] = value;             // Load signed label offset address into r_dest
            m_cycles += GPR_INST_SET_CYCLES[GPR_LA];        // Increment Cycles spent in execution
            break;
        
        case GPR_LB:
            r_dest = curr_inst & 0x00F80000;            // Get destination register number
            r_dest = r_dest >> 19;
            r_src1 = curr_inst & 0x0007C000;            // Get source 1 register number
            r_src1 = r_src1 >> 14;
            value = decodeInstr(curr_inst, 14);         // Get signed offset value
            
            // Correct address and read from memory into r_dest
            corrected_address = (MemSys::BaseUserDataSegmentAddress | m_register[r_src1]) + value;
            m_register[r_dest] = *((u_int8_t*)m_memory->read(corrected_address, sizeof(u_int8_t)));
            m_cycles += GPR_INST_SET_CYCLES[GPR_LB];        // Increment Cycles spent in execution
            break;
        
        case GPR_LI:
            r_dest = curr_inst & 0x00F80000;            // Get destination register number
            r_dest = r_dest >> 19;
            value = decodeInstr(curr_inst, 19);         // Get signed immediate value           
            
            m_register[r_dest] = value;             // Load signed immediate value into r_dest
            m_cycles += GPR_INST_SET_CYCLES[GPR_LI];        // Increment Cycles spent in execution
            break;
        
        case GPR_SUBI:
            r_dest = curr_inst & 0x00F80000;            // Get destination register number
            r_dest = r_dest >> 19;
            r_src1 = curr_inst & 0x0007C000;            // Get source 1 register number
            r_src1 = r_src1 >> 14;
            value = decodeInstr(curr_inst, 14);         // Get signed immediate value
            
            m_register[r_dest] = m_register[r_src1] - value;    // Subtract r_src1 and immediate value, store in r_dest
            m_cycles += GPR_INST_SET_CYCLES[GPR_SUBI];      // Increment Cycles spent in execution
            break;
        
        case GPR_SYSCALL:
        {
            u_int32_t sys_code = m_register[REG_VAL_1];     // Get syscall code
            switch(sys_code)
            {
                case SYSCALL_PRINT_STR:
                {
                    addr str_addr = MemSys::BaseUserDataSegmentAddress | m_register[REG_ARG_1]; // Corrected Address
                    u_int8_t letter = *((u_int8_t*)m_memory->read(str_addr, sizeof(u_int8_t))); // Read first char
                    std::string str;
                    str_addr++;
                    while (letter != '\0')          // Print each char in the string until NUL terminator
                    {
                    str += letter;
                    letter = *((u_int8_t*)m_memory->read(str_addr, sizeof(u_int8_t)));
                    str_addr++;
                    } 
                    
                    std::cout << str << std::endl; 
                }
                break;
        
        case SYSCALL_READ_STR:
        {
            std::string input;
            std::cin >> input;
            addr str_addr = MemSys::BaseUserDataSegmentAddress | m_register[REG_ARG_1]; // Corrected Address
            for (int i = 0; i < input.length(); i++)    // Write each char to memory
            {
              m_memory->write(str_addr, &input[i], sizeof(u_int8_t));
              str_addr++;
            }
            u_int8_t null_c = '\0';         // Add NUL terminator
            m_memory->write(str_addr, &null_c, sizeof(u_int8_t));
        }
                break;
        
        case SYSCALL_EXIT:
          user_mode = false;    // Exit user_mode
                break;
        
          default:
        break;
            }
        }
        m_cycles += GPR_INST_SET_CYCLES[GPR_SYSCALL];   // Increment Cycles spent in execution
        break;
        
    default:
      break;
      }
    }
    
    std::cout << "\tEnding GPR..." << std::endl;
}

int32_t Pipeline::decodeInstr(const u_int32_t& instr, const u_int8_t& num_bits)
{
    std::bitset<32> val32(instr);
    std::bitset<32> val;
    
    for (int i = 0; i < num_bits - 1; i++)  // Copy all bits up to msb
    val.set(i, val32[i]);
      
    for (int i = num_bits - 1; i < 32; i++) // Sign extend msb
        val.set(i, val32[num_bits - 1]);
    
    return val.to_ulong();
}

void Pipeline::gpr_fetch(const CYCLE_DESCRIPTOR& c_desc)
{
  inst curr_inst = 0;
  if (c_desc == CYCLE_FETCH)
  {
      // Read memory at PC  
      curr_inst = *((inst*)m_memory->read(m_pc,sizeof(inst)));
      //push instruction to latch
      m_if_id->pushInstruction(curr_inst);
  }
  else
  { //what i do with this
      helpUnexpDescr("GPR_FETCH()", c_desc);
  }
}

void Pipeline::gpr_decode(const CYCLE_DESCRIPTOR& c_desc)
{
  if (c_desc == CYCLE_DECODE)
  {
    //pull old instruction from latch
    inst old_instr = m_if_id->pullInstruction();
    //decode it into opcode
    u_int8_t opcode = ((old_instr & 0xFF000000) >> 24);
    m_id_exe->push_opcode(opcode);
    //increment pc and ic
    m_ic++;
    m_pc += sizeof(inst);
    //delegate other decoding pieces to instruction method...
    delegateCycle(opcode, CYCLE_DECODE);
  }
  else
  { //wat..?
      helpUnexpDescr("GPR_DECODE()", c_desc);
  }
}

void Pipeline::gpr_addi(const CYCLE_DESCRIPTOR& c_desc)
{
  inst curr_inst;
  u_int8_t r_dest, r_src1;
  u_int32_t value, op_A, op_B;
  
  switch (c_desc)
  {
    case CYCLE_DECODE:
      //pull old instruction again...(should still be the same...)
      curr_inst = m_if_id->pullInstruction();
      
      // Get and push r_dest number
      r_dest = (curr_inst & 0x00F80000) >> 19;
      m_id_exe->push_rd(r_dest); 
      
      // Get and push r_src1 number & operand A
      r_src1 = (curr_inst & 0x0007C000) >> 14;
      m_id_exe->push_rs(r_src1);
      m_id_exe->push_opA(m_register[r_src1]);
      
      // Get and push signed immediate value & operand B
      value = decodeInstr(curr_inst, 14);
      m_id_exe->push_val(value);
      m_id_exe->push_opB(value);
      break;
      
    case CYCLE_EXECUTE:
      // Forward opcode and r_dest
      m_exe_mem->push_opcode(m_id_exe->pull_opcode());
      m_exe_mem->push_rd(m_id_exe->pull_rd());
      
      // Get op A & B and add them, then push ALU_out
      op_A = m_id_exe->pull_opA();
      op_B = m_id_exe->pull_opB();
      m_exe_mem->push_aluout(op_A + op_B);
      break;
      
    case CYCLE_MEMORY:
      // Forward opcode, r_dest, and ALU_out    
      m_mem_wb->push_opcode(m_exe_mem->pull_opcode());
      m_mem_wb->push_rd(m_exe_mem->pull_rd());
      m_mem_wb->push_aluout(m_exe_mem->pull_aluout());
      break;
      
    case CYCLE_WRITEBACK:
      // Pull r_dest number & aluout, then write to r_dest
      m_register[m_mem_wb->pull_rd()] = m_mem_wb->pull_aluout();
      break;
      
    default:
      helpUnexpDescr("GPR_ADDI()", c_desc); //halp wat i do
      break;
  }
}

void Pipeline::gpr_b(const CYCLE_DESCRIPTOR& c_desc)
{
  inst curr_inst;
  u_int32_t value, aluout;
  
  if (c_desc == CYCLE_DECODE)
  {
      curr_inst = m_if_id->pullInstruction();
      // Get signed label offset value and calculate newpc
      value = decodeInstr(curr_inst, 24);
      aluout = m_pc + value * 4;
      
      // Branch (update PC)
      m_id_exe->push_newpc(aluout);
      m_pc = aluout;
      
      // Follow with NOP??
  }
  else
  { 
      helpUnexpDescr("GPR_B()", c_desc);
  }
}

void Pipeline::gpr_beqz(const CYCLE_DESCRIPTOR& c_desc)
{
  inst curr_inst;
  u_int8_t r_src1;
  u_int32_t value, aluout;
  
  if (c_desc == CYCLE_DECODE)
  {
      curr_inst = m_if_id->pullInstruction();
      // Get source 1 register number
      r_src1 = (curr_inst & 0x00F80000) >> 19;
      // Get signed label offset value and calculate newpc
      value = decodeInstr(curr_inst, 19);
      aluout = m_pc + value * 4;
            
      if (m_register[r_src1] == 0)
      { // Branch (update PC), if equals zero
    m_id_exe->push_newpc(aluout);
    m_pc = aluout;
      }
  }
  else
  { 
      helpUnexpDescr("GPR_BEQZ()", c_desc);
  }
  
}

void Pipeline::gpr_bge(const CYCLE_DESCRIPTOR& c_desc)
{
  inst curr_inst;
  u_int8_t r_src1, r_src2;
  u_int32_t value, aluout;
  
  if (c_desc == CYCLE_DECODE)
  {
      curr_inst = m_if_id->pullInstruction();
      // Get source 1 register number
      r_src1 = (curr_inst & 0x00F80000) >> 19;
      // Get source 2 register number
      r_src2 = (curr_inst & 0x0007C000) >> 14;
      // Get signed label offset value and calculate newpc
      value = decodeInstr(curr_inst, 19);
      aluout = m_pc + value * 4;
            
      if (m_register[r_src1] >= m_register[r_src2])
      { // Branch (update PC), if value of r_src1 >= r_src2
    m_id_exe->push_newpc(aluout);
    m_pc = aluout;
      }
  }
  else
  { 
      helpUnexpDescr("GPR_BGE()", c_desc);
  }
  
}

void Pipeline::gpr_bne(const CYCLE_DESCRIPTOR& c_desc)
{
  inst curr_inst;
  u_int8_t r_src1, r_src2;
  u_int32_t value, aluout;
  
  if (c_desc == CYCLE_DECODE)
  {
      curr_inst = m_if_id->pullInstruction();
      // Get source 1 register number
      r_src1 = (curr_inst & 0x00F80000) >> 19;
      // Get source 2 register number
      r_src2 = (curr_inst & 0x0007C000) >> 14;
      // Get signed label offset value and calculate newpc
      value = decodeInstr(curr_inst, 19);
      aluout = m_pc + value * 4;
            
      if (m_register[r_src1] != m_register[r_src2])
      { // Branch (update PC), if value of r_src1 != r_src2
    m_id_exe->push_newpc(aluout);
    m_pc = aluout;
      }
  }
  else
  { 
      helpUnexpDescr("GPR_BNE()", c_desc);
  }
}

void Pipeline::gpr_la(const CYCLE_DESCRIPTOR& c_desc)
{
  inst curr_inst;
  u_int8_t r_dest;
  u_int32_t value;
  
  switch (c_desc)
  {
    case CYCLE_DECODE:
      curr_inst = m_if_id->pullInstruction();
      
      // Get and push r_dest number
      r_dest = (curr_inst & 0x00F80000) >> 19;
      m_id_exe->push_rd(r_dest); 
      
      // Get and push signed label offset value
      value = decodeInstr(curr_inst, 19);
      m_id_exe->push_val(value);
      break;
      
    case CYCLE_EXECUTE:
      // Forward opcode, r_dest, and op_B (from value)
      m_exe_mem->push_opcode(m_id_exe->pull_opcode());
      m_exe_mem->push_rd(m_id_exe->pull_rd());
      m_exe_mem->push_opB(m_id_exe->pull_val());
      break;
      
    case CYCLE_MEMORY:
      // Forward opcode, r_dest, and op_B
      m_mem_wb->push_opcode(m_exe_mem->pull_opcode());
      m_mem_wb->push_rd(m_exe_mem->pull_rd());
      m_mem_wb->push_opB(m_exe_mem->pull_opB());
      break;
      
    case CYCLE_WRITEBACK:
      // Load signed label offset address into r_dest
      m_register[m_mem_wb->pull_rd()] = m_mem_wb->pull_opB();
      break;
      
    default:
      helpUnexpDescr("GPR_LA()", c_desc);
      break;
  }
}

void Pipeline::gpr_lb(const CYCLE_DESCRIPTOR& c_desc)
{
  inst curr_inst;
  u_int8_t r_dest, r_src1, mdr;
  u_int32_t value, aluout;
  
  switch (c_desc)
  {
    case CYCLE_DECODE:
      curr_inst = m_if_id->pullInstruction();
      
      // Get and push r_dest number
      r_dest = (curr_inst & 0x00F80000) >> 19;
      m_id_exe->push_rd(r_dest); 
      
      // Get and push r_src1 number
      r_src1 = (curr_inst & 0x0007C000) >> 14;
      m_id_exe->push_rs(r_src1);
      
      // Get and push signed offset value
      value = decodeInstr(curr_inst, 14);
      m_id_exe->push_val(value);
      break;
      
    case CYCLE_EXECUTE:
      // Forward opcode and r_dest
      m_exe_mem->push_opcode(m_id_exe->pull_opcode());
      m_exe_mem->push_rd(m_id_exe->pull_rd());
      
      // Correct target address and push to ALU_out
      aluout = (MemSys::BaseUserDataSegmentAddress | m_register[m_id_exe->pull_rs()]) + m_id_exe->pull_val();
      m_exe_mem->push_aluout(aluout);
      break;
      
    case CYCLE_MEMORY:
      // Forward opcode and r_dest
      m_mem_wb->push_opcode(m_exe_mem->pull_opcode());
      m_mem_wb->push_rd(m_exe_mem->pull_rd());
      
      // Read from memory at corrected target address into MDR
      mdr = *((u_int8_t*)m_memory->read(m_exe_mem->pull_aluout(), sizeof(u_int8_t)));
      m_mem_wb->push_mdr(mdr);
      break;
      
    case CYCLE_WRITEBACK:
      // Write MDR to r_dest
      m_register[m_mem_wb->pull_rd()] = m_mem_wb->pull_mdr();
      break;
      
    default:
      helpUnexpDescr("GPR_LB()", c_desc);
      break;
  }
}

void Pipeline::gpr_li(const CYCLE_DESCRIPTOR& c_desc)
{
  inst curr_inst;
  u_int8_t r_dest;
  u_int32_t value;
  
  switch (c_desc)
  {
    case CYCLE_DECODE:
      curr_inst = m_if_id->pullInstruction();
      
      // Get and push r_dest number
      r_dest = (curr_inst & 0x00F80000) >> 19;
      m_id_exe->push_rd(r_dest); 
      
      // Get and push signed immediate value
      value = decodeInstr(curr_inst, 19);
      m_id_exe->push_val(value);
      break;
      
    case CYCLE_EXECUTE:
      // Forward opcode, r_dest, and op_B (from imm value)
      m_exe_mem->push_opcode(m_id_exe->pull_opcode());
      m_exe_mem->push_rd(m_id_exe->pull_rd());
      m_exe_mem->push_opB(m_id_exe->pull_val());
      break;
      
    case CYCLE_MEMORY:
      // Forward opcode, r_dest, and op_B
      m_mem_wb->push_opcode(m_exe_mem->pull_opcode());
      m_mem_wb->push_rd(m_exe_mem->pull_rd());
      m_mem_wb->push_opB(m_exe_mem->pull_opB());
      break;
      
    case CYCLE_WRITEBACK:
      // Load signed label offset address into r_dest
      m_register[m_mem_wb->pull_rd()] = m_mem_wb->pull_opB();
      break;
      
    default:
      helpUnexpDescr("GPR_LI()", c_desc);
      break;
  }
}

void Pipeline::gpr_subi(const CYCLE_DESCRIPTOR& c_desc)
{
  inst curr_inst;
  u_int8_t r_dest, r_src1;
  u_int32_t value, op_A, op_B;
  
  switch (c_desc)
  {
    case CYCLE_DECODE:
      curr_inst = m_if_id->pullInstruction();
      
      // Get and push r_dest number
      r_dest = (curr_inst & 0x00F80000) >> 19;
      m_id_exe->push_rd(r_dest); 
      
      // Get and push r_src1 number & operand A
      r_src1 = (curr_inst & 0x0007C000) >> 14;
      m_id_exe->push_rs(r_src1);
      m_id_exe->push_opA(m_register[r_src1]);
      
      // Get and push signed immediate value & operand B
      value = decodeInstr(curr_inst, 14);
      m_id_exe->push_val(value);
      m_id_exe->push_opB(value);
      break;
      
    case CYCLE_EXECUTE:
      // Forward opcode and r_dest
      m_exe_mem->push_opcode(m_id_exe->pull_opcode());
      m_exe_mem->push_rd(m_id_exe->pull_rd());
      
      // Get op A & B and subtract them, then push ALU_out
      op_A = m_id_exe->pull_opA();
      op_B = m_id_exe->pull_opB();
      m_exe_mem->push_aluout(op_A - op_B);
      break;
      
    case CYCLE_MEMORY:
      // Forward opcode, r_dest, and ALU_out    
      m_mem_wb->push_opcode(m_exe_mem->pull_opcode());
      m_mem_wb->push_rd(m_exe_mem->pull_rd());
      m_mem_wb->push_aluout(m_exe_mem->pull_aluout());
      break;
      
    case CYCLE_WRITEBACK:
      // Pull r_dest number & aluout, then write to r_dest
      m_register[m_mem_wb->pull_rd()] = m_mem_wb->pull_aluout();
      break;
      
    default:
      helpUnexpDescr("GPR_SUBI()", c_desc); //halp wat i do
      break;
  }
}

void Pipeline::gpr_syscall(const CYCLE_DESCRIPTOR& c_desc)
{
  inst curr_inst;
  u_int32_t sys_code;
  addr str_addr;
  
  switch (c_desc)
  {
    case CYCLE_DECODE:
      curr_inst = m_if_id->pullInstruction();
      
      // Get sys_code and push into r_dest ???
      sys_code = m_register[REG_VAL_1];
      m_id_exe->push_rd(sys_code);
      break;
      
    case CYCLE_EXECUTE:
      // Forward sys_code
      m_exe_mem->push_rd(m_id_exe->pull_rd());
      
      // Calculate corrected str_addr and push into ALU_out
      str_addr = MemSys::BaseUserDataSegmentAddress | m_id_exe->pull_rd();
      m_exe_mem->push_aluout(str_addr);
      break;
      
    case CYCLE_MEMORY:
    {
      str_addr = m_exe_mem->pull_aluout();
      switch(m_exe_mem->pull_rd())
      {
    case SYSCALL_PRINT_STR:
    {
        u_int8_t letter = *((u_int8_t*)m_memory->read(str_addr, sizeof(u_int8_t))); // Read first char
        std::string str;
        str_addr++;
        while (letter != '\0')      // Print each char in the string until NUL terminator
        {
        str += letter;
        letter = *((u_int8_t*)m_memory->read(str_addr, sizeof(u_int8_t)));
        str_addr++;
        } 
        std::cout << str << std::endl; 
    }
    break;
    
    case SYSCALL_READ_STR:
    {
        std::string input;
        std::cin >> input;
        for (int i = 0; i < input.length(); i++)    // Write each char to memory
        {
          m_memory->write(str_addr, &input[i], sizeof(u_int8_t));
          str_addr++;
        }
        u_int8_t null_c = '\0';             // Add NUL terminator
        m_memory->write(str_addr, &null_c, sizeof(u_int8_t));
    }
    break;
    
    case SYSCALL_EXIT:
      //user_mode = false;  // Exit user_mode *****
      break;
      
    default:
      break;
      }
      
    }
    break;
      
    default:
      helpUnexpDescr("GPR_SYSCALL()", c_desc);
      break;
  }
  
}

void Pipeline::delegateCycle(const u_int8_t& opcode,
                                           const CYCLE_DESCRIPTOR& c_desc)
{
    switch (opcode)
    {
      case GPR_ADDI:    gpr_addi(c_desc); break;
      case GPR_B:       gpr_b(c_desc); break;
      case GPR_BEQZ:    gpr_beqz(c_desc); break;
      case GPR_BGE:     gpr_bge(c_desc); break;
      case GPR_BNE:     gpr_bne(c_desc); break;
      case GPR_LA:      gpr_la(c_desc); break;
      case GPR_LB:      gpr_lb(c_desc); break;
      case GPR_LI:      gpr_li(c_desc); break;
      case GPR_SUBI:    gpr_subi(c_desc); break;
      case GPR_SYSCALL: gpr_syscall(c_desc); break;
      default:
        std::cout << "DELEGATE_CYCLE() -- UNEXPECTED OPCODE: " 
        << opcode << std::endl;
        break;
    }
}

void Pipeline::helpUnexpDescr(const std::string& methodName, 
                                            const CYCLE_DESCRIPTOR& desc)
{
    std::cout << methodName
    << " RECIEVED UNEXPECTED CYCLE DESCRIPTOR: " 
    << desc
    << std::endl;
}

