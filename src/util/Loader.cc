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
 * 			10/14/14 - Added NOP Instruction to GPR
 *          10/2/14 - Added GPR instruction set implementation
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
        { //should be the same for all
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
                case GPR_ISA:
                    instruction = parseInstructionGPR(line);
                    break;
                case SCOB_ISA:
                    instruction = parseInstructionSCOB(line);
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
    
    return -1;
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
    
    return -1;
}

inst Loader::parseInstructionGPR(const std::string& inst_str)
{
    std::string inst_token;
    u_int32_t dollar_loc=inst_str.find("$");
    if (dollar_loc!=std::string::npos)
	  inst_token = inst_str.substr(0,inst_str.find("$"));
    else
	  inst_token = inst_str.substr(0,inst_str.find("0x"));   
    for(u_int32_t i=0;i<inst_token.length();i++)
    {
	  inst_token[i]=toupper(inst_token[i]);
    }
    if (inst_token.compare("ADD")==0)
        //ADD Rdest, Rsrc1, Rsrc2
        //[8-bit op][5-bit dest][5-bit src1][5-bit src2][9-bit usused]
        return parse3Reg(GPR_INST_SET_VALS[GPR_ADD], inst_str);
    else if (inst_token.compare("ADDI")==0)
        //ADDI Rdest, Rsrc1, Imm
        //[8-bit op][5-bit dest][5-bit src][14-bit immediate]
        return parse2Reg1Val(GPR_INST_SET_VALS[GPR_ADDI], inst_str);
    else if (inst_token.compare("B")==0)
        //B label
        //[8-bit op][24-bit relative offset]
        return (GPR_INST_SET_VALS[GPR_B] << 24) | parseOffset(inst_str);
    else if (inst_token.compare("BEQZ")==0)
        //BEGZ Rsrc1, label
        //[8-bit op][5-bit src][19-bit relative offset]
        return parse1Reg1Val(GPR_INST_SET_VALS[GPR_BEQZ], inst_str);
    else if (inst_token.compare("BGE")==0)
        //BGE Rsrc1, Rsrc2, label
        //[8-bit op][5-bit src1][5-bit src2][14-bit offset]
        return parse2Reg1Val(GPR_INST_SET_VALS[GPR_BGE], inst_str);
    else if (inst_token.compare("BNE")==0)
        //BNE Rsrc1, Rsrc2, label
        //[8-bit op][5-bit src1][5-bit src2][14-bit offset]
        return parse2Reg1Val(GPR_INST_SET_VALS[GPR_BNE], inst_str);
    else if (inst_token.compare("LA")==0)
        //LA Rdest, label
        //[8-bit op][5-bit dest][19-bit address]
        return parse1Reg1Val(GPR_INST_SET_VALS[GPR_LA], inst_str);
    else if (inst_token.compare("LB")==0) {
        //LB Rdest, offset(Rsrc1)
        //[8-bit op][5-bit Rdest][5-bit Rsrc1][14-bit offset]
		int comma_loc = inst_str.find(",");
		int open_paren_loc = inst_str.find("(");
		int close_paren_loc = inst_str.find(")");
		std::string offset_str = inst_str.substr(comma_loc+2,open_paren_loc-comma_loc-2);
		std::string rsrc1_str = inst_str.substr(open_paren_loc+1,close_paren_loc-open_paren_loc-1);
		std::string inst_str_modified = inst_str.substr(1,comma_loc);
		std::stringstream s;
		if (offset_str.compare("") == 0)
			offset_str = "0";
		s << offset_str;
		int off_val;
		s >> off_val;
		inst_str_modified += rsrc1_str + "," + int_to_hex(off_val);
		return parse2Reg1Val(GPR_INST_SET_VALS[GPR_LB], inst_str_modified);
    }
    else if (inst_token.compare("LI")==0)
        //LI Rdest, Imm
        //[8-bit op][5-bit Rsrc1][19-bit immediate]
        return parse1Reg1Val(GPR_INST_SET_VALS[GPR_LI], inst_str);
    else if (inst_token.compare("SUBI")==0)
        //SUBI Rdest, Rsrc1, Imm
        //[8-bit op][5-bit dest][5-bit src][14-bit immediate]
        return parse2Reg1Val(GPR_INST_SET_VALS[GPR_SUBI], inst_str);
    else if (inst_token.compare("SYSCALL")==0)
        //SYSCALL
        //[8-bit op][24-bit unused]
        return (GPR_INST_SET_VALS[GPR_SYSCALL] << 24);
    else if (inst_token.compare("NOP") == 0)
        return (GPR_INST_SET_VALS[GPR_NOP] << 24);
    
    return -1;
}

