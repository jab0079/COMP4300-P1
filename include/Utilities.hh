#ifndef UTILITIES_HH
#define UTILITIES_HH
/*
 * 
 *      Utilities.hh
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines common utility functions global
 *          to all sources in the project
 * 
 *      Change Log:
 *          9/9/14 - Initial creation
 * 
 * 
 */

//Defines a macro that safely deletes objects
//by checking if it exists, deleting it, and nulling it out.
#define SAFE_DELETE(x) if(x) delete(x); x=0x0;

#endif
