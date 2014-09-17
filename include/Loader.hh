#ifndef LOADER_HH
#define LOADER_HH
/*
 * 
 *      Loader.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This is the header for the object that takes in assembly source
 *          files and inserts the correct instructions into memory.
 * 
 *      Change Log:
 *          9/17/14 - Made class and derived classes Uncopyable
 *          9/10/14 - Created two separate methods for the different ISAs
 *          9/5/14 - Initial creation.
 * 
 * 
 */

#include<iostream>
#include<fstream>
#include<sstream>

#include "MemSys.hh"
#include "Utilities.hh"
#include "Accumulator.hh"
#include "Uncopyable.hh"

class Loader : private Uncopyable
{
    public:
        
        enum INST_SET
        {
            STACK_ISA,
            ACCUM_ISA
        };
        
        Loader(MemSys* mem);
        virtual ~Loader();
        
        virtual addr load(const std::string& file_path, const INST_SET& set);
        
    protected:
        virtual inst parseInstructionAccum(const std::string& inst_str);
        virtual inst parseInstructionStack(const std::string& inst_str);
        virtual addr parseAddress(const std::string& inst_str);
        
    private:
        MemSys* m_memory;
        
};

#endif
