#ifndef UNCOPYABLE_HH
#define UNCOPYABLE_HH
/*
 * 
 *      Simulator.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This class is purely for blocking copying privilages
 *          to any derived class. Any derived class that attempts
 *          to be copied will throw an error at compile-time. This
 *          class is adopted from Scott Meyer's Effective C++ 3rd Ed.
 * 
 *      Change Log:
 *          9/17/14 - Initial creation
 * 
 * 
 */

class Uncopyable
{
    protected:
        //Constructors / Destructor -------------------------------------------
        Uncopyable() {}
        //need not be virtual destructor (p.39)
        ~Uncopyable() {}
        
    private:
        
        //We don't want any client to accidentally use these
        //methods, therefore we will declare but not implement
        Uncopyable(const Uncopyable&); //declarations only
        Uncopyable& operator=(const Uncopyable&);
        
};

#endif