/**
  * The source code in this file is the property of 
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source: $File: //depot/4669_T01271350/4669/transactive/app/pa/PAManager/src/IWindow.h $
  * @author Jade Lee
  * @version $Revision: #1 $
  * Last modification: $DateTime: 2008/11/28 16:26:01 $
  * Last modified by: $Author: builder $
  * 
  * IWindow allows querying for the windows hWnd (to avoid forcing
  *     delayed attachment to a window, when it can't pass in it's m_hWnd
  *     value to a class because it's not yet valid)
  *
  */


#if !defined(AFX_IWindow_H__4EBD5CE7_C4D0_43BC_A835_518CA9141975__INCLUDED_)
#define AFX_IWindow_H__4EBD5CE7_C4D0_43BC_A835_518CA9141975__INCLUDED_

class IWindow
{
public:
    virtual HWND    getHWnd() = 0;
};

#endif // AFX_IWindow_H__4EBD5CE7_C4D0_43BC_A835_518CA9141975__INCLUDED_