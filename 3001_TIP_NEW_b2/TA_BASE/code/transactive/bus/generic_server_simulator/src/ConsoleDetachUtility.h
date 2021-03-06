#ifndef ConsoleDetachUtility_H
#define ConsoleDetachUtility_H
/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/generic_server_simulator/src/ConsoleDetachUtility.h $
  * @author:  Robert van Hugten
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * Declaration file for ConsoleDetachUtility class
  */
#include <string>

namespace TA_Base_Bus
{
    /**
      * Class with a method to detach from the terminal/console
      */
    class ConsoleDetachUtility
    {
    public:
        /**
          * 
          */
        static int detach(const std::string & host, const std::string & port);

        /** Accessor used to determine is the current simulator has detached
          * from the console or terminal
          * 
          * @return true if detached, false otherwise
          */
        static bool isDetached();

    private:
        /**
          * 
          */
        static int detach_win(const std::string & host, const std::string & port);

        /**
          * 
          */
        static int detach_unix(const std::string & host, const std::string & port);

        /** Hidden constructor, as this class is not intended to be constructed
          * 
          */
        ConsoleDetachUtility();

        /** Hidden destructor, as this class is not intended to be constructed
          * 
          */
        ~ConsoleDetachUtility();

    private:
        ///
        ///
        static bool m_isDetached;
    }; // class ConsoleDetachUtility

} // namespace TA_Base_Bus

#endif // #ifndef ConsoleDetachUtility_H
