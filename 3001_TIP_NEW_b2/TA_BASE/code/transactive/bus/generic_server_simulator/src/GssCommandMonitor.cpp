/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/generic_server_simulator/src/GssCommandMonitor.cpp $
  * @author:  Robert van Hugten
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * \class GssCommandMonitor
  * Implementation file for the GssCommandMonitor class, derived from the
  * CommandMonitor class. CommandMonitor provides functionality to constantly
  * listen for user input from the command line, and to process that input
  * and execute the appropriate commands.
  *
  * GssCommandMonitor extends CommandMonitor by overriding createSimulationModule
  * to return an instance of the class specified by the type, using the 
  * GssSimulationModuleFactory to create the correct class.
  */
#include "bus/generic_server_simulator/src/GssCommandMonitor.h"
#include "bus/generic_server_simulator/src/GssSimulationModuleFactory.h"
#include "bus/generic_server_simulator/src/GenericSimulator.h"


using namespace TA_Base_Bus;

/* ----------------------------------------------------------------------------
 * Construction/Destruction
 * --------------------------------------------------------------------------*/
GssCommandMonitor::GssCommandMonitor(const std::string &desc, GenericSimulator *simulator)
: CommandMonitor(desc,simulator)
{

}

GssCommandMonitor::~GssCommandMonitor()
{
}

TA_Base_Bus::ISimulationModule * GssCommandMonitor::createSimulationModule
(   const std::string& type,
    const std::string& name,
    const std::string& parameters)
{
    return GssSimulationModuleFactory::getInstance().createSimulationModule(type, name, parameters);
}
