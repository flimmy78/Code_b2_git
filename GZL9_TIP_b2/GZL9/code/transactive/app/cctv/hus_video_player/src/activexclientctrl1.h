#pragma once

// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CActivexclientctrl1 wrapper class

class CActivexclientctrl1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CActivexclientctrl1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x489B7964, 0xF1E4, 0x4826, { 0x93, 0x62, 0x9E, 0xB, 0xCA, 0x75, 0x84, 0x1F } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Attributes
public:


// Operations
public:

// _DActivexClient

// Functions
//

	void Login()
	{
		InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void FullScreen()
	{
		InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ExitFullScreen()
	{
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

CString GetsiteID()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}
void SetsiteID(CString propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}
CString GetsiteIP()
{
	CString result;
	GetProperty(0x2, VT_BSTR, (void*)&result);
	return result;
}
void SetsiteIP(CString propVal)
{
	SetProperty(0x2, VT_BSTR, propVal);
}
CString GetuserName()
{
	CString result;
	GetProperty(0x3, VT_BSTR, (void*)&result);
	return result;
}
void SetuserName(CString propVal)
{
	SetProperty(0x3, VT_BSTR, propVal);
}
CString Getpwd()
{
	CString result;
	GetProperty(0x4, VT_BSTR, (void*)&result);
	return result;
}
void Setpwd(CString propVal)
{
	SetProperty(0x4, VT_BSTR, propVal);
}
CString GetclientIP()
{
	CString result;
	GetProperty(0x5, VT_BSTR, (void*)&result);
	return result;
}
void SetclientIP(CString propVal)
{
	SetProperty(0x5, VT_BSTR, propVal);
}
CString GetclientPort()
{
	CString result;
	GetProperty(0x6, VT_BSTR, (void*)&result);
	return result;
}
void SetclientPort(CString propVal)
{
	SetProperty(0x6, VT_BSTR, propVal);
}
long Getwidth()
{
	long result;
	GetProperty(0x7, VT_I4, (void*)&result);
	return result;
}
void Setwidth(long propVal)
{
	SetProperty(0x7, VT_I4, propVal);
}
long Getheight()
{
	long result;
	GetProperty(0x8, VT_I4, (void*)&result);
	return result;
}
void Setheight(long propVal)
{
	SetProperty(0x8, VT_I4, propVal);
}


};
