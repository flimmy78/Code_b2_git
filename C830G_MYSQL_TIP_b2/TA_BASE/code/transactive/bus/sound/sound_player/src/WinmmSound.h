/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/TA_BASE/transactive/bus/sound/sound_player/src/WinmmSound.h $
  * @author:  Daniel Hoey
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  * 
  * Plays a sound using the Windows MultiMedia library.
  */

#ifndef WINMMSOUND_H
#define WINMMSOUND_H

#include <string>
#include "ISound.h"


namespace TA_Base_Bus
{
		class WinmmSound : public ISound
		{
		public:
		  /**
		    * Constructor
		    * 
		    * Constructs a WinmmSound object with a specified wav file.
		    *
		    * @param wavFile - the file containing the sound
		    *
		    */
		    WinmmSound(const std::string& wavFile);

		  /**
		    * Destructor
		    * 
		    */
		    virtual ~WinmmSound();

         /**
            * play
            * 
            * Plays the sound
            *
            * @exception SoundPlayerException - thrown when the sound cannot be played
            */
            virtual void play();

          /**
            * stop
            * 
            * Stops the sound from playing
            *
            */
            virtual void stop();

          /**
            * setFile
            *
            * Sets the filename for this sound.
            *
            * @param filename  The filename containing the sound to be played.
            */
            virtual void setFile(std::string filename);

		private:
            std::string m_wavFile;
		};		
}
#endif // WINMMSOUND_H
