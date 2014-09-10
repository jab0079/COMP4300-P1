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
 *          9/10/14 - Added instruction set static members
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
        
        //INSTRUCTION SET------------------------------------------------------
        
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
        
        static const u_int8_t ACC_INST_LOAD; //see impl for constant
        static const u_int8_t ACC_INST_STO;
        static const u_int8_t ACC_INST_ADD;
        static const u_int8_t ACC_INST_MULT;
        static const u_int8_t ACC_INST_END;
        
        //---------------------------------------------------------------------
        
    protected:
        reg m_register;
        
    private:
};


#endif
