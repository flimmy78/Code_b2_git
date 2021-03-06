/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/4669_T01271350/4669/transactive/app/pa/PAManager/src/PrioritySchemeUpdateSubscriber.h $
  * @author Jade Lee
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by: $Author: builder $
  * 
  * PrioritySchemeUpdateSubscriber subscriber to listen out for changes to
  * the PriorityScheme data set (used to determine estimated priorities)
  *
  */

#if !defined(PrioritySchemeUpdateSubscriber_3F7C474E_D4B5_4966_A962_1414544E17A6__INCLUDED_)
#define PrioritySchemeUpdateSubscriber_3F7C474E_D4B5_4966_A962_1414544E17A6__INCLUDED_

#include "bus/pa/messagesubscriber/src/GenericMessageSubscriber.h"
#include "bus/pa_4669/pa_agent/IDL/src/IPAAgentCorbaDef.h"


class PrioritySchemeUpdateSubscriber 
: 
public TA_IRS_Bus::GenericMessageSubscriber<TA_Base_Bus::IPAAgentCorbaDef::PrioritySchemeUpdateData>
{
public:

    typedef TA_Base_Bus::IPAAgentCorbaDef::PrioritySchemeUpdateData PrioritySchemeUpdateData;

    /**
     * PrioritySchemeUpdateSubscriber(constructor)
     */
    PrioritySchemeUpdateSubscriber();

    /**
     * getMessageType (interface implementation)
     *
     * @see GenericMessageSubscriber::getMessageType for more details
     *
     */
    virtual const TA_Base_Core::MessageType& getMessageType() const;

protected:

    /**
     * getNotificationData (interface implementation)
     *
     * @see GenericMessageSubscriber::getNotificationData
     *
     */
    virtual TA_Base_Bus::IPAAgentCorbaDef::PrioritySchemeUpdateData getNotificationData(
        const TA_Base_Bus::IPAAgentCorbaDef::PrioritySchemeUpdateData& packetData) { return packetData; }    

    /**
     * onSubscriptionSuccessful (interface implementation)
     *
     * @see GenericMessageSubscriber::onSubscriptionSuccessful for more details
     *
     */
    virtual void onSubscriptionSuccessful();

    /**
     * onPreProcessMessage (interface implementation)
     *
     * @see GenericMessageSubscriber::onPreProcessMessage for more details
     *
     */
    virtual void onPreProcessMessage(const PrioritySchemeUpdateData& updateData);
    
    /**
     * onPostProcessMessage (interface implementation)
     *
     * @see GenericMessageSubscriber::onPostProcessMessage for more details
     *
     */
    virtual void onPostProcessMessage(const PrioritySchemeUpdateData& updateData);
};


#endif // !defined(PrioritySchemeUpdateSubscriber_3F7C474E_D4B5_4966_A962_1414544E17A6__INCLUDED_)
