#ifndef IDUTYUPDATEOBSERVER_H_INCLUDED
#define IDUTYUPDATEOBSERVER_H_INCLUDED

/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/security/security_utilities/src/IDutyUpdateObserver.h $
  * @author:  Gregg Kirkpatrick
  * @version: $Revision: #4 $
  *
  * Last modification: $DateTime: 2012/06/11 14:34:19 $
  * Last modified by:  $Author: liwei.gong $
  *
  * TODO: Write this bit
  */

namespace TA_Base_Bus
{
	class IDutyUpdateObserver : public DutyUpdateSubject::ObserverType
	{
	public:
		IDutyUpdateObserver( DutyUpdateSubject& dutyUpdate );

        /** 
          * update
          *
          * Takes the update from the DutyUpdateSubject. This should
		  * not under normal circumstanced be overridden. If it is then
		  * the various methods will not get called
		  * when an update occurs unless the overrider calls back to this
		  * method.
          *
          * @param dutyUpdate - a reference to the DutyUpdateSubject object.
          */
		virtual void update( DutyUpdateSubject& dutyUpdate );

		/** 
		  * dutyChanged
		  *
		  * Notifies the observer of a duty change
		  *
		  * @param session - the session ID for which duty has changed
		  *
		  */
		virtual void dutyChanged( const std::string& session );
	
	//private:
	//	IDutyUpdateObserver(const IDutyUpdateObserver& dutyUpdateObserver);
	};
}
#endif // IDUTYUPDATEOBSERVER_H_INCLUDED
