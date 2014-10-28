/*
 * 
 *      driver_pipe.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the driver for the Pipeline Simulator
 *          executable.
 * 
 *      Change Log:
 *          10/23/14 - Initial creation.
 * 
 * 
 */

#include<iostream>

#include "MemSys.hh"
#include "Loader.hh"
#include "Pipeline.hh"
#include "Utilities.hh"

int main(int argc, char* argv[])
{   
    std::cout << std::endl;
    std::cout << "Pipeline Simulation Started..." << std::endl;
    
    //Create memory system
    MemSys* memory = new MemSys();
    
    //Load program into memory
    Loader* loader = new Loader(memory);
        
    //Very much a kludge, but this is the only way I figured
    //we could determine the path of the compiled sources without
    //the user having to add in a commandline argument.
    //NOTE: THIS IS COUPLED TO THE SOURCE TREE STRUCTURE
    std::string path = "docs/lab3c.s";
    std::string executePath = std::string(argv[0]);
    std::string replaceStr = "bin/pipeSim";
    if (executePath.compare(std::string("./pipeSim")) == 0)
    { //if we are executing from within the bin directory
        path.insert(0,"../"); //go up a directory...
    }
    else
    { //otherwise, replace the qualified path, but insert the corrected directory
        executePath = executePath.substr(0,executePath.length()-replaceStr.length());
        path = executePath + path; //append qualified path...
    }

    std::cout << "Loading source into memory..." << std::endl;
    addr setpc = loader->load(path.c_str(), Loader::GPR_ISA);
    
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
    Simulator* pipe = new Pipeline(memory);
    
    //Set up the program counter...
    pipe->setProgramCounter(setpc);
    
    //Run the simulator
    pipe->run();
    
    //Calculate and Print summary stats
    u_int32_t ic = pipe->getInstructionCount();
    u_int32_t cy = pipe->getCycleCount();
    u_int32_t nc = pipe->getNOPCount();
    
    std::cout << "Instruction Count: " << ic << std::endl;
    std::cout << "Cycle Count: " << cy << std::endl;
    std::cout << "NOP Count: " << nc << std::endl;
    
    std::ofstream output("../result.txt");
    output << "Instruction Count: " << ic << std::endl;
    output << "Cycle Count: " << cy << std::endl;
    output << "NOP Count: " << nc << std::endl;
    output.close();
    
    memory->outputSegment(USER_DATA);
    
    SAFE_DELETE(pipe); //see Utilities.hh
    SAFE_DELETE(loader);
    SAFE_DELETE(memory);
    
    std::cout << "...Pipeline Simulation Ended\n" << std::endl;
//     
    return 0;
}
