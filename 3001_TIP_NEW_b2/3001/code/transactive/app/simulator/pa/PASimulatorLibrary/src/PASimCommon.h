#ifndef PA_SIM_COMMON_H
#define PA_SIM_COMMON_H
/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/simulator/pa/PASimulatorLibrary/src/PASimCommon.h $
  * @author:  Robert van Hugten
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * Declaration file for typedefs, structs and constants common to PA
  * Simulation classes.
  */
#include "core/types/src/ta_types.h"
#include <string>
#include <vector>
#include <set>

#ifdef WIN32
#pragma warning (disable : 4786)
#pragma warning (disable : 4284)
#endif // #ifdef WIN32


namespace TA_IRS_App
{
namespace PA_Sim
{
    /**
      * Byte
      *
      * The same as unsigned char.  Would have liked to go via the ta_types
      * ta_uint8 to ensure cross-platformability, however on Windows it maps
	  * to "unsigned __int8" which apparently isn't the same as unsigned char,
      * or at least not the same enough to stop vc++ disallowing conversion
      * between types templated on it.
      */
    typedef unsigned char Byte;

    /**
      * ByteArray
      *
      * Essentially the same as unsigned char *, but via the ta_types
      * unsigned 8-bit type.
      */
    typedef Byte * ByteArray;

    /**
      * ByteString
      *
      * Essentially the same as std::string, but templated on the ta_types
      * unsigned 8-bit type.
      */
    typedef std::basic_string<Byte, std::char_traits<Byte>, std::allocator<Byte> > ByteString;

    /**
      * ByteVector
      *
      * Template for an STL vector templated on the unsigned 8-bit type.
      */
    typedef std::vector<Byte> ByteVector;


    /**
      * Word
      *
      * The same as unsigned short int.
      */
    typedef unsigned short int Word;

	/**
      * Word
      *
      * The same as unsigned short int.
      */
    typedef unsigned int DWord;


    /**
      * WordArray
      *
      * Essentially the same as unsigned short int *
      */
    typedef Word * WordArray;

    /**
      * WordString
      *
      * Essentially the same as std::string, but templated on the ta_types
      * unsigned 16-bit type.
      */
    typedef std::basic_string<Word, std::char_traits<Word>, std::allocator<Word> > WordString;

    /**
      * WordVector
      *
      * Typedef for an STL vector templated on the unsigned 16-bit type.
      */
    typedef std::vector<Word> WordVector;


    /**
      * RecordRange
      *
      * Represents a range of records
      */
    typedef std::set<unsigned long> RecordRange;


    /**
      * Constants representing Modbus frame Function Code identifiers
      */

    /// Function code for Read querys or replies
    const unsigned char PASim_FC_Read                 = 0x04;

    /// Function code for Write querys or replies
    const unsigned char PASim_FC_Write                = 0x10;

    /// Function code for Read replies with exception codes
    const unsigned char PASim_FC_ReadException        = 0x84;

    /// Function code for Write replies with exception codes
    const unsigned char PASim_FC_WriteException       = 0x90;

    /**
      * Constants representing Modbus frame Exception Code identifiers
      */
    /// Exception code for when there was no error or exception
    const unsigned char PASim_EC_NoException          = 0x00;

    /// Exception code for "Function not defined in the slave device"
    const unsigned char PASim_EC_FunctionNotDefined   = 0x01;

    /// Exception code for "MODBUS table address not recognised by the slave"
    const unsigned char PASim_EC_AddressNotRecognised = 0x02;

    /// Exception code for "Illegal value for the given address"
    const unsigned char PASim_EC_IllegalValue         = 0x03;

    /** An enumeration representing the 3 PA locations. Some of the
      * identifiers share the same value, being synonyms for that location.
      *
      * Can't just
      *
      * #include "core/data_access_interface/src/ILocation.h"
      *
      * because it only contains three locations, whereas we need to
      * differentiate between the three STATION locations
      */
    typedef enum LocationType
    {
        OCC     = 1,
        DPT     = 2,
        DEPOT   = 2,    // synonymous with DPT
        MSS     = 3,
        SS1     = 4,
        SS2     = 5,
        STATION = 6,

        NO_LOCATION=-1  // an erroneous value
    };

    ///
    /// enumeration of values for the format for outputing tables.
    typedef enum TableOutputFormat
    {
        f_hex          = 1,
        f_tabular      = 2,
        f_default      = f_tabular
    };

    /// Enumeration to represent the identifiers of PA and ISCS tables
    typedef enum TableIdentifier
    {
        PAPlatform             = 1,
        PATrain                = 2,
        PAWash                 = 3,
        PAWatchdog             = 4,
        PAWILD                 = 5,
        PADSS                  = 6,

        IscsAtcData             = 1001,
        IscsElectricalSubsection= 1002,
        IscsPlatform            = 1003,
        IscsTrain               = 1004,
        IscsWash                = 1005,
        IscsWatchdog            = 1006,

        PAIdentifierLo         = PAPlatform,
        PAIdentifierHi         = PADSS,

        IscsIdentifierLo        = IscsAtcData,
        IscsIdentifierHi        = IscsWatchdog,

        INVALID_IDENTIFIER      = 0,
        DEFAULT_IDENTIFIER      = 999

    } TableIdentifier;


    /** Sloppy union for the purposes of streaming Words to and from a
      * ByteVector.
      */
    union TwoByteUnion
    {
        Byte            the_bytes[2];
        Word            the_word[1];
    };

    /** Sloppy union for the purposes of streaming long Words to and from a
      * ByteVector.
      */
    union FourByteUnion
    {
        Byte            the_bytes[4];
        Word            the_words[2];
        unsigned long   the_long[1];
    };


    const int NumberOfDoorsPerCar = 8;


	namespace gss
	{
        extern std::ostream & cout;
	}
} // namespace PA_Sim
} // namespace TA_IRS_App
#endif // #ifndef PA_SIM_COMMON_H
