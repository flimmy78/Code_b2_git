/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/configuration/config_plugins/ecs_station_colour/src/ECSStationColourComponent.h $
  * @author:  Andy Siow
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  * 
  * This is the component the main Configuration Editor framework communicates with.
  * It implements the IConfigurableComponent interface. It will handle all toolbar and menu
  * requests and handle them appropriately.
  */

#if !defined(ECSStationColourComponent_A4EEC36D_18C5_4d02_927B_EC8EFFC7172B__INCLUDED_)
#define ECSStationColourComponent_A4EEC36D_18C5_4d02_927B_EC8EFFC7172B__INCLUDED_

#include <string>
#include <map>

#include "app/configuration/config_plugins/config_plugin_helper/src/AbstractComponent.h"
#include "app/configuration/config_plugins/config_plugin_helper/src/MessageSender.h"

#include "bus/security/access_control/actions/src/AccessControlledActions.h"

namespace TA_IRS_App
{

    class ECSStationColourComponent : public TA_Base_App::AbstractComponent
    {

    public:
        /** 
         * Constructor
         *
         * @param const string& - This is the name of the component displaying in the selection bar so we
         *                        can use the same name in the DLL for sending audit messages etc.
         */
        ECSStationColourComponent(const std::string& componentName);


        /**
         * Destructor
         */
	    virtual ~ECSStationColourComponent();


    public:
	    
	    /**
         * getIcon
         *
         * This returns the icon to be displayed in the selection bar.
         *
         * @return HICON - A handle to an icon that has been created
         */
	    virtual HICON getIcon();


	    /**
         * getComponentView
         *
         * This returns runtime class for the view to be shown in the bottom-right pane
         * of the application.
         *
         * @return CRuntimeClass* - This will be used to create the view in the correct pane.
         */
	    virtual CRuntimeClass* getComponentView();


        /**
         * getRightsActionForAddingThisComponent
         *
         * This should return the rights action the user must have to be able to view and use this
         * component. This action id will be passed straight to the rights library.
         *
         * @return unsigned long - The action id to use when checking whether to add this component
         *                         to the Configuration Editor.
         */
        virtual unsigned long getRightsActionForAddingThisComponent()
        {
            return TA_Base_Bus::aca_CE_CONFIGURE_ALARM_SEVERITIES;
        }


    protected:

        /**
         * getDLLName
         *
         * This returns the name of the DLL.
         */
        virtual std::string getDLLName() const;


        /**
         * getMenuItems
         *
         * This returns an empty vector, as this component has no menu items.
         *
         * @return std::vector<TA_Base_App::MenuItem> - All menu items required
         */
        std::vector<TA_Base_App::MenuItem> getMenuItems();
        
            
	    /**
         * getToolBarItems
         *
         * This returns an empty vector, as this component has no toolbar
         * items.
         *
         * @return std::vector<TA_Base_App::ToolBarItem> - All toolbar items required
         */
        std::vector<TA_Base_App::ToolBarItem> getToolBarItems();


    private:
        /**
         * Copy Constructor
         *
         * Hidden as a private method so it is not used.
         */
        ECSStationColourComponent( const ECSStationColourComponent&);


        /**
         * ECSStationColour =
         *
         * Hidden as a private method so it is not used.
         */
        ECSStationColourComponent& operator=(const ECSStationColourComponent&);



    public:
        // This is the name of the DLL and is used to load resources correctly.
        static const CString DLL_NAME;

    private:


        // The icon for this component
        HICON m_icon;
    };
}

#endif // !defined(ECSStationColourComponent_A4EEC36D_18C5_4d02_927B_EC8EFFC7172B__INCLUDED_)
