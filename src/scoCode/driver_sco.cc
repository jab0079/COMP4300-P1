/*
 * 
 *      driver_sco.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the driver for the Scoreboard Simulator
 *          executable.
 * 
 *      Change Log:
 *          11/27/14 - Initial Creation
 * 
 * 
 */

#include<iostream>

#include "MemSys.hh"
#include "Loader.hh"
#include "scoSim.hh"
#include "Utilities.hh"

int main(int argc, char* argv[])
{   
    std::cout << std::endl;
    std::cout << "Scoreboard Simulation Started..." << std::endl;
    
    //Create memory system
    MemSys* memory = new MemSys();
    
    //Load program into memory
    Loader* loader = new Loader(memory);
    std::cout << "Loading source into memory..." << std::endl;
    addr setpc = loader->load(argv[1], Loader::SCOB_ISA);
    
    //Put a null sentinel value at the end to buffer
    //if a syscall is at the end of file, it can read this
    //null value and exit in the decode stage without memory
    //errors...
    addr topText = memory->getUserTextTop();
    inst sentinel = 0;
    memory->write(topText, &sentinel, sizeof(inst));
    memory->write(topText+4, &sentinel, sizeof(inst));

    
    memory->outputSegment(USER_DATA);
    memory->outputSegment(USER_TEXT);
    
    //Create simulator with memory system
    Simulator* scob = new ScoreboardSimulator(memory);
    
    //Set up the program counter...
    scob->setProgramCounter(setpc);
    
    //Run the simulator
    scob->run();
    
    //Calculate and Print summary stats
    u_int32_t ic = scob->getInstructionCount();
    u_int32_t cy = scob->getCycleCount();
    u_int32_t nc = scob->getNOPCount();
    
    std::cout << "Instruction Count: " << ic << std::endl;
    std::cout << "Cycle Count: " << cy << std::endl;
    std::cout << "NOP Count: " << nc << std::endl;
    
//     std::ofstream output("./result.txt");
//     output << "Instruction Count: " << ic << std::endl;
//     output << "Cycle Count: " << cy << std::endl;
//     output << "NOP Count: " << nc << std::endl;
//     output.close();
    
//     memory->outputSegment(USER_DATA);
    
    SAFE_DELETE(scob); //see Utilities.hh
    SAFE_DELETE(loader);
    SAFE_DELETE(memory);
    
    std::cout << "...Scoreboard Simulation Ended\n" << std::endl;

    return 0;
}
