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
 *          9/5/14 - Initial creation detailing description.
 * 
 * 
 */

#include<iostream>

#include "MemSys.hh"

int main(int argc, char* argv[])
{
    std::cout << std::endl;
    std::cout << "Accumulator Simulator Started...\n" << std::endl;
    
    MemSys* memory = new MemSys();
    
    //-----------------------------------------------------
    //Testing Reads
    addr test_addr = MemSys::BaseUserTextSegmentAddress;
    int num = 20;
    char* test_ret = (char *)memory->read(test_addr, num);
    
    for (int i = 0; i < num; i++)
        std::cout << test_ret[i] << std::endl;;
    
    free(test_ret);
    memory->write(test_addr, "Z", 1);
    memory->outputSegment(USER_TEXT);
    //-----------------------------------------------------
    
    //-----------------------------------------------------
    //Testing Writes
    addr test_addr_2 = MemSys::BaseUserDataSegmentAddress;
    char* test_write = "This is a test string";
    int num_2 = 21;
    memory->write(test_addr_2, test_write, num_2);
    memory->outputSegment(USER_DATA);
    //-----------------------------------------------------
    
    delete memory;
    
    std::cout << "...Accumulator Simulator Ended\n" << std::endl;
    
    return 0;
}