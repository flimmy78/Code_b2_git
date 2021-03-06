/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/cctv/video_display_manager/src/Sequence.h $
  * @author:  Adam Radics
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  *
  * This is used to locally store state and association information
  * so it can easily be retrieved for displaying in the GUI.
  */


#if !defined(Sequence_H)
#define Sequence_H


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VideoInput.h"

#include <list>

namespace TA_IRS_App
{
    class Camera;

    class Sequence : public VideoInput
    {
    public:

        Sequence( unsigned long entityKey,
                  const std::string& name,
                  const std::string& description,
                  const std::string& group );


        virtual ~Sequence() {}

        /**
          * getDwellTime
          *
          * Gets the dwell time (1-99). 0 for empty sequences.
          *
          * @return the dwell time
          */
        virtual unsigned short getDwellTime();

        /**
          * setDwellTime
          *
          * Sets the dwell time (1-99). 0 for empty sequences.
          *
          * @param dwellTime the new dwell time
          */
        virtual void setDwellTime(unsigned short dwellTime);


        /**
          * getReadOnly
          *
          * Get whether the sequence is read only
          *
          * @return whether its read only
          */
        virtual bool getReadOnly();

        /**
          * setReadOnly
          *
          * Sets whether the sequence is read only
          *
          * @param readOnly true if the sequence cannot be written
          */
        virtual void setReadOnly(bool readOnly);

        // TD16691
        /**
          * getSequenceDescription
          *
          * Get the sequence description
          *
          * @return sequence description
          */
        virtual std::string getSequenceDescription();

        /**
          * setSequenceDescription
          *
          * Sets the sequence description
          *
          * @param sequence description
          */
        virtual void setSequenceDescription(std::string sequenceDescription);
        // TD16691

        /**
          * getCameras
          *
          * Gets the cameras associated with this sequence.
          *
          * @return the list of cameras. Order is important.
          */
        virtual std::list<Camera*> getCameras();

        /**
          * setCameras
          *
          * Sets the cameras associated with this sequence.
          *
          * @param cameras  the list of cameras. Order is important.
          */
        virtual void setCameras(std::list<Camera*> cameras);

        /**
          * getDetails
          *
          * Gets a more detailed description of the item.
          * This is formatted for printing in a text box.
          *
          * @return The detailed description.
          */
        virtual std::string getDetails();


    protected:

        unsigned short m_dwellTime;
        std::list<Camera*> m_cameras;
        bool m_readOnly;
        // TD16691
        std::string m_sequenceDescription;
        // TD16691

    private:

        // These arent needed
        Sequence();
        Sequence( const Sequence& );
        Sequence& operator=( const Sequence& );

    };
}

#endif // !defined(Sequence_H)

