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

static Instruction* create_instruction(const inst& instruction)
{
    //parse opcode
    u_int8_t opcode = ((instruction & 0xFF000000) >> 24);
    switch (opcode)
    {
        case SCOB_ADD:      return new Inst_ADD(instruction);
        case SCOB_ADDI:     return new Inst_ADDI(instruction);
        case SCOB_B:        return new Inst_B(instruction);
        case SCOB_BEQZ:     return new Inst_BEQZ(instruction);
        case SCOB_BGE:      return new Inst_BGE(instruction);
        case SCOB_BNE:      return new Inst_BNE(instruction);
        case SCOB_FADD:     return new Inst_FADD(instruction);
        case SCOB_FMUL:     return new Inst_FMUL(instruction);
        case SCOB_FSUB:     return new Inst_FSUB(instruction);
        case SCOB_LA:       return new Inst_LA(instruction);
        case SCOB_LB:       return new Inst_LB(instruction);
        case SCOB_LD:       return new Inst_LD(instruction);
        case SCOB_LI:       return new Inst_LI(instruction);
        case SCOB_NOP:      return new Inst_NOP(instruction);
        case SCOB_SD:       return new Inst_SD(instruction);
        case SCOB_SUBI:     return new Inst_SUBI(instruction);
        case SCOB_SYSCALL:  return new Inst_SYSCALL(instruction);
        default: return 0x0;
    }
    return 0x0;
}

ScoreboardSimulator::ScoreboardSimulator(MemSys* mem) 
: Simulator(mem), m_usermode(false), m_fetch_buffer(0x0)
{}

ScoreboardSimulator::~ScoreboardSimulator()
{
    SAFE_DELETE(m_fetch_buffer);
}

void ScoreboardSimulator::run()
{
    std::cout << "\tStarting Scoreboard..." << std::endl;
    
    m_usermode = true;
    while (m_usermode)
    {
        //TODO: print scoreboard
        
        this->issue();
        
    }
    

    std::cout << "\tEnding Scoreboard..." << std::endl;
}

void ScoreboardSimulator::issue()
{
    if (m_fetch_buffer == 0x0) 
    { //nothing in the fetch buffer, read from PC
        inst next_inst = 0;
        next_inst = *((inst*)m_memory->read(m_pc,sizeof(inst)));
        Instruction* next = create_instruction(next_inst);
    }
        
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



