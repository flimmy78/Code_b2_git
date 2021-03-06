/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/PRIV_3001/3001/transactive/app/system_control/banner/pages/ats_page/src/IscsBanner.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2018/03/14 13:51:20 $
  * Last modified by:  $Author: lim.cy $
  *
  */
// IscsBanner.cpp : Implementation of CIscsBanner
#include "app/system_control/banner/pages/ats_page/src/stdafx.h"
#include "app/system_control/banner/pages/ats_page/src/BannerInterface.h"
#include "app/system_control/banner/pages/ats_page/src/BannerInterface_i.c"
#include "app/system_control/banner/pages/ats_page/src/Resource.h"

#include "app/system_control/banner/pages/ats_page/src/IscsBanner.h"
#include "bus/banner_framework/src/constants.h"

/////////////////////////////////////////////////////////////////////////////
// CIscsBanner


STDMETHODIMP CIscsBanner::setAtsButtonState(BOOL flash)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState())
    PostMessage(HWND_BROADCAST, BANNER_CONST::WM_SET_FLASH_STATE, reinterpret_cast<WPARAM>(&BANNER_CONST::ATS), flash);
    return S_OK;
}
