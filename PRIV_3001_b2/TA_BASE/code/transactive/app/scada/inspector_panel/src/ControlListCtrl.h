/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/TA_BASE/transactive/app/scada/inspector_panel/src/ControlListCtrl.h $
  * @author:  Andy Parker
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  * 
  * This class manages the list display used to show the basic control information in
  * the CControlDialog class.
  *
  */

#ifndef CONTROLLISTCTRL_H
#define CONTROLLISTCTRL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bus/mfc_extensions/src/editable_list_control/EditableListCtrl.h"
#include "bus/scada/common_library/src/CommonDefs.h"

namespace TA_Base_Bus
{
	class DataPointProxySmartPtr;
}

namespace TA_Base_App
{
	class CEquipment;

	/////////////////////////////////////////////////////////////////////////////
	// CDataPointListCtrl window

	//TD15649, simplified this class 
	//by just responsing to the control state events of the visiable output datapoints
	//instead of using triggering entity of all datapoints to refresh the control state of visiable output datapoints
	
	class CControlListCtrl : public CEditableListCtrl, ICellManager
	{
		// Construction
		public:
			CControlListCtrl();

		// Attributes
		public:

		// Operations
		public:
			void setEquipment(CEquipment* equipment);

		// Overrides
			// ClassWizard generated virtual function overrides
			//{{AFX_VIRTUAL(CControlListCtrl)
			protected:
			virtual void PreSubclassWindow();
			//}}AFX_VIRTUAL

		// Implementation
		public:
			virtual ~CControlListCtrl();

			// ICellManager methods
			virtual CellType GetCellType(CEditableListCtrl* listCtrl, int item, int subItem);
            virtual unsigned long GetCellMaximumCharacters(CEditableListCtrl* listCtrl, int item, int subItem);
			virtual CellData GetCellData(CEditableListCtrl* listCtrl, int item, int subItem);
            virtual CString GetCellMask(CEditableListCtrl* listCtrl, int item, int subItem);
            virtual char GetCellMaskPromptChar(CEditableListCtrl* listCtrl, int item, int subItem);
			virtual bool UpdateCellValue(CEditableListCtrl* listCtrl, int item, int subItem, CString value);
			
			void updateDataPoint(unsigned long key, TA_Base_Bus::ScadaEntityUpdateType updateType);
			void updateDataNode(TA_Base_Bus::ScadaEntityUpdateType updateType);
			bool isOkToChangeTab();
			void updatePermissions(bool skipAccessCheck = false);
			bool isAnyDataPointsDisplayedOnScreen() const;
			void refreshDataPoints(); //wenching++ (TD13353)
			//TD15438, override the function to get a chance to adjust columns width.
			virtual BOOL SetWindowPos( const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags );
			
			// Generated message map functions
		protected:
			//{{AFX_MSG(CControlListCtrl)
			afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
			//}}AFX_MSG
        	//afx_msg void onCustomDrawList ( NMHDR* pNMHDR, LRESULT* pResult );

			DECLARE_MESSAGE_MAP()

			void SetupList();
			void DisplayDataPoints();
			void UpdateDataPointDisplay ( int iPoint, int nItem, TA_Base_Bus::ScadaEntityUpdateType updateType );
			std::string addControlStateToStatusLine ( TA_Base_Bus::DataPointProxySmartPtr & datapoint, TA_Base_Bus::EDataPointControlState state );
			std::string getControlStatusString ( TA_Base_Bus::EDataPointControlState state );
			void UpdateControlState();

			//add by tercel
			virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

		private:

			volatile bool					m_dataPointsDisplayedOnScreen;
			volatile bool					m_initialState; //wenching++ (TD12608)
			
			CEquipment*						m_equipment;
			std::map<unsigned int, bool>	m_setValueActionAllowed;

            static const COLORREF       COLOUR_ALARM;  // colour to be used for showing alarms
            static const COLORREF       COLOUR_DISABLE; // colour to be used for showing disabled data points
            static const COLORREF       COLOUR_NORMAL; // colour to be used for showing normal data points
	};
}

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // ifndef CONTROLLISTCTRL_H
