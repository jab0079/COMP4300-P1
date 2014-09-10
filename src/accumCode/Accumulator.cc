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
 *          9/10/14 - Added instruction set constants
 *          9/9/14 - Initial creation
 * 
 * 
 */
#include "Accumulator.hh"

const u_int8_t Accumulator::ACC_INST_LOAD = 0x01;
const u_int8_t Accumulator::ACC_INST_STO = 0x02;
const u_int8_t Accumulator::ACC_INST_MULT = 0x03;
const u_int8_t Accumulator::ACC_INST_ADD = 0x04;
const u_int8_t Accumulator::ACC_INST_END = 0x05;

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

