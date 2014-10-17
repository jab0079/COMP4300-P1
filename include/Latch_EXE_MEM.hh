#ifndef LATCH_EXE_MEM_HH
#define LATCH_EXE_MEM_HH
/*
 * 
 *      Latch_EXE_MEM.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          Class defines the specific structure for the
 *          Latch object found between the execution and the
 *          memory cycles of a pipelined simulator
 * 
 *      Change Log:
 *          10/14/14 - Initial creation
 * 
 * 
 */

#include <iostream>

#include "Latch.hh"

class Latch_EXE_MEM : public Latch
{
    public:
      Latch_EXE_MEM();
      virtual ~Latch_EXE_MEM();
      
      virtual void update();
      
    protected:
      
    private:
      
};

#endif
