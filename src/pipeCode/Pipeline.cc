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
 *          10/26/14 - Implemented correct syscall exception procedures; Fixed types
 *                      that were used for some of the values in some instructions
 *                      particularly the branch instructions;
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
  
  m_usermode = false;
  m_trapped = false;
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
    std::cout << "\tStarting Pipeline..." << std::endl;
    resetLatches();
    runPipeline();
    std::cout << "\tEnding Pipeline..." << std::endl;
}

void Pipeline::resetLatches()
{
    m_exe_mem->reset();
    m_id_exe->reset();
    m_if_id->reset();
    m_mem_wb->reset();
}

void Pipeline::updateLatches()
{
    m_exe_mem->update();
    m_id_exe->update();
    m_if_id->update();
    m_mem_wb->update();
}

void Pipeline::runPipeline()
{
    m_usermode = true;
    m_trapped = false;
    while (m_usermode)
    {
        gpr_fetch();
        gpr_decode();
        delegateCycle(m_id_exe->pull_opcode(), CYCLE_EXECUTE);
        delegateCycle(m_exe_mem->pull_opcode(), CYCLE_MEMORY);
        delegateCycle(m_mem_wb->pull_opcode(), CYCLE_WRITEBACK);
        
        updateLatches();
    }
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

void Pipeline::gpr_fetch()
{
    inst curr_inst = 0;
    // Read memory at PC  
    curr_inst = *((inst*)m_memory->read(m_pc,sizeof(inst)));
    //push instruction to latch
    m_if_id->pushInstruction(curr_inst);
}

void Pipeline::gpr_decode()
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

void Pipeline::gpr_addi(const CYCLE_DESCRIPTOR& c_desc)
{
  inst curr_inst;
  u_int8_t r_dest, r_src1, r_forwarddest;
  int32_t value, op_A, op_B;
  
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
  int32_t value; 
  u_int32_t aluout;
  
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
    int32_t value;
    u_int32_t aluout;
    
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
    int32_t value; 
    u_int32_t aluout;
    switch (c_desc)
    {
        case CYCLE_DECODE:
            curr_inst = m_if_id->pullInstruction();
            // Get source 1 register number
            r_src1 = (curr_inst & 0x00F80000) >> 19;
            // Get source 2 register number
            r_src2 = (curr_inst & 0x0007C000) >> 14;
            // Get signed label offset value and calculate newpc
            value = decodeInstr(curr_inst, 14);
            aluout = m_pc + value * 4;
                    
            if ((int32_t)m_register[r_src1] >= (int32_t)m_register[r_src2])
            { // Branch (update PC), if value of r_src1 >= r_src2
                m_id_exe->push_newpc(aluout);
                m_pc = aluout;
            }
            break;
        case CYCLE_EXECUTE: //do nothing
            m_exe_mem->push_opcode(m_id_exe->pull_opcode());
            break;
        case CYCLE_MEMORY: //do nothing
            m_mem_wb->push_opcode(m_exe_mem->pull_opcode());
            break;
    }
//     else
//     { 
//         helpUnexpDescr("GPR_BGE()", c_desc);
//     }
}

void Pipeline::gpr_bne(const CYCLE_DESCRIPTOR& c_desc)
{
    inst curr_inst;
    u_int8_t r_src1, r_src2;
    int32_t value;
    u_int32_t aluout;

    if (c_desc == CYCLE_DECODE)
    {
        curr_inst = m_if_id->pullInstruction();
        // Get source 1 register number
        r_src1 = (curr_inst & 0x00F80000) >> 19;
        // Get source 2 register number
        r_src2 = (curr_inst & 0x0007C000) >> 14;
        // Get signed label offset value and calculate newpc
        value = decodeInstr(curr_inst, 14);
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
      // Forward opcode, r_dest, and aluout (from value)
      m_exe_mem->push_opcode(m_id_exe->pull_opcode());
      m_exe_mem->push_rd(m_id_exe->pull_rd());
      m_exe_mem->push_aluout(m_id_exe->pull_val());
      break;
      
    case CYCLE_MEMORY:
      // Forward opcode, r_dest, and aluout
      m_mem_wb->push_opcode(m_exe_mem->pull_opcode());
      m_mem_wb->push_rd(m_exe_mem->pull_rd());
      m_mem_wb->push_aluout(m_exe_mem->pull_aluout());
      break;
      
    case CYCLE_WRITEBACK:
      // Load signed label offset address into r_dest
      m_register[m_mem_wb->pull_rd()] = m_mem_wb->pull_aluout();
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
      m_exe_mem->push_aluout(m_id_exe->pull_val());
      break;
      
    case CYCLE_MEMORY:
      // Forward opcode, r_dest, and aluout
      m_mem_wb->push_opcode(m_exe_mem->pull_opcode());
      m_mem_wb->push_rd(m_exe_mem->pull_rd());
      m_mem_wb->push_aluout(m_exe_mem->pull_aluout());
      break;
      
    case CYCLE_WRITEBACK:
      // Load signed label offset address into r_dest
      m_register[m_mem_wb->pull_rd()] = m_mem_wb->pull_aluout();
      break;
      
    default:
      helpUnexpDescr("GPR_LI()", c_desc);
      break;
  }
}

void Pipeline::gpr_subi(const CYCLE_DESCRIPTOR& c_desc)
{
    inst curr_inst;
    u_int8_t r_dest, r_src1, r_forwarddest;
    int32_t value, op_A, op_B;
  
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
            r_dest = m_id_exe->pull_rd();
            r_forwarddest = m_exe_mem->pull_rd(); //from previous instruction
            m_exe_mem->push_rd(r_dest);
        
            // Get op A & B and subtract them, then push ALU_out
            //data hazard detection...
            if (r_dest != r_forwarddest)
                op_A = m_id_exe->pull_opA();
            else
                op_A = m_exe_mem->pull_aluout();
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
    switch (c_desc)
    {
        case CYCLE_DECODE:
            //Psuedo-stop simulator here and jump to
            //"prearranged" exception handler code...  
            syscall_exception();
        break;

        default:
            helpUnexpDescr("GPR_SYSCALL()", c_desc);
            break;
    }
}


//This code contains the prearranged syscall code that is usually
//held inside the kernel, however for sake of simplicity we will
//hardcode the simulated part here.
void Pipeline::syscall_exception()
{
    //Here we "pause" the simulator and let previous
    //instructions complete before we continue with syscall
    //Let previous instructions complete with a controlled
    //flush of the previous instructions...
    //Controlled Simulated Timestep 1
    delegateCycle(m_id_exe->pull_opcode(), CYCLE_EXECUTE);
    delegateCycle(m_exe_mem->pull_opcode(), CYCLE_MEMORY);
    delegateCycle(m_mem_wb->pull_opcode(), CYCLE_WRITEBACK);
    updateLatches();
    //Controlled Simulated Timestep 2
    delegateCycle(m_exe_mem->pull_opcode(), CYCLE_MEMORY);
    delegateCycle(m_mem_wb->pull_opcode(), CYCLE_WRITEBACK);
    updateLatches();
    //Controlled Simulated Timestep 3
    delegateCycle(m_mem_wb->pull_opcode(), CYCLE_WRITEBACK);
    //Flush pipeline for after exception
    resetLatches();
    
    //Kernel Code...
    u_int32_t sys_code = m_register[REG_VAL_1];
    addr str_addr = MemSys::BaseUserDataSegmentAddress | m_register[REG_ARG_1];
    switch(sys_code)
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
            m_usermode = false;
            break;
        default:
            break;
    }
}

