/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/generic_server_simulator/examples/echo_server/src/EchoModuleCreator.h $
  * @author:  Ripple
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  */
///////////////////////////////////////////////////////////
//  EchoModuleCreator.h
//  Implementation of the Class EchoModuleCreator
//  Created on:      17-Jun-2004 17:57:14 PM
///////////////////////////////////////////////////////////

#if !defined(EchoModuleCreator_4738D7DF_634A_4103_82E4_4D522801C21C__INCLUDED_)
#define EchoModuleCreator_4738D7DF_634A_4103_82E4_4D522801C21C__INCLUDED_

#ifdef WIN32
#pragma warning(disable : 4786)
#pragma warning(disable : 4284)
#endif // #ifdef WIN32

#include "bus/generic_server_simulator/src/GssAbstractModuleCreator.h"

namespace TA_Base_Bus
{

    class ISimulationModule;

    class EchoModuleCreator : public GssAbstractModuleCreator
    {

    public:
        virtual ~EchoModuleCreator();

        virtual ISimulationModule * createSimulationModule(const std::string & name, const std::string & parameters);

        EchoModuleCreator(const std::string & type);

    }; // class EchoModuleCreator

} // namespace TA_Base_Bus

#endif // !defined(EchoModuleCreator_4738D7DF_634A_4103_82E4_4D522801C21C__INCLUDED_)
