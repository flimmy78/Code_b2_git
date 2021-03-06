/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/generic_gui/ItaUserMessage/src/CtaUserMessage.h $
  * @author:  San Teo
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  *
  * The implementation of ItaUserMessage
  *
  */


#if !defined(CTA_USER_MESSAGE_H)
#define CTA_USER_MESSAGE_H

#include "bus/generic_gui/ItaUserMessage/public_interfaces/ItaUserMessage.h"
#include <map>
#include "bus/generic_gui/src/TransActiveMessage.h"
#include "core/synchronisation/src/NonReEntrantThreadLockable.h"

namespace TA_Base_Bus
{

    class CtaUserMessage : public virtual ItaUserMessage
    {
    public:

        /** 
          * Constructor
          *
          * Initialise and loads the User Message DLL.
          *
          */
		CtaUserMessage();

        /** 
          * constructMessage
          *
          * Constructs a formatted string using the loaded string resource identifier
          * and the pre-input arguments.
          *
          * @param uiMessageID Resource identifier of the string to display
          *
          * @return The formatted string.
          */
	    virtual CString constructMessage(UINT uiMessageID);


        /** 
          * showMsgBox
          *
          * Displays a message box with text and appearance loaded from the input string resource
          * identifier. Returns the result of ::MessageBox, 0 upon failure.
          *
          * @param uiMessageID Resource identifier of the string to display
          */
	    virtual void showMsgBox(UINT uiMessageID);


        /** 
          * Destructor
          *
          * Free resource library if loaded and destroy CtaUserMessage object.
          *
          */
        virtual ~CtaUserMessage();


        /** 
          * Generic parameter vector input operators
          *
          * Inserts a string into the message.
          *
          * @param arg Parameter to be inserted into the message arguments member vector.
          */
        virtual ItaUserMessage& operator << (const std::string& arg);


        /** 
          * Generic parameter vector input operators
          *
          * Inserts a string into the message.
          *
          * @param arg Parameter to be inserted into the message arguments member vector.
          */
        virtual ItaUserMessage& operator << (const CString& arg);


        /** 
          * Generic parameter vector input operators
          *
          * Inserts a boolean into the message.
          *
          * @param arg Parameter to be inserted into the message arguments member vector.
          */
        virtual ItaUserMessage& operator << (const bool arg);


        /** 
          * Generic parameter vector input operators
          *
          * Inserts an integer into the message.
          *
          * @param arg Parameter to be inserted into the message arguments member vector.
          */
        virtual ItaUserMessage& operator << (const unsigned long arg);


        /** 
          * Generic parameter vector input operators
          *
          * Inserts a short integer into the message.
          *
          * @param arg Parameter to be inserted into the message arguments member vector.
          */
        virtual ItaUserMessage& operator << (const short arg);


        /** 
          * Generic parameter vector input operators
          *
          * Inserts an integer into the message.
          *
          * @param arg Parameter to be inserted into the message arguments member vector.
          */
        virtual ItaUserMessage& operator << (const int arg);


        /** 
          * Generic parameter vector input operators
          *
          * Inserts a double into the message.
          *
          * @param arg Parameter to be inserted into the message arguments member vector.
          */
        virtual ItaUserMessage& operator << (const float arg);


        /** 
          * clear
          *
          * Empties the member vector of message arguments
          *
          */
	    virtual void clear();

    private:
        TransActiveMessage& getMessage();

        typedef std::map<unsigned int, TransActiveMessage*> ThreadMessageMap;
        ThreadMessageMap m_map;

	    // protect the map
        mutable TA_Base_Core::NonReEntrantThreadLockable m_mapLock;
    };
};
#endif