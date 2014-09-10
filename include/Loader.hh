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
 *          9/5/14 - Initial creation.
 * 
 * 
 */

#include<iostream>
#include<fstream>

#include "MemSys.hh"

class Loader
{
    public:
        Loader(MemSys* mem);
        ~Loader();
        
        virtual addr load(const std::string& file_path);
        
    protected:
        virtual addr loadUserText(std::ifstream& strm);
        virtual addr loadUserData(std::ifstream& strm);
        
    private:
        MemSys* m_memory;
        
};

#endif
