/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/3001/transactive/app/configuration/config_plugins/tis_ratis_tag/src/TisRatisTagDetailView.h $
  * @author:  James
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * This view allows the user to configure an Tis Ratis Tag's details.
  */

#if !defined(AFX_TisRatisTagDetailView_H__4046FE10_EABC_4CF5_B97A_F54C40A0D214__INCLUDED_)
#define AFX_TisRatisTagDetailView_H__4046FE10_EABC_4CF5_B97A_F54C40A0D214__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "app/configuration/config_plugins/tis_ratis_tag/src/resource.h"
#include "bus/mfc_extensions/src/text_colour_edit/TextColourEdit.h"

#include "app/configuration/config_plugins/config_plugin_helper/src/TransparentImage.h"
#include "app/configuration/config_plugins/config_plugin_helper/src/AbstractDetailView.h"
#include "app/configuration/config_plugins/config_plugin_helper/src/ChangeDialog.h"

#include "bus/mfc_extensions/src/coloured_controls/HighlightItemListCtrl.h"

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

namespace TA_IRS_Core
{
    class IConfigTiRatisTag;
}


namespace TA_IRS_App
{
    class TisRatisTagDatabaseAccessor;
    class TisRatisTagListView;


    class TisRatisTagDetailView : public TA_Base_App::AbstractDetailView
    {
    protected:
        /**
         * Constructor
         *
         * protected constructor used by dynamic creation
         */
	    TisRatisTagDetailView();


        /**
         * Destructor
         */
	    virtual ~TisRatisTagDetailView();

        
        DECLARE_DYNCREATE(TisRatisTagDetailView)


    // Form Data
    public:
	    //{{AFX_DATA(TisRatisTagDetailView)
    	enum { IDD = IDD_TIS_RATIS_TAG_RECORD_VIEW };
    	CButton	            m_applyBtn;
    	CStatic	            m_modifyDate;
    	CStatic	            m_createDate;
        TA_Base_Bus::TextColourEdit	    m_tagGroupEdt;
        TA_Base_Bus::TextColourEdit	    m_detailEdt;

    	//}}AFX_DATA
       

        /**
         * populateItemDetails
         *
         * This will populate all fields in the view using the database object passed in.
         *
         * @param IConfigItem* - The database object for the item we want to display. We will use this to
         *                       set new values and apply. If this is NULL then the details should all be hidden
         */
        void populateItemDetails(TA_Base_Core::IConfigItem* currentItem);

        /**
         * refreshButtonAvailability
         *
         * This should be called after any modification to the fields. This will enable or disable
         * the reset and apply buttons based on whether or not any data has changed.
         */
        virtual void refreshButtonAvailability();




    // Overrides
	    // ClassWizard generated virtual function overrides
	    //{{AFX_VIRTUAL(TisRatisTagDetailView)
	public:
	virtual void OnInitialUpdate();
	protected:
	    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

    protected:

    #ifdef _DEBUG
	    virtual void AssertValid() const;
	    virtual void Dump(CDumpContext& dc) const;
    #endif


	    // Generated message map functions
	    //{{AFX_MSG(TisRatisTagDetailView)
	    afx_msg void onButtonReset();
	    afx_msg void onButtonApply();

        afx_msg void onKillfocusTagGroupEdt();
        afx_msg void onKillfocusDetailEdt();

        //}}AFX_MSG
	    DECLARE_MESSAGE_MAP()


    protected:

        /**
         * getConfigMessageType
         *
         * This should return the type of configuration update. ie ENTITY, OPERATOR etc.
         *
         * @return ConfigUpdateType - The type of component this update is for
         */
        virtual TA_Base_App::MessageSender::ConfigUpdateType getConfigMessageType() const
        {
            return TA_Base_App::MessageSender::TIS_RATIS_TAG;
        }


    private:
        /**
         * Copy Constructor
         *
         * Hidden as a private method so it is not used.
         */
        TisRatisTagDetailView( const TisRatisTagDetailView&);


        /**
         * Operator =
         *
         * Hidden as a private method so it is not used.
         */
        TisRatisTagDetailView& operator=(const TisRatisTagDetailView&);


        /**
         * showItemDetails
         *
         * This will show or hide all the controls for the Tis Ratis Tag details. These controls will be
         * hidden until the user selects a Tis Ratis Tag from the list.
         *
         * @param bool - This indicates if the controls are shown or not. true will display the
         *               controls and false will hide them
         */
        virtual void showItemDetails(bool isShown);


        /**
         * refreshEntityAndEntityType
         *
         * Only one of these items can be enabled at once based on the radio button checked
         * This retrieves the data from the IConfigTisRatisTag to determine which is enabled.
         * It then sets the correct check and enabled and disables the fields.
         */
        void refreshEntityAndEntityType();
    
        /**
         * populateAssociatedEntityArea
         *
         * Refreshes the list control showing all the associated entities
         */
        void populateAssociatedEntityArea(bool initialisation = false);
        
        enum EAssocUpdate
        {
            ADD_NEW,
            EDIT_EXISTING,
            REMOVE_EXISTING
        };

    private:
        // The titles for the change dialog box
        static const int TAG_GROUP_FIELD_LENGTH;
        static const int DETAIL_FIELD_LENGTH;

        TA_IRS_Core::IConfigTiRatisTag* m_configItem; // The current Tis Ratis Tag the user
                                                              // is configuring. This is the database object
                                                              // for it.

        TisRatisTagListView* m_listView; // This is the view in the top pane of the splitter
                                            // showing the list of all Tis Ratis Tags. We need to
                                            // use this to tell it when Tis Ratis Tag details have
                                            // changed.

        TisRatisTagDatabaseAccessor* m_databaseAccessor;  // The object that we can use to retrieve 
                                                             // information from the database.
    };
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

}


#endif // !defined(AFX_TisRatisTagDetailView_H__4046FE10_EABC_4CF5_B97A_F54C40A0D214__INCLUDED_)
