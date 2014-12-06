/*
 * 
 *      FunctionalUnit.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the Functional unit
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "FunctionalUnit.hh"

FunctionalUnit::FunctionalUnit(FU_ID fu_type, u_int32_t stages)
: m_id(fu_type), m_issued_inst(0x0), 
m_stagesLeft(0), m_numstages(stages), 
m_execute_buffer(0x0), m_write_back(0x0)
{}

FunctionalUnit::FunctionalUnit(const FunctionalUnit& other)
: m_id(other.m_id), m_stagesLeft(other.m_stagesLeft),
m_numstages(other.m_numstages), m_stage_queue(other.m_stage_queue)
{
    m_issued_inst = other.m_issued_inst->clone();
    m_write_back = other.m_write_back->clone();
    m_execute_buffer = other.m_execute_buffer->clone();
}

FunctionalUnit::~FunctionalUnit()
{
    SAFE_DELETE(m_issued_inst);
    Instruction* i;
    while ((i = m_stage_queue.front()) != 0x0)
    {
        SAFE_DELETE(i);
        m_stage_queue.pop();
    }
    SAFE_DELETE(m_write_back);
    SAFE_DELETE(m_execute_buffer);
}

void FunctionalUnit::issue(const Instruction& i)
{
    SAFE_DELETE(m_issued_inst);
    m_issued_inst = i.clone();
}

u_int32_t FunctionalUnit::read_operands()
{
    u_int32_t id = -1;
    if (m_issued_inst != 0x0)
    {
        m_issued_inst->fetch_operands();
        id = m_issued_inst->getInstr_id();
        //Hand off to wait to be executed
        m_execute_buffer = m_issued_inst;
        m_issued_inst = 0x0;
    }
    return id;
}

//returns the ID of the completed instruction, if
//there was one.
u_int32_t FunctionalUnit::execute(bool pushExecuteBuffer)
{
    u_int32_t id = -1;
    
    //Hand off to be executed
    if (m_execute_buffer != 0x0 && pushExecuteBuffer)
    {
        m_stage_queue.push(m_execute_buffer);   
        m_execute_buffer = 0x0;
    }
    else
    {
        m_stage_queue.push(0x0);
    }
    
    if (m_stage_queue.size() % m_numstages == 0)
    {
        Instruction* i = m_stage_queue.front();
        m_stage_queue.pop();
        if (i != 0x0)
        {
            i->execute();
            id = i->getInstr_id();
            m_write_back = i;
        }
        return id;
    }
    return id;
}

u_int32_t FunctionalUnit::write_back()
{
    u_int32_t id = -1;
    if (m_write_back != 0x0)
    {
        m_write_back->write_back();
        id = m_write_back->getInstr_id();
        SAFE_DELETE(m_write_back);
    }
    return id;
}

void FunctionalUnit::setFU_ID(FU_ID fu_type)
{ m_id = fu_type; }
FU_ID FunctionalUnit::getFU_ID() const
{ return m_id; }
u_int32_t FunctionalUnit::getInstr_id() const
{ 
//     if (m_instruction != 0x0) 
//         return m_instruction->getInstr_id(); 
    return -1;
}
u_int32_t FunctionalUnit::getInstr_id_issued() const
{ 
    if (m_issued_inst != 0x0) 
        return m_issued_inst->getInstr_id(); 
    return -1;
}
u_int32_t FunctionalUnit::getInstr_id_executebuffer() const
{ 
    if (m_execute_buffer != 0x0) 
        return m_execute_buffer->getInstr_id(); 
    return -1;
}
u_int32_t FunctionalUnit::getInstr_id_writeback() const
{ 
    if (m_write_back != 0x0) 
        return m_write_back->getInstr_id(); 
    return -1;
}

