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
 *          9/29/14 - Added exceptions to read and write
 *          9/17/14 - Made class and derived classes Uncopyable
 *          9/8/14 - Set up constants for bases and segment sizes, as
 *                      well as the byte-size segments that accompany
 *                      each segment.
 *          9/5/14 - Created initial interface
 *          9/5/14 - Initial creation detailing description.
 * 
 * 
 */

#include <iostream>
#include <stdlib.h> //for calloc
#include <string.h> //for strncpy
#include <exception>
#include <stdexcept>
#include "Uncopyable.hh"
#include "Utilities.hh"

typedef u_int32_t addr;
typedef u_int32_t inst;

enum Segment
{
  USER_TEXT,
  USER_DATA,
  KERNEL_TEXT,
  KERNEL_DATA,
  STACK
};

class MemSys : private Uncopyable
{
    
    public:
        MemSys();
        virtual ~MemSys();
        
        //Public Methods ------------------------------------------------------
        virtual void* read(const addr& address, 
                           const unsigned int& size) const 
                           throw(std::range_error);
        
        virtual bool write(const addr& address, 
                           const void* data, 
                           const unsigned int& size)
                           throw(std::range_error);
        
        virtual void outputSegment(const Segment& segment) const;
        
        // Public Constants ---------------------------------------------------
        //Segment Sizes...(in bytes)
        static const unsigned int UserTextSegmentSize;
        static const unsigned int UserDataSegmentSize;
        static const unsigned int KernelTextSegmentSize;
        static const unsigned int KernelDataSegmentSize;
        static const unsigned int StackSegmentSize;
        
        //Segment Address Bases...
        static const addr BaseUserTextSegmentAddress;
        static const addr BaseUserDataSegmentAddress;
        static const addr BaseKernelTextSegmentAddress;
        static const addr BaseKernelDataSegmentAddress;
        static const addr BaseStackSegmentAddress;
        
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
        char* m_usertext_seg;
        char* m_userdata_seg;
        char* m_kerneltext_seg;
        char* m_kerneldata_seg;
        char* m_stack_seg;

    
};

#endif