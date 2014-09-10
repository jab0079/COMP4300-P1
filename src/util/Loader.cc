/*
 * 
 *      Loader.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the driver for the loader that
 *          takes in assembly source files and loads the instructions
 *          into a MemSys object.
 * 
 *      Change Log:
 *          9/5/14 - Initial creation.
 * 
 * 
 */

#include "Loader.hh"

Loader::Loader(MemSys* mem) 
{
    if (mem)
        m_memory = mem;
    else
        m_memory = 0x0;
}

Loader::~Loader() {}

addr Loader::load(const std::string& file_path)
{
    
}

addr Loader::loadUserText(std::ifstream& strm)
{
    
}

addr  Loader::loadUserData(std::ifstream& strm)
{
    
}


