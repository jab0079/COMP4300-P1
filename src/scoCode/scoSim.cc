/*
 * 
 *      scoSim.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the Scoreboard Simulator
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "scoSim.hh"

#include "Inst_ADD.hh"
#include "Inst_ADDI.hh"
#include "Inst_B.hh"
#include "Inst_BEQZ.hh"
#include "Inst_BGE.hh"
#include "Inst_BNE.hh"
#include "Inst_FADD.hh"
#include "Inst_FMUL.hh"
#include "Inst_FSUB.hh"
#include "Inst_LA.hh"
#include "Inst_LB.hh"
#include "Inst_LD.hh"
#include "Inst_LI.hh"
#include "Inst_NOP.hh"
#include "Inst_SD.hh"
#include "Inst_SUBI.hh"
#include "Inst_SYSCALL.hh"

static Instruction* create_instruction(ScoreboardSimulator* simu, inst& instruction)
{
    //parse opcode
    u_int8_t opcode = ((instruction & 0xFF000000) >> 24);
    switch (opcode)
    {
        case SCOB_ADD:      return new Inst_ADD(simu, instruction);
        case SCOB_ADDI:     return new Inst_ADDI(simu, instruction);
        case SCOB_B:        return new Inst_B(simu, instruction);
        case SCOB_BEQZ:     return new Inst_BEQZ(simu, instruction);
        case SCOB_BGE:      return new Inst_BGE(simu, instruction);
        case SCOB_BNE:      return new Inst_BNE(simu, instruction);
        case SCOB_FADD:     return new Inst_FADD(simu, instruction);
        case SCOB_FMUL:     return new Inst_FMUL(simu, instruction);
        case SCOB_FSUB:     return new Inst_FSUB(simu, instruction);
        case SCOB_LA:       return new Inst_LA(simu, instruction);
        case SCOB_LB:       return new Inst_LB(simu, instruction);
        case SCOB_LD:       return new Inst_LD(simu, instruction);
        case SCOB_LI:       return new Inst_LI(simu, instruction);
        case SCOB_NOP:      return new Inst_NOP(simu, instruction);
        case SCOB_SD:       return new Inst_SD(simu, instruction);
        case SCOB_SUBI:     return new Inst_SUBI(simu, instruction);
        case SCOB_SYSCALL:  return new Inst_SYSCALL(simu, instruction);
        default: return 0x0;
    }
    return 0x0;
}

ScoreboardSimulator::ScoreboardSimulator(MemSys* mem) 
: Simulator(mem), m_usermode(false), m_fetch_buffer(0x0)
{
    m_integer_fu = new FunctionalUnit(FU_INTEGER, 2);
    m_fpadd_fu = new FunctionalUnit(FU_FP_ADDER, 2);
    m_fpmult_fu = new FunctionalUnit(FU_FP_MULT, 6);
    m_mem_fu = new FunctionalUnit(FU_MEMORY, 1);
}

ScoreboardSimulator::~ScoreboardSimulator()
{
    SAFE_DELETE(m_fetch_buffer);
    SAFE_DELETE(m_integer_fu);
    SAFE_DELETE(m_fpadd_fu);
    SAFE_DELETE(m_fpmult_fu);
    SAFE_DELETE(m_mem_fu);
}

void ScoreboardSimulator::run()
{
    std::cout << "\tStarting Scoreboard..." << std::endl;
    
    m_usermode = true;
    while (m_usermode)
    {
        //TODO: print scoreboard
        
        this->issue();
        this->read_operands();
        
    }
    
    std::cout << "\tEnding Scoreboard..." << std::endl;
}

void ScoreboardSimulator::issue()
{
    if (m_fetch_buffer == 0x0) 
    { //nothing in the fetch buffer, read from PC
        inst next_inst = 0;
        next_inst = *((inst*)m_memory->read(m_pc,sizeof(inst)));
        this->setProgramCounter(this->getProgramCounter() + sizeof(inst));
        //Go ahead and put it in the fetch buffer. If
        //we don't stall, then we take it out...
        m_fetch_buffer = create_instruction(this, next_inst);
    }
    
    m_fetch_buffer->decode(); //decode instruction in buffer
    
    FU_ID fu = getRespectiveFU(*m_fetch_buffer);
    
    //Check if functional unit is busy
    bool stallFUBusy = m_scob->check_FU_busy(fu, *m_fetch_buffer);
    
    //Check WAW hazard from scoreboard
    bool stallWAW = m_scob->check_WAW(fu, m_fetch_buffer->getDestinationRegister());
    
    
    //if we need to stall, keep whatever is in the fetch
    //buffer inside the buffer. Otherwise, take out the
    //item in the fetch buffer and issue it to a functional unit
    if (!stallFUBusy && !stallWAW)
    {
        switch (fu)
        {
            case FU_INTEGER:
                m_integer_fu->issue(*m_fetch_buffer);
                break;
            case FU_FP_ADDER:
                m_fpadd_fu->issue(*m_fetch_buffer);
                break;
            case FU_FP_MULT:
                m_fpmult_fu->issue(*m_fetch_buffer);
                break;
            case FU_MEMORY:
                m_mem_fu->issue(*m_fetch_buffer);
                break;
            default:
                break;
        }
        SAFE_DELETE(m_fetch_buffer); //remove from buffer
    }
    else
    {
        
    }
        
}

void ScoreboardSimulator::read_operands()
{
    //TODO: for each functional unit, ask scoreboard which stage
    //the functional unit is in.
    
    //TODO: if the functional unit is in the read operands stage,
    //ask scoreboard whether both operands are ready.
    
    //TODO: if both are ready, read the operands. Otherwise, skip   
}

/* SETS ---------------------------------------------------------------------*/
void ScoreboardSimulator::setRegister(const u_int8_t& regnum, const reg& val)
{
    if (regnum >= 0 && regnum < REGISTER_COUNT)
        m_register[regnum] = val;
}

