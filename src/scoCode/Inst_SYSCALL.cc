/*
 *
 *      Inst_SYSCALL.cc
 *
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 *
 *      Description:
 *          This source file defines the implementation for the control
 *          that manipulates a Simulator reference based on how the
 *          definition for SYSCALL is described in the MIPS architecture.
 *
 *      Change Log:
 *          12/2/14 - Initial Creation
 *
 *
 */
#include "Inst_SYSCALL.hh"

Inst_SYSCALL::Inst_SYSCALL(ScoreboardSimulator* simu, inst the_instruction)
: Instruction(simu, the_instruction)
{}

Inst_SYSCALL::~Inst_SYSCALL() {}

Inst_SYSCALL::Inst_SYSCALL(const Inst_SYSCALL& other)
: Instruction(other)
{}

Instruction* Inst_SYSCALL::clone() const { return new Inst_SYSCALL(*this); }

/* Stage Methods ------------------------------------------------------------*/
void Inst_SYSCALL::decode()
{
    //Kernel Code...
    u_int32_t sys_code = sim->getRegister(REG_VAL_1);
    addr str_addr = MemSys::BaseUserDataSegmentAddress | sim->getRegister(REG_ARG_1);
    switch(sys_code)
    {
        case SYSCALL_PRINT_STR:
        {
            u_int8_t letter = *((u_int8_t*)sim->getMemorySystem()
                ->read(str_addr, sizeof(u_int8_t))); // Read first char
            std::string str;
            str_addr++;
            while (letter != '\0') // Print each char in the string until NUL terminator
            {
                str += letter;
                letter = *((u_int8_t*)sim->getMemorySystem()
                    ->read(str_addr, sizeof(u_int8_t)));
                str_addr++;
            } 
            std::cout << str << std::endl;
        }
        break;
    
        case SYSCALL_READ_STR:
        {
            std::string input;
            std::cin >> input;
            for (u_int32_t i = 0; i < input.length(); i++)    // Write each char to memory
            {
                sim->getMemorySystem()->write(str_addr, &input[i], sizeof(u_int8_t));
                str_addr++;
            }
            u_int8_t null_c = '\0';             // Add NUL terminator
            sim->getMemorySystem()->write(str_addr, &null_c, sizeof(u_int8_t));
        }
        break;
        
        case SYSCALL_PRINT_INT:
        {
            u_int32_t int_print = sim->getRegister(REG_ARG_1); // Read integer
            std::ostringstream os;
            os << int_print;
            std::string str = os.str();
            std::cout << str << std::endl; 
        }
        break;
        
        case SYSCALL_EXIT:
            sim->setUserMode(false);
            break;
        default:
            break;
    }
}

void Inst_SYSCALL::fetch_operands()
{
    //blank for syscall
}

void Inst_SYSCALL::execute()
{
    //blank for syscall
}

void Inst_SYSCALL::memory()
{
    //blank for syscall
}

void Inst_SYSCALL::write_back()
{
    //blank for syscall
}


