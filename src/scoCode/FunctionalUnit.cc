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

FunctionalUnit::FunctionalUnit(FU_ID fu_type)
: m_id(fu_type)
{}

FunctionalUnit::FunctionalUnit(const FunctionalUnit& other)
: m_id(other.m_id)
{}

FunctionalUnit::~FunctionalUnit()
{}

void FunctionalUnit::issue(const Instruction& i)
{
    m_instruction = i.clone();
    
}

void FunctionalUnit::setFU_ID(FU_ID fu_type)
{ m_id = fu_type; }
FU_ID FunctionalUnit::getFU_ID() const
{ return m_id; }
