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
 *          9/9/14 - Added memory system and test data for instructions
 *                      and the actual simulator object.
 *          9/5/14 - Initial creation detailing description.
 * 
 * 
 */

#include<iostream>

#include "MemSys.hh"
#include "Accumulator.hh"
#include "Utilities.hh"

int main(int argc, char* argv[])
{
    std::cout << std::endl;
    std::cout << "Accumulator Simulation Started..." << std::endl;
    
    //Create memory system
    MemSys* memory = new MemSys();
    
    //Load program into memory
    //..for now we will hand generate this
    //until the loader is implemented
    
    //Load data into memory
    u_int32_t X = 3;
    u_int32_t A = 7;
    u_int32_t B = 5;
    u_int32_t C = 4;
    memory->write(MemSys::BaseUserDataSegmentAddress, &X, sizeof(u_int32_t));
    memory->write(MemSys::BaseUserDataSegmentAddress+4, &A, sizeof(u_int32_t));
    memory->write(MemSys::BaseUserDataSegmentAddress+8, &B, sizeof(u_int32_t));
    memory->write(MemSys::BaseUserDataSegmentAddress+12, &C, sizeof(u_int32_t));
    memory->outputSegment(USER_DATA);
    
    inst instruction = 0;
    //Load instructions into memory
    instruction = (inst)(0x00000000 | (MemSys::BaseUserDataSegmentAddress)); //LOAD X
    memory->write(MemSys::BaseUserTextSegmentAddress, &instruction, sizeof(inst));
    instruction = 0x03000000 | (MemSys::BaseUserDataSegmentAddress); //MULT X
    memory->write(MemSys::BaseUserTextSegmentAddress+4, &instruction, sizeof(inst));
    instruction = 0x03000000 | (MemSys::BaseUserDataSegmentAddress+4); //MULT A
    memory->write(MemSys::BaseUserTextSegmentAddress+8, &instruction, sizeof(inst));
    instruction = 0x01000000 | (MemSys::BaseUserDataSegmentAddress+16); //STO C+4
    memory->write(MemSys::BaseUserTextSegmentAddress+12, &instruction, sizeof(inst));
    instruction = 0x00000000 | (MemSys::BaseUserDataSegmentAddress); //LOAD X
    memory->write(MemSys::BaseUserTextSegmentAddress+16, &instruction, sizeof(inst));
    instruction = 0x03000000 | (MemSys::BaseUserDataSegmentAddress+8); //MULT B
    memory->write(MemSys::BaseUserTextSegmentAddress+20, &instruction, sizeof(inst));
    instruction = 0x02000000 | (MemSys::BaseUserDataSegmentAddress+16); //ADD C+4
    memory->write(MemSys::BaseUserTextSegmentAddress+24, &instruction, sizeof(inst));
    instruction = 0x02000000 | (MemSys::BaseUserDataSegmentAddress+12); //ADD C
    memory->write(MemSys::BaseUserTextSegmentAddress+28, &instruction, sizeof(inst));
    instruction = 0x01000000 | (MemSys::BaseUserDataSegmentAddress+16); //STO C+4
    memory->write(MemSys::BaseUserTextSegmentAddress+32, &instruction, sizeof(inst));
        memory->outputSegment(USER_TEXT);

    //Create simulator with memory system
    Simulator* acc = new Accumulator(memory);
    
    //Run the simulator
    acc->run();
    
    SAFE_DELETE(acc); //see Utilities.hh
    SAFE_DELETE(memory);
    
    std::cout << "...Accumulator Simulation Ended\n" << std::endl;
    
    return 0;
}
