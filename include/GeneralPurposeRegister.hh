#ifndef GENERALPURPOSEREGISTER_HH
#define GENERALPURPOSEREGISTER_HH
/*
 * 
 *      GeneralPurposeRegister.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This class defines the interface for the GeneralPurposeRegister Simulator
 * 
 *      Change Log:
 * 	    10/3/14 - Added Register Constants and decodeInstr method
 *          9/29/14 - Initial Creation
 * 
 * 
 */

#include<iostream>
#include<bitset>

#include "Simulator.hh"
#include "Utilities.hh"

static const u_int32_t REGISTER_COUNT = 32;
static const u_int32_t REG_VAL_1 = 2;	// Register $2 = $v0 from MIPS
static const u_int32_t REG_ARG_1 = 4;	// Register $4 = $a0 from MIPS
static const u_int32_t REG_ARG_2 = 5;	// Register $5 = $a1 from MIPS

class GeneralPurposeRegister : public Simulator
{
    public:
        GeneralPurposeRegister(MemSys* mem);
        virtual ~GeneralPurposeRegister();
        
        virtual void run();
        virtual int32_t decodeInstr(const u_int32_t& instr, const u_int8_t& num_bits);
        
    protected:
        reg m_register[REGISTER_COUNT]; //Utilities.hh
        
    private:
};


#endif //GENERALPURPOSEREGISTER_HH
