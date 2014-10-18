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
 *          10/18/14 - Added CYCLE_DESCRIPTOR enumeration
 *          10/3/14 - Added instruction counting
 *          9/17/14 - Made class and derived classes Uncopyable
 *          9/9/14 - Initial creation
 * 
 * 
 */

#include <iostream>

#include "MemSys.hh"
#include "Uncopyable.hh"

class Simulator : private Uncopyable
{
    public:
        
        //Constructors / Destructor -------------------------------------------
        Simulator(MemSys* mem);
        virtual ~Simulator();
        
        // Methods ------------------------------------------------------------
        virtual void run() = 0;
        
        // Gets and Sets-------------------------------------------------------
        virtual void setProgramCounter(const addr& in);
        virtual void setStackPointer(const addr& in);
        virtual addr getProgramCounter() const;
        virtual addr getStackPointer() const;
        virtual u_int32_t getInstructionCount() const;
        virtual u_int32_t getCycleCount() const;
        
    protected:
        
        //Members -------------------------------------------------------------
        MemSys* m_memory; //memory
        addr m_pc; //program counter
        addr m_sp; //stack pointer
        
        u_int32_t m_ic; //instruction count
        u_int32_t m_cycles; //total number of cycles
        
        enum CYCLE_DESCRIPTOR
        {
          CYCLE_FETCH,
          CYCLE_DECODE,
          CYCLE_EXECUTE,
          CYCLE_MEMORY,
          CYCLE_WRITEBACK
        };
        
    private:
      
/*        
        We don't want any client to accidentally use these
        methods, therefore we will declare but not implement
        Simulator(const Simulator&); //declarations only
        Simulator& operator=(const Simulator&);*/
        
};

#endif
