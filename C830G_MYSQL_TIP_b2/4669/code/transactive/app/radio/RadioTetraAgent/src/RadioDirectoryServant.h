/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/4669_T01271350/4669/transactive/app/radio/RadioTetraAgent/src/RadioDirectoryServant.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by:  $Author: builder $
  *
  */
///////////////////////////////////////////////////////////
//
//  RadioDirectoryServant.h
//  Implementation of the Class RadioDirectoryServant
//  Generated by Enterprise Architect
//  Created on:      30-Oct-2003 08:19:59
//  Original author: 
//  
///////////////////////////////////////////////////////////
//  Modification history:
//  
//
///////////////////////////////////////////////////////////


#if !defined(RadioDirectoryServant_DC5CCB91_948A_42b3_9674_9CED6E32D9F2__INCLUDED_)
#define RadioDirectoryServant_DC5CCB91_948A_42b3_9674_9CED6E32D9F2__INCLUDED_

#include "core/corba/src/ServantBase.h"
#include "core/data_access_interface/entity_access/src/RadioDirectoryEntityData.h"

#include "bus/radio/RadioAgentCorbaDef_4669/idl/src/IRadioDirectoryCorbaDef.h"
#include "bus/generic_agent/src/IEntity.h"

#include "app/radio/RadioTetraAgent/src/RadioSessionInitialisationThread.h"
#include "app/radio/RadioTetraAgent/src/IRadioDirectoryCallback.h"

namespace TA_IRS_App
{
	class Radio;
	class RadioDirectory;
	class RadioDirectorySynchronisation;

	class RadioDirectoryServant : virtual public POA_TA_Base_Bus::IRadioDirectoryCorbaDef,
								  virtual public TA_Base_Core::ServantBase, 
		                          virtual public TA_Base_Bus::IEntity,
                                  virtual public IRadioDirectoryCallback
	{

		public:

			RadioDirectoryServant(TA_IRS_App::Radio& radio,TA_Base_Core::RadioDirectoryEntityDataPtr EntityData);
			virtual ~RadioDirectoryServant();

            virtual long                                                 getLastDirectorySynchronisationTime();
            

			//****************************
			// IEntity Interface Methods *
			//****************************
			virtual bool isValid();
			virtual void start();
			virtual void stop();
			virtual void update(const class TA_Base_Core::ConfigUpdateDetails& details);
			virtual void remove();
			virtual void setToControlMode();
			virtual void setToMonitorMode();

			//********************************************
			// IRadioDirectoryCallback Interface Methods *
			//********************************************
			virtual void onSubscriberChange(TA_Base_Core::IRASubscribers * subscriber, SubscriberChangeType changeType);
			virtual void onConnectionLost();
			virtual void onConnectionEstablish();
			virtual void onSwitchConnection();

		private:



			RadioDirectory*	                 m_radioDirectory;
			RadioDirectorySynchronisation*	 m_radioDirectorySynchronisation;

			std::string   m_directoryName;
			unsigned long m_entityKey;	
            unsigned long m_locationKey;
	};
};

#endif // !defined(RadioDirectoryServant_DC5CCB91_948A_42b3_9674_9CED6E32D9F2__INCLUDED_)
