#ifndef CORBARIGHTSLIBRARY_H_INCLUDED
#define CORBARIGHTSLIBRARY_H_INCLUDED

/**
  *  The source code in this file is the property of
  *  Ripple Systems and is not for redistribution
  *  in any form.
  *
  *  Source:   $File$
  *  @author:  Gregg Kirkpatrick
  *  @version: $Revision$
  *
  *  Last modification: $DateTime$
  *  Last modified by:  $Author$
  *
  *  A CORBA based RightsLibrary. It hides the RightsAgent interface
  *  from the caller.
  *
  *  TODO: To enable caching the CorbaRightsLibrary now implicitly KNOWS how the rights agent
  *        works. This is A BAD THING and should be removed as soon as the Rights Agent is able to
  *        run on operator consoles.
  */



namespace TA_Base_Bus
{
	/**
	  * This class creates a connection to the Rights Agent 
	  * every time it is instantiated. To improve performace
	  * consider creating and maintaining one per thread.
	  *
	  */
	class CorbaRightsLibrary : public RightsLibrary
	{
	public:
		CorbaRightsLibrary(); 
		virtual ~CorbaRightsLibrary();

		virtual bool isActionPermittedOnResource(
					const std::string& sessionId, unsigned long resourceKey,
					unsigned long actionKey, std::string& reasonString,
					EDecisionModule& decisionModule );

		virtual bool isActionPermittedOnResourceAndLocSub(
					const std::string& sessionId, unsigned long resourceKey, unsigned long locationKey, unsigned long subsystemKey,
					unsigned long actionKey, std::string& reasonString,
					EDecisionModule& decisionModule );
		virtual void isActionPermittedOnResources(
			const std::string& sessionId, ResourceList& resourceKeys,ResourceList& returnResourceList,
			unsigned long actionKey, std::string& reasonString,
			EDecisionModule& decisionModule );
		virtual void areActionsPermittedOnSubsystemAndLocSub(
			const std::string& sessionId,unsigned long resourceKey,  unsigned long locationKey, unsigned long subsystemKey,
			ActionList& actionKeys,ActionList& returnActionList, std::string& reasonString,
			EDecisionModule& decisionModule );
		virtual void resetCache();

		virtual void registerObserver(IRightsChangeObserver& observer);
		virtual void unregisterObserver(IRightsChangeObserver& observer);

	protected:
		friend class RightsCache;
		void notifyObservers(std::string& sessionId, ERightsChangeType changeType, DutyChanges& changes);
			
	private:
		CorbaRightsLibrary( const CorbaRightsLibrary& );
		CorbaRightsLibrary& operator=( const CorbaRightsLibrary& );

        /**
         * isSuperProfile
         *
         * Returns true if the specified session is using the super profile.
         *
         * @param sessionId The ID of the session to check the profiles for.
         *
         * @return bool True if the specified session has the super profile associated with it.
         */
        bool isSuperProfile( const std::string& sessionId );

        /**
         * isSuperSession
         *
         * Returns true if the specified session is the super session.
         *
         * @param sessionId The ID of the session to check.
         *
         * @return bool True if the specified session is the super session.
         */
        bool isSuperSession( const std::string& sessionId );

		typedef TA_Base_Core::NamedObject<IRightsAgentCorbaDef,
				IRightsAgentCorbaDef_ptr,
				IRightsAgentCorbaDef_var> RightsAgentType;
		
		RightsAgentType* m_rightsAgent;
		SessionUpdateSubject m_sessionUpdates;
		RightsCache m_cache;
		DutyCommsSubscriber m_subscriber;
		TA_Base_Core::NonReEntrantThreadLockable m_cacheLock;
        unsigned long m_superProfileKey;
        AuthenticationLibrary m_authLibrary;

		typedef std::list<IRightsChangeObserver*>::iterator observeriterator;
		std::list<IRightsChangeObserver*> m_observers;
		TA_Base_Core::NonReEntrantThreadLockable m_observersLock;
    };
}

#endif // CORBARIGHTSLIBRARY_H_INCLUDED
