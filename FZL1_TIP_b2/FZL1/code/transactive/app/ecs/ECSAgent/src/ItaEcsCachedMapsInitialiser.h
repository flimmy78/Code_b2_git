/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/GZL6_TIP/3002/transactive/app/ecs/ECSAgent/src/ItaEcsCachedMapsInitialiser.h $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2012/06/12 13:35:44 $
  * Last modified by:  $Author: builder $
  *
  */
// ItaEcsCachedMapsInitialiser.h: interface for the ItaEcsCachedMapsInitialiser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ItaEcsCachedMapsInitialiser_H__AC46F392_4FE1_4341_B976_D4DBE3CB8EAD__INCLUDED_)
#define AFX_ItaEcsCachedMapsInitialiser_H__AC46F392_4FE1_4341_B976_D4DBE3CB8EAD__INCLUDED_

#include "app/ecs/ECSAgent/src/EcsGlobals.h"

class ItaEcsCachedMapsInitialiser  
{

public:

    
    // Reads all zoneId records
    virtual void refreshZoneRecords()=0;

    // Only refreshes for given zoneIds
    virtual void refreshZoneRecords(const std::vector<unsigned long>& zoneIds)=0;

    // specify locationKey to refresh for a given location only
    virtual void refreshStationModeRecords(unsigned long locationKey=-1)=0; 

    virtual void refreshMasterModeRecords()=0;
    
    virtual void refreshLocationNames()=0;
    
    virtual void refreshMasterModeLockProxies(const std::string& sqlToken)=0;
    
    virtual void refreshSelectedMasterModeProxies(const std::string& sqlToken)=0;
    
    virtual void refreshSelectedOverridingStationModeProxies(const std::string& sqlToken)=0;
    
    virtual void refreshLastAppliedMasterModeProxies(const std::string& sqlToken)=0;
    
    virtual void refreshLastAppliedStationModeProxies(const std::string& sqlToken)=0;
    
    virtual void refreshLocalModeProxies(const std::string& sqlToken)=0;


    // Pre: refreshZoneRecords() called
    virtual void refreshMyZoneCongestionDataPoints(const DataPoints& dataPoints)=0;

    // Pre: refreshZoneRecords() called
    virtual void refreshMyZoneEmergencyDataPoints(const DataPoints& dataPoints)=0;

    // No longer required
    // Pre: refreshZoneRecords() called
    //virtual void refreshMyZoneCongestionAppliedDataPoints(const DataPoints& dataPoints)=0; 
    
    // Pre: refreshZoneRecords() called
    virtual void refreshMyZoneEmergencyAppliedDataPoints(const DataPoints& dataPoints)=0;

    // Pre: refreshZoneRecords() called
    virtual void refreshMyZoneEvacuationSelectedDataPoints(const DataPoints& dataPoints)=0;

    // Pre: refreshZoneRecords() called
    virtual void refreshMyZoneAirflowSelectedDataPoints(const DataPoints& dataPoints)=0;

    // Pre: refreshZoneRecords() called
    virtual void refreshMyZoneEvacuationAppliedDataPoints(const DataPoints& dataPoints)=0;

    // Pre: refreshZoneRecords() called
    virtual void refreshMyZoneAirflowAppliedDataPoints(const DataPoints& dataPoints)=0;

    virtual void refreshStationEcsAgentCorbaNames()=0;
    
    virtual void refreshZoneIdInScope(const std::vector<TA_Base_Bus::DataPoint*>& dataPoints)=0;
    /**
     * validateX methods
	 *
	 * Verification methods to validate loaded data after all required maps have
     * refreshed.
     *
     * @throws InvalidECSConfigurationException if data is invalid
     *
     */

    virtual void validateAllInitialisedMaps()=0; 

};


#endif // !defined(AFX_ItaEcsCachedMapsInitialiser_H__AC46F392_4FE1_4341_B976_D4DBE3CB8EAD__INCLUDED_)