inst Loader::parseInstructionSCOB(const std::string& inst_str)
{
    std::string inst_token;
    u_int32_t dollar_loc=inst_str.find("$");
    if (dollar_loc!=std::string::npos)
      inst_token = inst_str.substr(0,inst_str.find("$"));
    else
      inst_token = inst_str.substr(0,inst_str.find("0x"));   
    for(u_int32_t i=0;i<inst_token.length();i++)
    {
      inst_token[i]=toupper(inst_token[i]);
    }
    if (inst_token.compare("ADD")==0)
        //ADD Rdest, Rsrc1, Rsrc2
        //[8-bit op][5-bit dest][5-bit src1][5-bit src2][9-bit usused]
        return parse3Reg(SCOB_INST_SET_VALS[SCOB_ADD], inst_str);
    else if (inst_token.compare("ADDI")==0)
        //ADDI Rdest, Rsrc1, Imm
        //[8-bit op][5-bit dest][5-bit src][14-bit immediate]
        return parse2Reg1Val(SCOB_INST_SET_VALS[SCOB_ADDI], inst_str);
    else if (inst_token.compare("B")==0)
        //B label
        //[8-bit op][24-bit relative offset]
        return (SCOB_INST_SET_VALS[SCOB_B] << 24) | parseOffset(inst_str);
    else if (inst_token.compare("BEQZ")==0)
        //BEGZ Rsrc1, label
        //[8-bit op][5-bit src][19-bit relative offset]
        return parse1Reg1Val(SCOB_INST_SET_VALS[SCOB_BEQZ], inst_str);
    else if (inst_token.compare("BGE")==0)
        //BGE Rsrc1, Rsrc2, label
        //[8-bit op][5-bit src1][5-bit src2][14-bit offset]
        return parse2Reg1Val(SCOB_INST_SET_VALS[SCOB_BGE], inst_str);
    else if (inst_token.compare("BNE")==0)
        //BNE Rsrc1, Rsrc2, label
        //[8-bit op][5-bit src1][5-bit src2][14-bit offset]
        return parse2Reg1Val(SCOB_INST_SET_VALS[SCOB_BNE], inst_str);
    else if (inst_token.compare("LA")==0)
        //LA Rdest, label
        //[8-bit op][5-bit dest][19-bit address]
        return parse1Reg1Val(SCOB_INST_SET_VALS[SCOB_LA], inst_str);
    else if (inst_token.compare("LB")==0)
        //LB Rdest, offset(Rsrc1)
        //[8-bit op][5-bit Rdest][5-bit Rsrc1][14-bit offset]
        return parseRegisterOffset(SCOB_INST_SET_VALS[SCOB_LB], inst_str);
    else if (inst_token.compare("LI")==0)
        //LI Rdest, Imm
        //[8-bit op][5-bit Rsrc1][19-bit immediate]
        return parse1Reg1Val(SCOB_INST_SET_VALS[SCOB_LI], inst_str);
    else if (inst_token.compare("SUBI")==0)
        //SUBI Rdest, Rsrc1, Imm
        //[8-bit op][5-bit dest][5-bit src][14-bit immediate]
        return parse2Reg1Val(SCOB_INST_SET_VALS[SCOB_SUBI], inst_str);
    else if (inst_token.compare("SYSCALL")==0)
        //SYSCALL
        //[8-bit op][24-bit unused]
        return (SCOB_INST_SET_VALS[SCOB_SYSCALL] << 24);
    else if (inst_token.compare("NOP") == 0)
        //NOP
        //[8-bit op][24-bit usused]
        return (SCOB_INST_SET_VALS[SCOB_NOP] << 24);
    else if (inst_token.compare("FADD") == 0)
        //FADD Rdest, Rsrc1, Rsrc2
        //[8-bit op][5-bit dest][5-bit src1][5-bit src2][9-bit usused]
        return parse3Reg(SCOB_INST_SET_VALS[SCOB_FADD], inst_str);
    else if (inst_token.compare("FMUL") == 0)
        //FMUL Rdest, Rsrc1, Rsrc2
        //[8-bit op][5-bit dest][5-bit src1][5-bit src2][9-bit usused]
        return parse3Reg(SCOB_INST_SET_VALS[SCOB_FMUL], inst_str);
    else if (inst_token.compare("FSUB") == 0)
        //FSUB Rdest, Rsrc1, Rsrc2
        //[8-bit op][5-bit dest][5-bit src1][5-bit src2][9-bit usused]
        return parse3Reg(SCOB_INST_SET_VALS[SCOB_FSUB], inst_str);
    else if (inst_token.compare("L.D") == 0)
        //L.D Rdest, offset(Rsrc1)
        //[8-bit op][5-bit Rdest][5-bit Rsrc1][14-bit offset]
        return parseRegisterOffset(SCOB_INST_SET_VALS[SCOB_LD], inst_str);
    else if (inst_token.compare("S.D") == 0)
        //S.D Rdest, offset(Rsrc1)
        //[8-bit op][5-bit Rdest][5-bit Rsrc1][14-bit offset]
        return parseRegisterOffset(SCOB_INST_SET_VALS[SCOB_SD], inst_str);
        
    return -1;
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

u_int32_t Loader::parseValue(const std::string& hexStr, const u_int8_t& num_bits)
{
    std::bitset<32> val32(strHexToAddr(hexStr));
    std::bitset<32> val;
    //take first num_bits bits
    for (int i = 0; i < num_bits; i++)
        val.set(i, val32[i]);
    
    return val.to_ulong();
}


u_int32_t Loader::parseOffset(const std::string& inst_str)
{
    int hex_loc = inst_str.find("x");
    return parseValue(inst_str.substr(hex_loc-1,inst_str.length()),24);
}

inst Loader::parse3Reg(const u_int8_t& opcode, const std::string& inst_str)
{
    std::stringstream s;
    inst instruction = 0;
    std::string token_str = inst_str; //we will modify this so copy it
    instruction = instruction | (opcode << 24);
    
    //parse registers
    for (int i = 0; i < 3; i++)
        instruction = instruction | (parseRegister(token_str) << (19-i*5));
    
    return instruction;
}

inst Loader::parse2Reg1Val(const u_int8_t& opcode, const std::string& inst_str)
{
    std::stringstream s;
    inst instruction = 0;
    std::string token_str = inst_str; //we will modify this so copy it
    instruction = instruction | (opcode << 24);
    
    //parse registers
    for (int i = 0; i < 2; i++)
        instruction = instruction | (parseRegister(token_str) << (19-i*5));
    
    instruction = instruction | parseValue(token_str, 14);
    
    return instruction;
}

inst Loader::parse1Reg1Val(const u_int8_t& opcode, const std::string& inst_str)
{
    std::stringstream s;
    inst instruction = 0;
    std::string token_str = inst_str; //we will modify this so copy it
    instruction = instruction | (opcode << 24);
    instruction = instruction | (parseRegister(token_str) << 19);    
    instruction = instruction | parseValue(token_str, 19);

    return instruction;
}

inst Loader::parseRegisterOffset(const u_int8_t& opcode, const std::string& inst_str)
{
    int comma_loc = inst_str.find(",");
    int open_paren_loc = inst_str.find("(");
    int close_paren_loc = inst_str.find(")");
    std::string offset_str = inst_str.substr(comma_loc+2,open_paren_loc-comma_loc-2);
    std::string rsrc1_str = inst_str.substr(open_paren_loc+1,close_paren_loc-open_paren_loc-1);
    std::string inst_str_modified = inst_str.substr(1,comma_loc);
    std::stringstream s;
    if (offset_str.compare("") == 0)
        offset_str = "0";
    s << offset_str;
    int off_val;
    s >> off_val;
    inst_str_modified += rsrc1_str + "," + int_to_hex(off_val);
    return parse2Reg1Val(SCOB_INST_SET_VALS[SCOB_LB], inst_str_modified);
}

//inst_str will be modified!
u_int32_t Loader::parseRegister(std::string& inst_str)
{
    u_int32_t reg_loc = inst_str.find("$");
    bool isFP = false;
    if (inst_str.at(reg_loc + 1) == (char)'f')
    {
        isFP = true;
        reg_loc++; //skip the f
    }
    u_int32_t comma_loc = inst_str.find(",");
    std::string reg_str = inst_str.substr(reg_loc+1,comma_loc-reg_loc-1);
    u_int32_t register_num = 0;
    std::stringstream s;
    s.clear();
    s << reg_str;
    s >> register_num;
    if (isFP) {
        register_num += 16; //skip 16 non floating point registers
    }
    inst_str = inst_str.substr(comma_loc+1); //after the comma
    return register_num;
}





