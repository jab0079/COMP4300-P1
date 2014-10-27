#ifndef LATCH_HH
#define LATCH_HH
/*
 * 
 *      Latch.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This class defines the abstract behavior and
 *          abstract structure for any Latch object. Every latch
 *          object, as per the push model, must define an update
 *          method in which the new information is pushed into the
 *          old information.
 * 
 *      Change Log:
 *          10/24/14 - Added reset method
 *          10/14/14 - Initial creation
 * 
 * 
 */

#include <iostream>

#include "Uncopyable.hh"
#include "Utilities.hh"

class Latch : public Uncopyable
{
    public:
      Latch() {}
      virtual ~Latch() {}
      
      virtual void update() = 0;
      virtual void reset() = 0;
      virtual void reset_old() = 0;
      virtual void reset_new() = 0;
      
};

#endif
