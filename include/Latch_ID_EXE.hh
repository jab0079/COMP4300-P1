#ifndef LATCH_ID_EXE_HH
#define LATCH_ID_EXE_HH
/*
 * 
 *      Latch_ID_EXE.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          Class defines the specific structure for the
 *          Latch object found between the decode and the
 *          execution cycles of a pipelined simulator
 * 
 *      Change Log:
 *          10/14/14 - Initial creation
 * 
 * 
 */

#include <iostream>

#include "Latch.hh"

class Latch_ID_EXE : public Latch
{
    public:
      Latch_ID_EXE();
      virtual ~Latch_ID_EXE();
      
      virtual void update();
      
      
    protected:
      
      
    private:
      
};

#endif
