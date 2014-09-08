#ifndef MEMSYS_HH
#define MEMSYS_HH
/*
 * 
 *      MemSys.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This class defines the interface for the memory system (MemSys)
 *          used by the simulators in this application.
 * 
 *      Change Log:
 *          9/8/14 - Set up constants for bases and segment sizes, as
 *                      well as the byte-size segments that accompany
 *                      each segment.
 *          9/5/14 - Created initial interface
 *          9/5/14 - Initial creation detailing description.
 * 
 * 
 */

#include<iostream>
#include<stdlib.h> //for calloc
#include<string.h> //for strncpy

#define BLOCK 4096

typedef unsigned int addr;

enum Segment
{
  USER_TEXT,
  USER_DATA,
  KERNEL_TEXT,
  KERNEL_DATA,
  STACK
};

class MemSys
{
    
    public:
        MemSys();
        //Public Methods ------------------------------------------------------
        virtual void* read(const addr& address, 
                           const unsigned int& size) const;
        
        virtual bool write(const addr& address, 
                           const void* data, 
                           const unsigned int& size);
        
        virtual void outputSegment(const Segment& segment) const;
        
        virtual ~MemSys();
        
        // Public Constants ---------------------------------------------------
        //Segment Sizes...(in bytes)
        static const unsigned int UserTextSegmentSize = BLOCK;
        static const unsigned int UserDataSegmentSize = BLOCK;
        static const unsigned int KernelTextSegmentSize = BLOCK;
        static const unsigned int KernelDataSegmentSize = BLOCK;
        static const unsigned int StackSegmentSize = BLOCK;
        
        //Segment Address Bases...
        static const addr BaseUserTextSegmentAddress = 0x10000000;
        static const addr BaseUserDataSegmentAddress = 0x20000000;
        static const addr BaseKernelTextSegmentAddress = 0x30000000;
        static const addr BaseKernelDataSegmentAddress = 0x40000000;
        static const addr BaseStackSegmentAddress = 0x50000000;
        
    protected:
        //Protected Members ---------------------------------------------------
        addr m_usertext_top;
        addr m_userdata_top;
        addr m_kerneltext_top;
        addr m_kerneldata_top;
        addr m_stack_top;
    
    private:
        //Private Methods -----------------------------------------------------
//         MemSys();
        
        //Private Members -----------------------------------------------------
        char m_usertext_seg[UserTextSegmentSize];
        char m_userdata_seg[UserDataSegmentSize];
        char m_kerneltext_seg[KernelTextSegmentSize];
        char m_kerneldata_seg[KernelDataSegmentSize];
        char m_stack_seg[StackSegmentSize];

    
};

#endif