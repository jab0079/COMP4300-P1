#ifndef LATCH_IF_ID_HH
#define LATCH_IF_ID_HH
/*
 * 
 *      Latch_IF_ID.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          Class defines the specific structure for the
 *          Latch object found between the fetch and the
 *          decode cycles of a pipelined simulator
 * 
 *      Change Log:
 *          10/14/14 - Initial creation
 * 
 * 
 */

#include <iostream>

#include "Utilities.hh"
#include "Latch.hh"
#include "MemSys.hh"

class Latch_IF_ID : public Latch
{
    public:
      Latch_IF_ID();
      virtual ~Latch_IF_ID();
      
      virtual void update();
      
      /*
       * Method pulls the old instruction 
       * from the previous cycle
       */
      virtual inst pullInstruction();
      
      /*
       * Method pushes from IF cycle into
       * the m_inst_buffer_new.
       */
      virtual void pushInstruction(const inst& i);
      
    protected:
      
    private:
      inst m_inst_buffer_old;
      inst m_inst_buffer_new;
      
      
};

#endif
