#if !defined(AFX_DUTYMANAGERDLG_H__2146B198_0486_4E14_BD4A_EDBAFDF01ABB__INCLUDED_)
#define AFX_DUTYMANAGERDLG_H__2146B198_0486_4E14_BD4A_EDBAFDF01ABB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/3001_TIP_NEW/TA_BASE/transactive/app/security/DutyManager/src/DutyManagerDlg.h $
  * @author:  Bart Golab
  * @version: $Revision: #6 $
  *
  * Last modification: $DateTime: 2013/04/29 14:29:02 $
  * Last modified by:  $Author: haijun.li $
  *
  * This class represents the main Rights Manager dialog window.
  *
  */


namespace TA_Base_App
{
	class OtherSesSubDutyPropertyPage;
	class DutyManagerBridge;
	//TD18095, replace inheritate from ISessionObserver, and IConfigDataObserver with aggregate two objects.
    class DutyManagerDlg : public TA_Base_Bus::TransActiveDialog,
						   public TA_Base_Core::SpecialisedMessageSubscriber<TA_Base_Core::CommsMessageCorbaDef>/*,
                           public TA_Base_Bus::ISessionObserver,
                           public TA_Base_Bus::IConfigDataObserver//*/
    {
    // Operations
    public:
	    DutyManagerDlg(TA_Base_Bus::IGUIAccess& genericGUICallback);
        virtual ~DutyManagerDlg();

		//TD18095, jianghp
		void init();
		//TD18095, jianghp

		//jinhua++
		SubsystemDutyPropertyPage& getSubsytemDutyPropertyPage();
		OtherSesSubDutyPropertyPage& getOhterSesSubDutyPropertyPage();

        /**
        * TA_Base_Core::SpecialisedMessageSubscriber interface
        *
        */
        virtual void receiveSpecialisedMessage(const TA_Base_Core::CommsMessageCorbaDef& message);

		static UINT initialiseSubsystemDutyGridThreadFun( LPVOID pParam  );
		
		//dazhi++
		static UINT getSessionIdsAsync( LPVOID pParam );
		static UINT initOperatorAccessFactoryAsync( LPVOID pParam  );
		//dazhi++

		bool isShowOhterSession()
		{
			return m_showOtherSession;
		}

    private:
        DutyManagerDlg(const DutyManagerDlg& dutyManagerDlg);
        DutyManagerDlg& operator=(const DutyManagerDlg& dutyManagerDlg);


    // Overrides
	    //{{AFX_VIRTUAL(DutyManagerDlg)
	protected:
	    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	    //}}AFX_VIRTUAL

	// Implementation
    protected:
	    // Generated message map functions
	    //{{AFX_MSG(DutyManagerDlg)
	    virtual BOOL OnInitDialog();
        afx_msg void OnAppAbout();
	    afx_msg void OnPaint();
	    afx_msg HCURSOR OnQueryDragIcon();
	    afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg	 void OnTimer(UINT nIDEvent);  //TD17082
		afx_msg void OnAppExit();
		afx_msg void OnClose();
		afx_msg void OnTransActiveHelp();
		afx_msg LRESULT OnReceiveDutyAgentRecover(WPARAM wParam, LPARAM lParam);
		afx_msg LRESULT OnPopulateData(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	    DECLARE_MESSAGE_MAP()


    // Dialog data
    private:
	    //{{AFX_DATA(DutyManagerDlg)
	enum { IDD = IDD_DUTY_MANAGER_DLG };
	//}}AFX_DATA

        void positionControls();  //TD17082

	    HICON m_hIcon;

        //std::string m_originalTitleText; TD18095, jianghp

		DutyManagerBridge * m_bridge;

        DutyManagerPropertySheet m_dutyPropertySheet;

        RegionDutyPropertyPage *m_regionDutyPropertyPage;
        SubsystemDutyPropertyPage *m_subsystemDutyPropertyPage;
		OtherSesSubDutyPropertyPage *m_otherSesSubDutyPropertyPage;

		bool m_shownStatus;

		//std::string m_showOtherSessionSt;
		bool m_showOtherSession;

		/*/TD18095, jianghp
        TA_Base_Bus::DutyDataStore m_dutyDataStore;
        TA_Base_Bus::DataCache& m_dataCache;
        TA_Base_Bus::SessionCache& m_sessionCache;
		//TD18095, jianghp*/

	public:
		static bool m_isMartixDataInited;
    };

} // namespace TA_Base_App

#endif // !defined(AFX_DUTYMANAGERDLG_H__2146B198_0486_4E14_BD4A_EDBAFDF01ABB__INCLUDED_)
