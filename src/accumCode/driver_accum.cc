/*
 * 
 *      driver_accum.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the driver for the Accumulator Simulator
 *          executable.
 * 
 *      Change Log:
 *          9/10/14 - Added the Loader to system
 *          9/9/14 - Added memory system and test data for instructions
 *                      and the actual simulator object.
 *          9/5/14 - Initial creation detailing description.
 * 
 * 
 */

#include<iostream>

#include "MemSys.hh"
#include "Loader.hh"
#include "Accumulator.hh"
#include "Utilities.hh"

int main(int argc, char* argv[])
{   
    std::cout << std::endl;
    std::cout << "Accumulator Simulation Started..." << std::endl;
    
    //Create memory system
    MemSys* memory = new MemSys();
    
    //Load program into memory
    Loader* loader = new Loader(memory);
    
    //Very much a kludge, but this is the only way I figured
    //we could determine the path of the compiled sources without
    //the user having to add in a commandline argument.
    //NOTE: THIS IS COUPLED TO THE SOURCE TREE STRUCTURE
    std::string path = "docs/accum_compiled.s";
    std::string executePath = std::string(argv[0]);
    std::string replaceStr = "bin/accumSim";
    if (executePath.compare(std::string("./accumSim")) == 0)
    { //if we are executing from within the bin directory
        path.insert(0,"../"); //go up a directory...
    }
    else
    { //otherwise, replace the qualified path, but insert the corrected directory
        executePath = executePath.substr(0,executePath.length()-replaceStr.length());
        path = executePath + path; //append qualified path...
    }

    std::cout << "Loading source into memory..." << std::endl;
    addr setpc = loader->load(path.c_str(), Loader::ACCUM_ISA);
    
    memory->outputSegment(USER_DATA);
    memory->outputSegment(USER_TEXT);

    //Create simulator with memory system
    Simulator* acc = new Accumulator(memory);
    
    //Set up the program counter...
    acc->setProgramCounter(setpc);
    
    //Run the simulator
    acc->run();
    
    memory->outputSegment(USER_DATA);

    
    SAFE_DELETE(acc); //see Utilities.hh
    SAFE_DELETE(loader);
    SAFE_DELETE(memory);
    
    std::cout << "...Accumulator Simulation Ended\n" << std::endl;
    
    return 0;
}
