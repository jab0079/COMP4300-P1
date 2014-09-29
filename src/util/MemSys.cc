/*
 * 
 *      MemSys.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 *      Description: 
 *          This class defines the implementation for the memory system (MemSys)
 *          used by the simulators in this application.
 * 
 *      Change Log:
 *          9/29/14 - Added exceptions to read and write
 *          9/11/14 - Changed how system checks reading addresses
 *          9/8/14 - Implemented read/write functions and added the
 *                      outputSegment function
 *          9/5/14 - Initial implementation stubs created
 *          9/5/14 - Initial creation detailing description.
 * 
 * 
 */
#include "MemSys.hh"

#define BLOCK 4096

//Segment Sizes...(in bytes)
const unsigned int MemSys::UserTextSegmentSize = BLOCK;
const unsigned int MemSys::UserDataSegmentSize = BLOCK;
const unsigned int MemSys::KernelTextSegmentSize = BLOCK;
const unsigned int MemSys::KernelDataSegmentSize = BLOCK;
const unsigned int MemSys::StackSegmentSize = BLOCK;

//Segment Address Bases...
const addr MemSys::BaseUserTextSegmentAddress = 0x00100000;
const addr MemSys::BaseUserDataSegmentAddress = 0x00200000;
const addr MemSys::BaseKernelTextSegmentAddress = 0x00300000;
const addr MemSys::BaseKernelDataSegmentAddress = 0x00400000;
const addr MemSys::BaseStackSegmentAddress = 0x00500000;

MemSys::MemSys()
{
    //Initialize Tops To Bases (fresh memory)
    m_usertext_top = BaseUserTextSegmentAddress;
    m_userdata_top = BaseUserDataSegmentAddress;
    m_kerneltext_top = BaseKernelTextSegmentAddress;
    m_kerneldata_top = BaseKernelDataSegmentAddress;
    m_stack_top = BaseStackSegmentAddress;
    
    m_usertext_seg = (char*)calloc(UserTextSegmentSize,sizeof(char));
    m_userdata_seg = (char*)calloc(UserDataSegmentSize,sizeof(char));
    m_kerneltext_seg = (char*)calloc(KernelTextSegmentSize,sizeof(char));
    m_kerneldata_seg = (char*)calloc(KernelDataSegmentSize,sizeof(char));
    m_stack_seg = (char*)calloc(StackSegmentSize,sizeof(char));
}

MemSys::~MemSys()
{
    free(m_usertext_seg);
    free(m_userdata_seg);
    free(m_kerneltext_seg);
    free(m_kerneldata_seg);
    free(m_stack_seg);
}

