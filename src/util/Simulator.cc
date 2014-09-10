/*
 * 
 *      Simulator.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the simulator interface
 * 
 *      Change Log:
 *          9/9/14 - Initial creation
 * 
 * 
 */

#include "Simulator.hh"

Simulator::Simulator(MemSys* mem)
{
    if (mem)
    {
        m_memory = mem;
    }
    else
    {
        //fail gracefully...
    }
    
    m_pc = MemSys::BaseUserTextSegmentAddress;
    m_sp = MemSys::BaseStackSegmentAddress;
}

Simulator::~Simulator()
{
    //We just want to null it out instead of delete this.
    m_memory = 0x0;
}

void Simulator::setProgramCounter(const addr& in)
{ m_pc = in;}

void Simulator::setStackPointer(const addr& in)
{ m_sp = in; }

addr Simulator::getProgramCounter() const {return m_pc;}
addr Simulator::getStackPointer() const {return m_sp;}


