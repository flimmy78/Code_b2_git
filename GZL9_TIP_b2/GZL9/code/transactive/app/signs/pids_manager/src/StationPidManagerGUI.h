/**
 * The source code in this file is the property of 
 * Ripple Systems and is not for redistribution
 * in any form.
 *
 * Source:   $File: //depot/4677_TIP/4677/transactive/app/signs/pids_manager/src/StationPidManagerGUI.h $
 * @author:  
 * @version: $Revision: #2 $
 *
 * Last modification: $DateTime: 2009/12/15 19:31:45 $
 * Last modified by:  $Author: grace.koh $
 * 
 * Class to provide handlers for GenericGUI functionality. Most importantly, it is
 * responsible for instantiating an instance of the PidManagerDialog class.
 */

//#if !defined(StationPidManagerGUI_3F1AFB05_A216_40d0_899F_59EDBB6FB7CD__INCLUDED_)
//#define StationPidManagerGUI_3F1AFB05_A216_40d0_899F_59EDBB6FB7CD__INCLUDED_
#pragma once

#include "bus/generic_gui/src/AbstractDialogGUI.h"
//#include "app/signs/pids_manager/src/IStationPidUpdater.h"

namespace TA_IRS_App
{

class StationPidManagerGUI : public TA_Base_Bus::AbstractDialogGUI
{
public:
    StationPidManagerGUI();
    virtual ~StationPidManagerGUI();
	
	
    /**
    * getApplicationType
    * 
    * This returns the application type for this GUI. GenericGUI will then save
    * this in the RunParams and will use it to pass to the Control Station. In the
    * existing system the application type would need to be hard-coded into here.
    *
    * @return unsigned long representing the application type
    *
    */
    unsigned long getApplicationType();

    /**
    * checkEntity
    * 
    * This will check that the entity is valid and then store a local pointer to the
    * entity. 
    *
    * @param IEntityData* guiEntity - A pointer to the gui entity to check and store.
    *
    * @exceptions GenericGUIException with the type set to ENTITY_CONFIGURATION_INVALID
    *             This should be thrown if the application checks the entity and it is
    *             not configured correctly for the GUI to run.
    *
    */
    void checkEntity(TA_Base_Core::IEntityData* guiEntity);

    /**
    * checkCommandLine
    *
    * This checks that all the appropriate RunParams have been set from the command line.
    * If anything is invalid or missing then this will throw an exception.
    * All settings SHOULD be in the GUI entity and the only additional command line
    * parameter should be --control-entity.
    *
    * @exceptions GenericGUIException with the type set to COMMAND_LINE_INVALID
    *             It must throw this if the command line does not contain the correct
    *             information for the GUI to run.
    */
    void checkCommandLine();

    /**
    * entityChanged
    *
    * This will be called by GenericGUI when it receives a callback indicating that the
    * GUI entity has been modified. GenericGUI will have invalidated the entity database
    * object and will tell the GUI which items were modified. The GUI just has to retrieve
    * the details out of it and update accordingly.
    *
    * @param vector<string>& changes - This is a list of all attributes changed in the
    *                                  object.
    */
    void entityChanged(const std::vector<std::string>& changes);

    /**
    * serverIsDown
    *
    * This is called when the server the workstation is using goes down. The GUI should
    * indicate to the user that the server is down. It should also then limit operations
    * so that the user can only view existing data.
    */
    void serverIsDown();

    /**
    * serverIsUp
    *
    * This is called when the server the workstation is using starts functioning again.
    * The GUI should indicate to the user that the server is functioning. It should 
    * then allow the user to perform all valid operations again.
    */
    void serverIsUp();

    /**
    * loadAllUserSettings
    *
    * This will load all the application's user preferences if configured to do so.
    * This should be called by the application itself in OnInit() or equivalent. 
    *
    * @exceptions TODO:
    */
    void loadAllUserSettings();

    /**
    * saveAllUserSettings
    *
    * This will save all the application's user preferences if configured to do so.
    * This is provided in case the GUI needs to save user preferences at a predetermined
    * time. The settings are already saved when the application exits.
    *
    * @exceptions TODO:
    */
    void saveAllUserSettings();

    /**
    * changeFocus
    *
    * Implementing for IGUIApplication. The Control Station needs to alert the GUI
    * applications when they should regain the focus on the screen. This is the most
    * common focus request by the Control Station but it may also need to tell the
    * applications to minimise or maximise. This is done through this method. This takes
    * an enumeration indicating how the GUI should change it's focus. Changing the focus
    * of a window is the same for all window types so this can be implemented here.
    *
    * @param    EFocusType focus - This indicates how the window should change it's focus.
    */
    //void changeFocus(const TA_Base_Core::EFocusType focus); //TES230
	

protected:

	//TD18095, jianghp
	virtual void onInitGenericGUICompleted();
	
	virtual void createApplicationObject();
    /**
    * prepareForClose
    *
    * This method is used to prepare the GUI for closing. It should save the user settings
    * and perform any other tidying up. eg Stop any processing threads, ask the user if they
    * wish to save anything etc.
    */
    void prepareForClose();

    /**
    * createApplicationObject
    *
    * This method must set the m_application member variable. It should create a new
    * instance of the dialog/document/property sheet and assign it to m_application
    */
    

private:
    //
    // Hide the copy constructor and assignment operator as they
    // are not needed.
    //
    StationPidManagerGUI( const StationPidManagerGUI& theStationPidManagerGUI);
    StationPidManagerGUI& operator=(const StationPidManagerGUI &);
};

}