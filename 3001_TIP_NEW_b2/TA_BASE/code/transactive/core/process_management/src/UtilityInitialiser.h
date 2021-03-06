/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution in any form.
  * 
  * Source:    $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/process_management/src/UtilityInitialiser.h $
  * @author:   Ross Tucker
  * @version:  $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last mofified by:  $Author: haijun.li $
  *
  * The Utility Initialiser is used to set up the utilities used by
  * managed process.
  */
#if !defined(UTILITYINITIALISER)
#define UTILITYINITIALISER

#include <string>

namespace TA_Base_Core
{
    class UtilityInitialiser
    {
    public:

        /**
          * Constructor
          */
        UtilityInitialiser(){}

        /**
          * Destructor
          */
        ~UtilityInitialiser(){}

        /**
          * initialiseUtilities
          *
          * This method parses an agent style command line and
          * initialises the following utilities :
          * RunParams, CorbaUtil, DebugUtil, DebugSETranslator (for the calling thread)
          *
          * @param The number of command line arguments passed
          * @param The command line arguments
          *
          * @return  True if all utilities have been initialised and the process
          *          should continue. False if the program should exit (for
          *          example, if a --version command line argument is present). 
          *
          * @exception InvalidCommandLineException thrown if the command line 
          *            arguments are not of the form: foo --parameter-name=BAR
          * @exception UtilitiesException raised if CorbaUtil or DebugUtil fail
          *            to initialise
          */
        static bool initialiseUtilities( int argc, char* argv[] );

        /**
          * initialiseUtilities
          *
          * This method parses an GUI style command line and
          * initialises the following utilities :
          * RunParams, CorbaUtil, DebugUtil, DebugSETranslator (for the calling thread)
          *
          * @param The command line arguments
          *
          * @return  True if all utilities have been initialised and the process
          *          should continue. False if the program should exit (for
          *          example, if a --version command line argument is present). 
          *
          * @exception InvalidCommandLineException thrown if the command line 
          *            arguments are not of the form: foo --parameter-name=BAR
          * @exception UtilitiesException raised if CorbaUtil or DebugUtil fail
          *            to initialise
          */
        static bool initialiseUtilities( const std::string& commandLine );

    private:

        /**
          * initialiseCorba
          *
          * This method initialises and starts the ORB
          *
          * @exception UtilitiesException raised if we fail to initialise
          */
        static void initialiseCorba();

        // Disable the copy constructor and assignment operator
        UtilityInitialiser( const UtilityInitialiser& theUtilityInitialiser);
        UtilityInitialiser& operator=(const UtilityInitialiser &);
    };
}

#endif // !defined(UTILITYINITIALISER)
