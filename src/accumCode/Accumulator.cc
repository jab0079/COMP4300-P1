/*
 * 
 *      Accumulator.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the Accumulator Simulator
 * 
 *      Change Log:
 *          9/9/14 - Initial creation
 * 
 * 
 */
#include "Accumulator.hh"

Accumulator::Accumulator(MemSys* mem) 
: Simulator(mem)
{
}

Accumulator::~Accumulator()
{}

void Accumulator::run()
{
    std::cout << "\tStarting Accumulator..." << std::endl;
    
    inst curr_inst = *((inst*)m_memory->read(m_pc,sizeof(inst))); 
    
    std::cout << "\tEnding Accumulator..." << std::endl;
}

