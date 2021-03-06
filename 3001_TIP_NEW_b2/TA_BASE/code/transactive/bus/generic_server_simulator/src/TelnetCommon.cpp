/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/generic_server_simulator/src/TelnetCommon.cpp $
  * @author:  Robert van Hugten
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * 
  */

#ifdef WIN32
#pragma warning (disable : 4786)
#endif // #ifdef WIN32

#include "bus/generic_server_simulator/src/TelnetCommon.h"

using namespace TA_Base_Bus;

SimpleByteData::SimpleByteData(Byte b)
: m_value(b)
{
}

SimpleByteData::SimpleByteData(signed char c)
: m_value(c)
{
}

SimpleByteData::SimpleByteData(int i)
: m_value(i)
{
}

TelnetCommand::TelnetCommand(Byte b)
: SimpleByteData(b)
{
}

TelnetCommand::TelnetCommand(signed char c)
: SimpleByteData(c)
{
}

TelnetCommand::TelnetCommand(int i)
: SimpleByteData(i)
{
}


TelnetOption::TelnetOption(Byte b)
: SimpleByteData(b)
{
}

TelnetOption::TelnetOption(signed char c)
: SimpleByteData(c)
{
}

TelnetOption::TelnetOption(int i)
: SimpleByteData(i)
{
}


TelnetOptionStatus::TelnetOptionStatus(Byte b)
: SimpleByteData(b)
, m_pending(false)
{
}

TelnetOptionStatus::TelnetOptionStatus(signed char c)
: SimpleByteData(c)
, m_pending(false)
{
}

TelnetOptionStatus::TelnetOptionStatus(int i)
: SimpleByteData(i)
, m_pending(false)
{
}

TelnetOptionStatus::TelnetOptionStatus(const TelnetCommand & cmd)
: SimpleByteData(Invalid)
, m_pending(false)
{
    if (cmd.value()==TelnetCommand::WILL)
    {
        setValue(Will);
    }
    else if (cmd.value()==TelnetCommand::WONT)
    {
        setValue(Wont);
    }
    else if (cmd.value()==TelnetCommand::DO)
    {
        setValue(Do);
    }
    else if (cmd.value()==TelnetCommand::DONT)
    {
        setValue(Dont);
    }
}

TelnetOptionStatus::TelnetOptionStatus()
: SimpleByteData(Invalid)
, m_pending(false)
{
}

