/*
 *
 *      Stack.cc
 *
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 *      Description:
 *          This class defines the implementation for the stack-based simulator.
 *
 *      Change Log:
 *          9/8/14 - Initial implementation created
 *
 *
 */
#include "Stack.hh"

Stack::Stack(MemSys* mem)
: Simulator(mem)
{
}

Stack::~Stack()
{}

void Stack::run()
{
    std::cout << "\tStarting Stack..." << std::endl;

    inst curr_inst = (inst)m_memory->read(m_pc,sizeof(inst));

    std::cout << "\tEnding Stack..." << std::endl;
}
