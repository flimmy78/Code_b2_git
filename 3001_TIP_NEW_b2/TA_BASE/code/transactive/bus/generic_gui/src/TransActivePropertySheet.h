/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/bus/generic_gui/src/TransActivePropertySheet.h $
  * @author:  Karen Graham
  * @version: $Revision: #2 $
  *
  * Last modification: $DateTime: 2012/02/06 16:15:14 $
  * Last modified by:  $Author: haijun.li $
  * 
  * This inherits from CPropertySheet and implements all common functionality for
  * TransActive property sheets.
  */

#if !defined(AFX_TRANSACTIVEPROPERTYSHEET_H__F9076B67_5412_11D5_B5EE_0080AD74DCEE__INCLUDED_)
#define AFX_TRANSACTIVEPROPERTYSHEET_H__F9076B67_5412_11D5_B5EE_0080AD74DCEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bus/generic_gui/src/StdAfx.h"
#include "bus/generic_gui/src/ResizingProperties.h"

namespace TA_Base_Bus
{
    class IGUIAccess;

    /////////////////////////////////////////////////////////////////////////////
    // CEventsGuiDlg dialog

    class TransActivePropertySheet : public CPropertySheet
    {
        DECLARE_DYNAMIC(TransActivePropertySheet)
    
    // Construction
    public:

        /**
         * Constructor
         *
         * @param IGUIAccess& - The implementation of an IGUIAccess. This must not be NULL.
         * @param UINT - The resource id of a caption for the property sheet.
         * @param CWnd* - The parent window.
         */
        TransActivePropertySheet(IGUIAccess& genericGUICallback,
                                 UINT captionId,
                                 CWnd* pParent = NULL);

		/**
         * Destructor
         *
         */
		virtual ~TransActivePropertySheet() {};

        /**
         * DestroyWindow
         *
         * This method must be implemented to ensure that when the window
         * is destroyed the dialog tells the GUIAccess object to clean up
         */
        virtual BOOL DestroyWindow();


    protected:

        /**
         * setResizingProperties
         *
         * This method should be called to set the resizing properties of the
         * property sheet. It must be called before OnInitDialog is called. Ideally it
         * will be called from the constructor of the property sheet.
         */
        void setResizingProperties(const ResizingProperties& resizingProperties);

        /**
         * getGenericGUICallbackObject
         *
         * This method is provided so classes that inherit from this class can
         * use the IGUIAccess object.
         *
         * @return IGUIAcces& - A reference to the GUI object so callbacks can
         *                      be performed.
         */
        IGUIAccess& getGenericGUICallbackObject();

        /**
         * OnInitDialog
         *
         * This method must be implemented to ensure that when the dialog is
         * initialised all the correct GenericGUI calls are made.
         */
        virtual BOOL OnInitDialog();

        /**
         * OnSysCommand
         *
         * This method must be implemented to handle requests to display
         * the About box.
         */
        virtual afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

        /**
         * OnOK
         *
         * This method has been implemented to hide accidental calls when
         * the Enter key is pressed. It can be override with new behaviour if required.
         */
        virtual afx_msg void OnOK();

        /**
         * OnCancel
         *
         * This method has been implemented to hide accidental calls when
         * the ESC key is pressed. It can be override with new behaviour if required.
         */
        virtual afx_msg void OnCancel();

        /**
         * OnGetMinMaxInfo
         *
         * This method controls the resizing and maximising of the frame.
         * It ensures the frame is not resized to an inappropriate size.
         * It uses the m_resizingProperties member variable.
         */
        virtual afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);

        /**
         * OnWindowPosChanging
         *
         * This method controls the resizing of the frame.
         * It ensures the frame is not resized to an inappropriate size.
         * It uses the m_resizingProperties member variable.
         */
        virtual afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);

        /**
         * OnSetWindowPosition
         *
         * This method is called whenever GenericGui gets a new window position
         * from control station
         * 
         */
        virtual afx_msg LRESULT OnSetWindowPosition(WPARAM wParam, LPARAM lParam);

        DECLARE_MESSAGE_MAP()

    private:

        // Reference to the callback object for GenericGUI
        IGUIAccess& m_genericGUICallback;

        // This contains the details on how the window can be resized.
        ResizingProperties m_resizingProperties;

        // This indicates if the resizing properties have been set
        bool m_arePropertiesSet;

        // This variable stores the monitor on which this application is currently located
        int m_currentScreen;

        // This is the available screen rectangle for the current screen. By caching this, 
        // we do not have to query the control station until we change screens.
        CRect m_workingArea;

    };
}

#endif // !defined(AFX_TRANSACTIVEPROPERTYSHEET_H__F9076B67_5412_11D5_B5EE_0080AD74DCEE__INCLUDED_)
