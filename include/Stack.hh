#ifndef STACK_HH_
#define STACK_HH_

/*
 *
 *      Stack.hh
 *
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 *
 *      Description:
 *          This class defines the interface for the stack-based simulator.
 *
 *      Change Log:
 *          9/8/14 - Created initial interface
 *
 *
 */

#include<iostream>

#include "Simulator.hh"


typedef u_int32_t reg; //32-bit registers

class Stack : public Simulator
{
    public:
        Stack(MemSys* mem);
        ~Stack();

        virtual void run();

        //Enumeration that defines
        //all instructions for this
        //architecture.
        enum INST_SET
        {
            PUSH,
            POP,
            ADD,
            MULT,
            END
        };

    protected:
        reg m_register;

    private:
};

#endif /* STACK_HH_ */
