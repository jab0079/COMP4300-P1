/*
 * 
 *      driver_stack.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the driver for the Stack Simulator
 *          executable.
 * 
 *      Change Log:
 *          9/10/14 - Added the Loader to system and memory (just copied driver_accum.cc)
 *          9/5/14 - Initial creation detailing description.
 * 
 * 
 */

#include<iostream>

#include "MemSys.hh"
#include "Loader.hh"
#include "Stack.hh"
#include "Utilities.hh"

int main(int argc, char* argv[])
{
    std::cout << std::endl;
    std::cout << "Stack Simulation Started..." << std::endl;
    
    //Create memory system
    MemSys* memory = new MemSys();
    
    //Load program into memory
    Loader* loader = new Loader(memory);
    
    //Very much a kludge, but this is the only way I figured
    //we could determine the path of the compiled sources without
    //the user having to add in a commandline argument.
    //NOTE: THIS IS COUPLED TO THE SOURCE TREE STRUCTURE
    std::string path = "docs/stack_compiled.s";
    std::string executePath = std::string(argv[0]);
    std::string replaceStr = "bin/stackSim";
    if (executePath.compare(std::string("./stackSim")) == 0)
    { //if we are executing from within the bin directory
        path.insert(0,"../"); //go up a directory...
    }
    else
    { //otherwise, replace the qualified path, but insert the corrected directory
        executePath = executePath.substr(0,executePath.length()-replaceStr.length());
        path = executePath + path; //append qualified path...
    }

    std::cout << "Loading source into memory..." << std::endl;
    addr setpc = loader->load(path.c_str(), Loader::STACK_ISA);
    
    memory->outputSegment(USER_DATA);
    memory->outputSegment(USER_TEXT);

    //Create simulator with memory system
    Simulator* stk = new Stack(memory);
    
    //Set up the program counter...
    stk->setProgramCounter(setpc);
    
    //Run the simulator
    stk->run();
    
    SAFE_DELETE(stk); //see Utilities.hh
    SAFE_DELETE(loader);
    SAFE_DELETE(memory);
    
    std::cout << "...Stack Simulation Ended\n" << std::endl;
    
    return 0;
}
