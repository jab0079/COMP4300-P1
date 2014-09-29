#ifndef GENERALPURPOSEREGISTER_HH
#define GENERALPURPOSEREGISTER_HH
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
 *          9/29/14 - Initial Creation
 * 
 * 
 */

#include<iostream>

#include "Simulator.hh"
#include "Utilities.hh"

static const u_int32_t REGISTER_COUNT = 32;

class GeneralPurposeRegister : public Simulator
{
    public:
        GeneralPurposeRegister(MemSys* mem);
        virtual ~GeneralPurposeRegister();
        
        virtual void run();
        
    protected:
        reg m_register[REGISTER_COUNT]; //Utilities.hh
        
    private:
};


#endif //GENERALPURPOSEREGISTER_HH
