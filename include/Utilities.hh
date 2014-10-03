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

#include<iostream>
#include<algorithm>
#include<sstream>
#include<iomanip>

static const u_int8_t ACC_INST_LOAD = 0x01;
static const u_int8_t ACC_INST_STO = 0x02;
static const u_int8_t ACC_INST_MULT = 0x03;
static const u_int8_t ACC_INST_ADD = 0x04;
static const u_int8_t ACC_INST_END = 0x05;

static const u_int8_t STK_INST_PUSH = 0x01;
static const u_int8_t STK_INST_POP = 0x02;
static const u_int8_t STK_INST_MULT = 0x03;
static const u_int8_t STK_INST_ADD = 0x04;
static const u_int8_t STK_INST_END = 0x05;

enum GPR_INST_SET {
    GPR_ADDI, //0
    GPR_B, //1
    GPR_BEQZ, //2
    GPR_BGE, //3
    GPR_BNE, //4
    GPR_LA, //5
    GPR_LB, //6
    GPR_LI, //7
    GPR_SUBI, //8
    GPR_SYSCALL //9
};

enum SYSCALL_CODES {
    SYSCALL_PRINT_STR,
    SYSCALL_READ_STR,
    SYSCALL_EXIT
};

static const u_int8_t GPR_INST_SET_VALS[] =
{ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
static const u_int8_t GPR_INST_SET_CYCLES[] =
{6,4,5,5,6,3,6,8};

typedef u_int32_t reg; //32-bit registers

static std::string removeWhiteSpace(const std::string& str)
{
    std::string s = str;
    //Reused from http://www.cplusplus.com/forum/beginner/9557/
    s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
    return s;
}

static std::string removeComments(const std::string& str)
{
    std::string ret;
    int comment = str.find("#");
    if (comment > -1)
        ret = str.substr(0,comment);
    else
        ret = str;
    return ret;
}

//adpoted from ...
//http://stackoverflow.com/questions/5100718/int-to-hex-string-in-c
template< typename T >
static std::string int_to_hex( T i )
{
  std::stringstream stream;
  stream << "0x" 
         << std::setfill ('0') << std::setw(sizeof(T)*2) 
         << std::hex << i;
  return stream.str();
}



static u_int32_t strHexToAddr(const std::string& hexstr)
{
    unsigned int x;   
    std::stringstream ss;
    ss << std::hex << hexstr;
    ss >> x;
    return x;
}

static bool containsStr(const std::string& str, const std::string& pattern)
{
    if (str.length() < pattern.length()) return false;
    
    for (u_int32_t i = 0; i < str.length()-pattern.length()+1; i++)
    {
        for (u_int32_t j = 0; j < pattern.length(); j++)
        {
            if (str[i+j] != pattern[j])
                break;
            if (j == pattern.length()-1 && str[i+j] == pattern[j])
                return true;
        }
    }
    return false;
}


#endif