void ScoreboardSimulator::setFPRegister(const u_int8_t& regnum, const reg_d& val)
{
    if (regnum >= 0 && regnum < FLOATING_POINT_REGISTERS)
        m_register_d[regnum] = val;
    
    if (regnum >= FLOATING_POINT_REGISTERS)
        setFPRegister((regnum - FLOATING_POINT_REGISTERS), val);
}

void ScoreboardSimulator::setUserMode(const bool& isInUserMode)
{
    m_usermode = isInUserMode;
}

/* GETS ---------------------------------------------------------------------*/
reg ScoreboardSimulator::getRegister(const u_int8_t& regnum) const
{ return m_register[regnum]; }

reg_d ScoreboardSimulator::getFPRegister(const u_int8_t& regnum) const
{ 
    if (regnum >= 0 && regnum < FLOATING_POINT_REGISTERS)
         return m_register_d[regnum];
    
    if (regnum >= FLOATING_POINT_REGISTERS)
         return getFPRegister((regnum - FLOATING_POINT_REGISTERS));
    
    return -1;
}

bool ScoreboardSimulator::isInUserMode() const
{ return m_usermode; }

FU_ID ScoreboardSimulator::getRespectiveFU(const Instruction& i) const
{
    u_int8_t op = i.getOpCode();
    if (op == SCOB_INST_SET_VALS[SCOB_ADD]
        || op == SCOB_INST_SET_VALS[SCOB_ADDI]
        || op == SCOB_INST_SET_VALS[SCOB_B]
        || op == SCOB_INST_SET_VALS[SCOB_BEQZ]
        || op == SCOB_INST_SET_VALS[SCOB_BGE]
        || op == SCOB_INST_SET_VALS[SCOB_BNE]
        || op == SCOB_INST_SET_VALS[SCOB_SUBI])
    {
        return FU_INTEGER;
    }
    else if (op == SCOB_INST_SET_VALS[SCOB_FADD]
        || op == SCOB_INST_SET_VALS[SCOB_FSUB])
    {
        return FU_FP_ADDER;
    }
    else if (op == SCOB_INST_SET_VALS[SCOB_FMUL])
    {
        return FU_FP_MULT;
    }
    else if (op == SCOB_INST_SET_VALS[SCOB_LA]
        || op == SCOB_INST_SET_VALS[SCOB_LB]
        || op == SCOB_INST_SET_VALS[SCOB_LD]
        || op == SCOB_INST_SET_VALS[SCOB_LI]
        || op == SCOB_INST_SET_VALS[SCOB_SD])
    {
        return FU_MEMORY;
    }
    return FU_UNDEFINED;   
}


