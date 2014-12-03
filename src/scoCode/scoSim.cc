/*
 * 
 *      scoSim.cc
 * 
 *      Contributors:   Adam Eichelkraut
 *                      Jared Brown
 *      Contact:        ake0005@tigermail.auburn.edu
 *                      jab0079@tigermail.auburn.edu
 * 
 *      Description: 
 *          This source file defines the implementation for the Scoreboard Simulator
 * 
 *      Change Log:
 *          12/2/14 - Initial Creation
 * 
 * 
 */
#include "scoSim.hh"

ScoreboardSimulator::ScoreboardSimulator(MemSys* mem) 
: Simulator(mem)
{
  m_usermode = false;

}

ScoreboardSimulator::~ScoreboardSimulator()
{

}

void ScoreboardSimulator::run()
{
    std::cout << "\tStarting Pipeline..." << std::endl;

    std::cout << "\tEnding Pipeline..." << std::endl;
}

/* SETS ---------------------------------------------------------------------*/
void ScoreboardSimulator::setRegister(const u_int8_t& regnum, const reg& val)
{
    if (regnum >= 0 && regnum < REGISTER_COUNT)
        m_register[regnum] = val;
}

void ScoreboardSimulator::setFPRegister(const u_int8_t& regnum, const reg_d& val)
{
    if (regnum >= 0 && regnum < FLOATING_POINT_REGISTERS)
        m_register_d[regnum] = val;
}

void ScoreboardSimulator::setUserMode(const bool& isInUserMode)
{
    m_usermode = isInUserMode;
}

/* GETS ---------------------------------------------------------------------*/
reg ScoreboardSimulator::getRegister(const u_int8_t& regnum) const
{ return m_register[regnum]; }

reg_d ScoreboardSimulator::getFPRegister(const u_int8_t& regnum) const
{ return m_register_d[regnum]; }

bool ScoreboardSimulator::isInUserMode() const
{ return m_usermode; }