void Pipeline::gpr_nop(const CYCLE_DESCRIPTOR& c_desc)
{
    switch (c_desc)
    {
        case CYCLE_EXECUTE:
            m_exe_mem->push_opcode(m_id_exe->pull_opcode());
            break;
        case CYCLE_MEMORY:
            m_mem_wb->push_opcode(m_exe_mem->pull_opcode());
            break;
        default:
            break;
        
    }
}

void Pipeline::delegateCycle(const u_int8_t& opcode,
                             const CYCLE_DESCRIPTOR& c_desc)
{
    if (opcode == GPR_INST_SET_VALS[GPR_ADDI])
        gpr_addi(c_desc);
    else if (opcode == GPR_INST_SET_VALS[GPR_B])
        gpr_b(c_desc);
    else if (opcode == GPR_INST_SET_VALS[GPR_BEQZ])
        gpr_beqz(c_desc);
    else if (opcode == GPR_INST_SET_VALS[GPR_BGE])
        gpr_bge(c_desc);
    else if (opcode == GPR_INST_SET_VALS[GPR_BNE])
        gpr_bne(c_desc);
    else if (opcode == GPR_INST_SET_VALS[GPR_LA])
        gpr_la(c_desc);
    else if (opcode == GPR_INST_SET_VALS[GPR_LB])
        gpr_lb(c_desc);
    else if (opcode == GPR_INST_SET_VALS[GPR_LI])
        gpr_li(c_desc);
    else if (opcode == GPR_INST_SET_VALS[GPR_SUBI])
        gpr_subi(c_desc);
    else if (opcode == GPR_INST_SET_VALS[GPR_SYSCALL])
        gpr_syscall(c_desc);
    else if (opcode == GPR_INST_SET_VALS[GPR_NOP])
        gpr_nop(c_desc);
}

void Pipeline::helpUnexpDescr(const std::string& methodName, 
                                            const CYCLE_DESCRIPTOR& desc)
{
    std::cout << methodName
    << " RECIEVED UNEXPECTED CYCLE DESCRIPTOR: " 
    << desc
    << std::endl;
}

