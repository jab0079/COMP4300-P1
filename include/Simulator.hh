#ifndef SIMULATOR_HH
#define SIMULATOR_HH
/*
 * 
 *      Simulator.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This class defines the interface for all simulators. The intention
 *          is to have this class provide a generic representation of how
 *          simulators should behave and shared attributes. This is an abstract
 *          class that should simply be a template for simulators
 * 
 *      Change Log:
 *          9/9/14 - Initial creation
 * 
 * 
 */

#include <iostream>

#include "MemSys.hh"

class Simulator
{
    public:
        
        //Constructors / Destructor -------------------------------------------
        Simulator(MemSys* mem);
        ~Simulator();
        
        // Methods ------------------------------------------------------------
        virtual void run() = 0;
        
        // Gets and Sets-------------------------------------------------------
        virtual void setProgramCounter(const addr& in);
        virtual void setStackPointer(const addr& in);
        virtual addr getProgramCounter() const;
        virtual addr getStackPointer() const;
        
    protected:
        
        //Members -------------------------------------------------------------
        MemSys* m_memory; //memory
        addr m_pc; //program counter
        addr m_sp; //stack pointer
        
    private:
        
};

#endif
