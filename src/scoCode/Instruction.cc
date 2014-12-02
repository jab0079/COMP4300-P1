/*
 * 
 *      Instruction.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the provided
 *          methods that go along with the abstract Instruction interface.
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "Instruction.hh"

Instruction::Instruction(inst the_instruction)
: m_instruction(the_instruction)
{}

Instruction::~Instruction() {}

inst Instruction::getInstruction() const
{return m_instruction; }

