/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/bus/telephone/telephone_direct_lines_library/src/TelephoneSpeedDialButtonDetails.h $
  * @author:  Raymond Pau
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  * Simply a placeholder structure for Telephone Speed Dial Button Details
  */

#if !defined(TelephoneSpeedDialButtonDetails_FC4719D5_D0F7_4b4f_931B_3C89D100227D__INCLUDED_)
#define TelephoneSpeedDialButtonDetails_FC4719D5_D0F7_4b4f_931B_3C89D100227D__INCLUDED_

#include <string>

struct TelephoneSpeedDialButtonDetails
{

public:
      TelephoneSpeedDialButtonDetails();
      TelephoneSpeedDialButtonDetails(const TelephoneSpeedDialButtonDetails &copy);
      TelephoneSpeedDialButtonDetails& operator=(const TelephoneSpeedDialButtonDetails &copy);

public:
    /**
     * Name of the Speed Dial set the button belongs to.
     */
    std::string SetName;

    /**
     * The button number in the set between 1 and 36.
     */
    int buttonPosition;

    /**
     * Telephone Number associated with the Speed Dial button
     */
    std::string telephoneNumber;

    /**
     * Label associated with the Speed Dial button
     */
    std::string label;
};
#endif // !defined(TelephoneSpeedDialButtonDetails_FC4719D5_D0F7_4b4f_931B_3C89D100227D__INCLUDED_)
