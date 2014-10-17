#ifndef LATCH_MEM_WB_HH
#define LATCH_MEM_WB_HH
/*
 * 
 *      Latch_MEM_WB.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          Class defines the specific structure for the
 *          Latch object found between the memory and the
 *          write-back cycles of a pipelined simulator
 * 
 *      Change Log:
 *          10/14/14 - Initial creation
 * 
 * 
 */

#include <iostream>

#include "Latch.hh"

class Latch_MEM_WB : public Latch
{
    public:
      Latch_MEM_WB();
      virtual ~Latch_MEM_WB();
      
      virtual void update();
      
    protected:
      
    private:
      
};

#endif
