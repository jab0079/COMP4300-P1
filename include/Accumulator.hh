#ifndef ACCUMULATOR_HH
#define ACCUMULATOR_HH
/*
 * 
 *      Accumulator.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This class defines the interface for the Accumulator Simulator
 * 
 *      Change Log:
 *          9/9/14 - Initial creation
 * 
 * 
 */

#include<iostream>

#include "Simulator.hh"


typedef u_int32_t reg; //32-bit registers

class Accumulator : public Simulator
{
    public:
        Accumulator(MemSys* mem);
        ~Accumulator();
        
        virtual void run();
        
        //Enumeration that defines
        //all instructions for this
        //architecture.
        enum INST_SET
        {
            LOAD,
            STO,
            ADD,
            MULT,
            END
        };
        
    protected:
        reg m_register;
        
    private:
};


#endif
