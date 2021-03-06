 /**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/3001_TIP_NEW/TA_BASE/transactive/core/data_access_interface/pa_4669/src/PaTrainDvaMessage.cpp $
  * @author Jade Lee
  * @version $Revision: #4 $
  * Last modification: $DateTime: 2013/09/26 14:59:27 $
  * Last modified by: $Author: huangjian $
  * 
  * PaTrainDvaMessage is an implementation of IPaTrainDvaMessage. It holds the data specific to an PaTrainDvaMessage entry
  * in the database, and allows read-only access to that data.
  *
  */

#ifdef __WIN32__
#pragma warning(disable:4786 4290)
#endif

#include "core/data_access_interface/pa_4669/src/PaTrainDvaMessage.h"

#include "core/utilities/src/TAAssert.h"

namespace TA_Base_Core
{

    PaTrainDvaMessage::PaTrainDvaMessage(const unsigned long key)
     : m_paTrainDvaMessageHelper ( new PaTrainDvaMessageHelper(key))
    {}


    PaTrainDvaMessage::PaTrainDvaMessage(unsigned long row, TA_Base_Core::IData& data)
     : m_paTrainDvaMessageHelper(new PaTrainDvaMessageHelper(row, data))
    {
    }


    PaTrainDvaMessage::~PaTrainDvaMessage() 
	{
        delete m_paTrainDvaMessageHelper;
        m_paTrainDvaMessageHelper=NULL;
    }


    unsigned long PaTrainDvaMessage::getKey()
    {
        TA_ASSERT(m_paTrainDvaMessageHelper != NULL,"The PaTrainDvaMessageHelper pointer is null.");
        return m_paTrainDvaMessageHelper->getKey();
    }


    std::string PaTrainDvaMessage::getLabel()
    {
        TA_ASSERT(m_paTrainDvaMessageHelper != NULL,"The PaTrainDvaMessageHelper pointer is null.");
        return m_paTrainDvaMessageHelper->getLabel();
    }    
    

    void PaTrainDvaMessage::invalidate()
    {
        TA_ASSERT(m_paTrainDvaMessageHelper != NULL,"The PaTrainDvaMessageHelper pointer is null.");
        m_paTrainDvaMessageHelper->invalidate();
    }


    std::string PaTrainDvaMessage::getName()
    {
        TA_ASSERT(m_paTrainDvaMessageHelper != NULL,"The m_paTrainDvaMessageHelper pointer is null.");

        std::ostringstream name;
		name << "PA Train DVA Message " << m_paTrainDvaMessageHelper->getKey();

        return name.str();
    }

} // closes TA_Base_Core
