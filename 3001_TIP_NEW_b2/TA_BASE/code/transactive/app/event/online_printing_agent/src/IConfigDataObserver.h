#if !defined(ICNFIGDATAOBSERVER_H_INCLUDED)
#define ICNFIGDATAOBSERVER_H_INCLUDED

/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/event/online_printing_agent/src/IConfigDataObserver.h $
  * @author:  Bart Golab
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * Implemented by classes wanting to receive config data change notifications.
  *
  */

namespace TA_Base_App
{
    class IConfigDataObserver
    {
    public:
        /**
         * parametersChanged
         *
         * Notifies a change in the specified agent entity parameters.
         */
        virtual void parametersChanged(const EntityParameterList& parameters) = 0;

        virtual ~IConfigDataObserver() {};
    };
}

#endif // !defined(ICNFIGDATAOBSERVER_H_INCLUDED)