void* MemSys::read(const addr& address, const unsigned int& size) const
throw(std::range_error)
{
    //get the base address to determine which segment to access
    addr base = (address & 0x00F00000);
    
    unsigned int start = address & 0x000FFFFF; //needed for indexing into arrays
    
    try
    {
        switch (base)
        {
            case (BaseUserTextSegmentAddress):
                //Sanity check
                if (size > UserTextSegmentSize 
                    || address > BaseUserTextSegmentAddress+UserTextSegmentSize)
                    throw std::range_error("MemSys out of bounds read: BaseUserTextSegmentAddress");
                
                { //need block so ret is not visible to other cases
                    void* ret = calloc(size,sizeof(char)); 
                    memcpy(ret, m_usertext_seg+start, size);
                    return ret;
                }
                break;
            case (BaseUserDataSegmentAddress):
                //Sanity check
                if (size > UserDataSegmentSize 
                    || address > BaseUserDataSegmentAddress+UserDataSegmentSize)
                    throw std::range_error("MemSys out of bounds read: BaseUserDataSegmentAddress");
                
                { //need block so ret is not visible to other cases
                    void* ret = calloc(size,sizeof(char)); 
                    memcpy(ret, m_userdata_seg+start, size);
                    return ret;
                }
                break;
            case (BaseKernelTextSegmentAddress):
                //Sanity check
                if (size > KernelTextSegmentSize 
                    || address > BaseKernelTextSegmentAddress+KernelTextSegmentSize)
                    throw std::range_error("MemSys out of bounds read: BaseKernelTextSegmentAddress");
                
                { //need block so ret is not visible to other cases
                    void* ret = calloc(size,sizeof(char)); 
                    memcpy(ret, m_kerneltext_seg+start, size);
                    return ret;
                }
                break;
            case (BaseKernelDataSegmentAddress):
                //Sanity check
                if (size > KernelDataSegmentSize 
                    || address > BaseKernelDataSegmentAddress+KernelDataSegmentSize)
                    throw std::range_error("MemSys out of bounds read: BaseKernelDataSegmentAddress");
                
                { //need block so ret is not visible to other cases
                    void* ret = calloc(size,sizeof(char)); 
                    memcpy(ret, m_kerneldata_seg+start, size);
                    return ret;
                }
                break;
            case (BaseStackSegmentAddress):
                //Sanity check
                if (size > StackSegmentSize 
                    || address > BaseStackSegmentAddress+StackSegmentSize)
                    throw std::range_error("MemSys out of bounds read: BaseStackSegmentAddress");
                
                { //need block so ret is not visible to other cases
                    char* ret = (char*)calloc(size,sizeof(char)); 
                    memcpy(ret, (const char *)m_stack_seg+start, size);
                    return ret;
                }
                break;
            default:
                throw std::range_error("MemSys invalid base read specifier!");
                break;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

bool MemSys::write(const addr& address, const void* data, const unsigned int& size)
throw(std::range_error)
{
    //get the base address to determine which segment to access
    addr base = (address & 0x00F00000);
    unsigned int start = address & 0x000FFFFF; //needed for indexing into arrays
    try
    {
        switch (base)
        {
            case (BaseUserTextSegmentAddress):
                
                if (size > UserTextSegmentSize 
                    || address + size > BaseUserTextSegmentAddress+UserTextSegmentSize)
                    throw std::range_error("MemSys out of bounds write: UserTextSegmentSize");
                
                memcpy(m_usertext_seg+start, data, size);
                
                if (address + size > m_usertext_top)
                    m_usertext_top = address + size;
                return true;
                
            case (BaseUserDataSegmentAddress):
                
                if (size > UserDataSegmentSize 
                    || address + size > BaseUserDataSegmentAddress+UserDataSegmentSize)
                    throw std::range_error("MemSys out of bounds write: BaseUserDataSegmentAddress");
                
                memcpy(m_userdata_seg+start, data, size);
                
                if (address + size > m_userdata_top)
                    m_userdata_top = address + size;
                return true;
                
            case (BaseKernelTextSegmentAddress):
                
                if (size > KernelTextSegmentSize 
                    || address + size > BaseKernelTextSegmentAddress+KernelTextSegmentSize)
                    throw std::range_error("MemSys out of bounds write: BaseKernelTextSegmentAddress");
                
                memcpy(m_kerneltext_seg+start, data, size);
                
                if (address + size > m_kerneltext_top)
                    m_kerneltext_top = address + size;
                return true;
                
            case (BaseKernelDataSegmentAddress):
                
                if (size > KernelDataSegmentSize 
                    || address + size > BaseKernelDataSegmentAddress+KernelDataSegmentSize)
                    throw std::range_error("MemSys out of bounds write: BaseKernelDataSegmentAddress");
                
                memcpy(m_kerneldata_seg+start, data, size);
                
                if (address + size > m_kerneldata_top)
                    m_kerneldata_top = address + size;
                return true;
                
            case (BaseStackSegmentAddress):
                
                if (size > StackSegmentSize 
                    || address + size > BaseStackSegmentAddress+StackSegmentSize)
                    throw std::range_error("MemSys out of bounds write: BaseStackSegmentAddress");
                
                memcpy(m_stack_seg+start, data, size);
                
                if (address + size > m_stack_top)
                    m_stack_top = address + size;
                return true;
                
            default:
                throw std::range_error("MemSys invalid base write specifier!");
                return false;
                break;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void MemSys::outputSegment(const Segment& segment) const
{
    const char* seg = 0x0;
    int size = 0;
    switch (segment)
    {
        case (USER_TEXT):
            std::cout << "---------- User Text Segment --------------" << std::endl;
            seg = m_usertext_seg;
            size = m_usertext_top & 0x000FFFFF;
            break;
        case (USER_DATA):
            std::cout << "---------- User Data Segment --------------" << std::endl;
            seg = m_userdata_seg;
            size = m_userdata_top & 0x000FFFFF;
            break;
        case (KERNEL_TEXT):
            std::cout << "---------- Kernel Text Segment ------------" << std::endl;
            seg = m_kerneltext_seg;
            size = m_kerneltext_top & 0x000FFFFF;
            break;
        case (KERNEL_DATA):
            std::cout << "---------- Kernel Data Segment ------------" << std::endl;
            seg = m_kerneldata_seg;
            size = m_kerneldata_top & 0x000FFFFF;
            break;
        case (STACK):
            std::cout << "---------- Stack Segment ------------------" << std::endl;
            seg = m_stack_seg;
            size = m_stack_top & 0x000FFFFF;
            break;
    }
    
    if (seg)
    {
        int counter = 0;
        int row = 0;
        for (int i = 0; i < size; i++)
        {
            std::cout << (u_int32_t)seg[i] << " ";
            counter++;
            if (counter == 4)
            {
                std::cout << "\t\t" << *((u_int32_t *)(seg+(row*4)));
                std::cout << std::endl;
                counter = 0;
                row++;
            }
        }
    }
    std::cout << std::endl << "-------------------------------------------" << std::endl;
}



