/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/simulator/pa/PASimulatorLibrary/cmd/ShowTableCommand.cpp $
  * @author:  Robert van Hugten
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  * 
  * Definition/Implementation file for PASimCommand classes
  */
#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4284)
#endif // #ifdef WIN32

#include "app/simulator/pa/PASimulatorLibrary/cmd/ShowTableCommand.h"
#include "app/simulator/pa/PASimulatorLibrary/src/PASimTableAddressRegister.h"
#include "app/simulator/pa/PASimulatorLibrary/src/PASimUserProtocol.h"

// #include <stdlib.h>
#include <iostream>

using namespace TA_IRS_App::PA_Sim;


ShowTableCommand::ShowTableCommand(CommandOwner * owner)
: LeafCommand(owner, "table")
{
}

bool ShowTableCommand::makeQuery(TokenList & args, const std::string & argstr, UserQuery * query, LocationType location, std::ostream & err)
{
    //
    // basic argument checking
    if ((args.size() < 1) || (args.size() > 2))
    {
        err << "ERROR: insufficient parameters. Expected 1 or 2, got "
            << args.size() << ": " << argstr << std::endl;
        return false;
    }

    //
    // determine the table
    std::string tablename = args.front();
    args.pop_front();
    TableIdentifier tableId = PASimUtility::string2TableIdentifier(tablename);
    if (tableId==INVALID_IDENTIFIER)
    {
        err << "ERROR: invalid table name specified: " << tablename << std::endl;
        return false;
    }
    
    //
    // table address
    // At the stations, the PA tables are shared, and have location STATION
    // rather than MSS|SS1|SS2.
    if ( (tableId >= PAIdentifierLo) && (tableId <= PAIdentifierHi) )
    {
        if ( (location==MSS) || (location==SS1) || (location==SS2) )
        {
            location = STATION;
        }
    }

    //
    // from which we figure the table address
    unsigned short tAddr = TableAddressRegister::getInstance().getAddress(tableId, location);
    if (tAddr == TableAddressRegister::INVALID_ADDRESS)
    {
        err << "ERROR: could not determine table address for table " << tablename << ", id=" << tableId << std::endl;
        return false;
    }
    query->setTableAddress(tAddr);

    //
    // the [optional] records
    if ( ! args.empty() )
    {
        std::string recordstr = args.front();
        args.pop_front();
        int records = query->setRecords(recordstr, ULONG_MAX);
        if (records < 1)
        {
            err << "ERROR: invalid record range specified: " << recordstr << std::endl;
            return false;
        }
    }
    
    if ( (tableId >= PAIdentifierLo) && (tableId <= PAIdentifierHi) && (tableId != PAWatchdog) )
    {
        if ( query->getRecords().size() != 1 )
        {
            // an PA table was specified, but no records.  This is not appropriate,
            // as PA tables are too large to print more than one record at a time
            err << "WARNING: PA tables require 1 record to be specified: " ;

            if ( query->getRecords().empty() )
            {
                err << "will use record number 1" << std::endl;
                query->setRecord(1);
            }
            else // too many records
            {
                unsigned long r1 = *(query->getRecords().begin());
                err << "will use the first record specified (" << r1 << ")" << std::endl;
            }
        }
    }
    
    return true;
}


void ShowTableCommand::usage(const std::string & name, std::ostream & os) const
{
    os << "table <table name> [record range]" << std::endl;
}

