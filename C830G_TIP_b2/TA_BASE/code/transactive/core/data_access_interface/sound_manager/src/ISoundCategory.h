/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/core/data_access_interface/sound_manager/src/ISoundCategory.h $
  * @author:  Justin Ebedes
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  * This interface contains methods that provide read-only 
  * access to an entry in the so_sound_category table.
  *
  */

#ifndef ISOUNDCATEGORY_H
#define ISOUNDCATEGORY_H

#include <string>

namespace TA_Base_Core
{
    class ISoundCategory
    {

    public:

        /** 
          * getCategoryKey
          *
          * Returns the pkey of the category.
          *
          * @return The sound category's key.
          *
          */
        virtual unsigned long getCategoryKey() = 0;


        /** 
          * getName
          *
          * Returns the name of the category.
          *
          * @return The category's name.
          *
          */
        virtual std::string getName() = 0;


        /** 
          * getPosition
          *
          * Returns this category's position in the sequence of sounds. So, this
		  * specifies when the sound category is played.
          *
          * @return The sound category's position.
          *
          */
        virtual unsigned long getPosition() = 0;

    };
    
} // namespace TA_Base_Core

#endif // ISOUNDCATEGORY_H
