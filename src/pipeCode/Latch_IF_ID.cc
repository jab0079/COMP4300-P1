/*
 * 
 *      Latch_IF_ID.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the Latch_IF_ID
 *          object between the instruction fetch and the instruction decode
 *          cycles.
 * 
 *      Change Log:
 *          10/14/14 - Initial Creation
 * 
 * 
 */

#include "Latch_IF_ID.hh"

Latch_IF_ID::Latch_IF_ID() {}

Latch_IF_ID::~Latch_IF_ID() {}

void Latch_IF_ID::update()
{
  m_inst_buffer_old = m_inst_buffer_new;
}

inst Latch_IF_ID::pullInstruction()
{
  return m_inst_buffer_old;
}

void Latch_IF_ID::pushInstruction(const inst& i)
{
  m_inst_buffer_new = i;
}
