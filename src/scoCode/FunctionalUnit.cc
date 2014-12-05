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
: m_id(fu_type), m_instruction(0x0), 
m_stagesLeft(0), m_numstages(stages)
{}

FunctionalUnit::FunctionalUnit(const FunctionalUnit& other)
: m_id(other.m_id), m_stagesLeft(other.m_stagesLeft),
m_numstages(other.m_numstages)
{
    m_instruction = other.m_instruction->clone();
}

FunctionalUnit::~FunctionalUnit()
{
    SAFE_DELETE(m_instruction);
}

void FunctionalUnit::issue(const Instruction& i)
{
    m_instruction = i.clone();
}

void FunctionalUnit::read_operands()
{
    m_instruction->fetch_operands();
}

bool FunctionalUnit::execute()
{
    m_stagesLeft--;
    if (m_stagesLeft == 0)
    {
        m_instruction->execute();
        return true;
    }
    return false;
}

void FunctionalUnit::write_back()
{
    m_instruction->write_back();
}

void FunctionalUnit::setFU_ID(FU_ID fu_type)
{ m_id = fu_type; }
FU_ID FunctionalUnit::getFU_ID() const
{ return m_id; }
u_int32_t FunctionalUnit::getInstr_id() const
{ 
    if (m_instruction != 0x0) 
        return m_instruction->getInstr_id(); 
    return -1;
}
