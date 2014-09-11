/*
 * 
 *      Loader.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the driver for the loader that
 *          takes in assembly source files and loads the instructions
 *          into a MemSys object.
 * 
 *      Change Log:
 *          9/10/14 - Implemented load function and helper functions
 *          9/5/14 - Initial creation.
 * 
 * 
 */

#include "Loader.hh"

Loader::Loader(MemSys* mem) 
{
    if (mem)
        m_memory = mem;
    else
        m_memory = 0x0;
}

Loader::~Loader() 
{
    m_memory = 0x0; //just null it out, it's a reference
}

addr Loader::load(const std::string& file_path, const INST_SET& set)
{
    //Open file stream
    std::ifstream fs(file_path.c_str(), std::fstream::in);
    if (!fs.is_open())
    {
        //fail gracefully..
        std::cout << "Could not find file..." << std::endl;
    }
    
    addr ret = MemSys::BaseUserTextSegmentAddress;
    std::string line;
    bool userData = false;
    bool userText = false;
    u_int32_t text_offset = 0;
    
    while (std::getline(fs,line))
    {
        line = removeWhiteSpace(line);
        line = removeComments(line);
        if (line.compare("") == 0)
            continue; //skip these lines
        
        if (line.compare(".data") == 0)
        {
            userData = true;
            userText = false;
            continue;//we don't want to continue processing
        }
        
        if (line.compare(".text") == 0)
        {
            userData = false;
            userText = true;
            continue;//we don't want to continue processing
        }
        
        if (userData)
        { //should be the same for both Stack and Accumulator
            //parse address
            int colon = line.find(":");
            std::string address = line.substr(0,colon);
            addr address_i = strHexToAddr(address);
            //parse value
            std::string value = line.substr(colon+1,line.length());
            std::stringstream s(value);
            u_int32_t value_i;
            s >> value_i;
            
            //check address
            if (address_i >= MemSys::BaseUserDataSegmentAddress 
                && address_i < (MemSys::BaseUserDataSegmentAddress+MemSys::UserDataSegmentSize))
            { //write if ok
                m_memory->write(address_i, &value_i, sizeof(u_int32_t));
            }
            else
            {
                //fail gracefully...
            }
        }
        else if (userText)
        {
            inst instruction = 0;
            switch (set)
            {
                case STACK_ISA:
                    instruction = parseInstructionStack(line);
                    break;
                case ACCUM_ISA:
                    instruction = parseInstructionAccum(line);
                    break;
            }
            
            m_memory->write(MemSys::BaseUserTextSegmentAddress+text_offset, 
                            &instruction, 
                            sizeof(inst));
            text_offset += 4;
        }
    }
    
    fs.close();
    
    if (ret == 0)
    { //check output before returning
        //fail gracefully
    }
    return ret;
}

inst Loader::parseInstructionStack(const std::string& inst_str)
{
    if (containsStr(inst_str,"PUSH"))
        return (STK_INST_PUSH << 24) | parseAddress(inst_str);
    else if (containsStr(inst_str,"POP"))
        return (STK_INST_POP << 24) | parseAddress(inst_str);
    else if (containsStr(inst_str,"ADD"))
        return (STK_INST_ADD << 24);
    else if (containsStr(inst_str,"MULT"))
        return (STK_INST_MULT << 24);
    else if (containsStr(inst_str,"END"))
        return (STK_INST_END << 24);
}

inst Loader::parseInstructionAccum(const std::string& inst_str)
{
    if (containsStr(inst_str,"LOAD"))
        return (ACC_INST_LOAD << 24) | parseAddress(inst_str);
    else if (containsStr(inst_str,"STO"))
        return (ACC_INST_STO << 24) | parseAddress(inst_str);
    else if (containsStr(inst_str,"ADD"))
        return (ACC_INST_ADD << 24) | parseAddress(inst_str);
    else if (containsStr(inst_str,"MULT"))
        return (ACC_INST_MULT << 24) | parseAddress(inst_str);
    else if (containsStr(inst_str,"END"))
        return (ACC_INST_END << 24);
}

addr Loader::parseAddress(const std::string& inst_str)
{
    addr address = 0;
    std::string address_str = "";
    
    int address_start = inst_str.rfind("x");
    if (address_start > -1)
    {
        address_str = inst_str.substr(address_start+1,inst_str.length());
        address = strHexToAddr(address_str);
    }
    return address;
}


