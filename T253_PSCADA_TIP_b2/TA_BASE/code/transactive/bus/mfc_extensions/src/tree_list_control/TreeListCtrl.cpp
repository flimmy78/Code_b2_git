/**
  * The source code in this file is the property of
  * Ripple Systems and is not for redistribution
  * in any form.
  *
  * Source:   $File: //depot/T253_PSCADA_TIP/TA_BASE/transactive/bus/mfc_extensions/src/tree_list_control/TreeListCtrl.cpp $
  * @author:  Ripple
  * @version: $Revision: #1 $
  *
  * Last modification: $DateTime: 2017/10/31 16:21:54 $
  * Last modified by:  $Author: CM $
  *
  */
/*
 * Implementation of the TreeListCtrl
 *
 * Copyright (c)1999 David Carballo, All Right Reserved
 *
 * Created June 1999
 * Revised: August 1999
 * Written by David Carballo
 * Internet: fibeto@redestb.es
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 */

#pragma warning (disable : 4786)

#include "bus/mfc_extensions/src/StdAfx.h"
#include "TreeListCtrl.h"

#include "bus/mfc_extensions/src/resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CTreeListCtrl, ListCtrlSelNoFocus)
	//{{AFX_MSG_MAP(CTreeListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrl

CTreeListCtrl::CTreeListCtrl()
:
m_indentMultiplier(1)
{
}

CTreeListCtrl::~CTreeListCtrl()
{
}


BOOL  CTreeListCtrl::SetItemData(int nItem,DWORD dwData)
{
	//int iPos = ListCtrlSelNoFocus::GetItemData(nItem);
	m_tree.at(nItem).m_itemData = dwData;
	return TRUE;
}

DWORD CTreeListCtrl::GetItemData(int nItem) const
{
	//int iPos = ListCtrlSelNoFocus::GetItemData(nItem);
	return m_tree.at(nItem).m_itemData;
}


/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrl overrides

void CTreeListCtrl::PreSubclassWindow() 
{
	// LVS_EX_GRIDLINES // 5.0: LVS_EX_LABELTIP 
	SetExtendedStyle(LVS_EX_FULLROWSELECT);

	if (NULL == m_ilState.GetSafeHandle())
	{
		m_ilState.Create(IDB_STATE_2, 16, 1, RGB(255, 0, 0));
	}
	SetImageList(&m_ilState, LVSIL_STATE);
	
	ListCtrlSelNoFocus::PreSubclassWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrl operations

BOOL CTreeListCtrl::Create
	(
	DWORD			dwStyle,
	const RECT&		rect,
	CWnd*			pParentWnd,
	UINT			nID
	)
{
	if (!ListCtrlSelNoFocus::Create(dwStyle, rect, pParentWnd, nID))
		return FALSE;

	// LVS_EX_GRIDLINES // 5.0: LVS_EX_LABELTIP 
	SetExtendedStyle(LVS_EX_FULLROWSELECT);

	if (NULL == m_ilState.GetSafeHandle())
	{
		m_ilState.Create(IDB_STATE_2, 16, 1, RGB(255, 0, 0));
	}
	SetImageList(&m_ilState, LVSIL_STATE);

	return TRUE;
}

int CTreeListCtrl::AddItem
	(
	LPCTSTR		lpszItem,
	int			nImage,
	int			nLevel
	)
{
	LVITEM			item;
	tree_list_info	info;
	int				nItem;

	// If the list is empty clear the tree
	if (GetItemCount()<1)
	{
		m_tree.clear();
	}
	
	nItem = m_tree.size();
	info.m_nLevel	= nLevel;
	info.m_nImage	= nImage;
	info.m_lstCols.resize(GetHeaderCtrl()->GetItemCount());
	info.m_lstCols[0] = lpszItem;
	info.m_bCollapsed = true;
	info.m_itemData = 0L;
	m_tree.push_back(info);

	item.mask		= LVIF_TEXT | LVIF_IMAGE | LVIF_INDENT | LVIF_STATE | LVIF_PARAM;
	item.iItem		= GetItemCount(); //nItem;
	item.iSubItem	= 0;
	item.pszText	= (LPTSTR)(LPCTSTR)info.m_lstCols[0];
	item.iImage		= info.m_nImage;
	item.iIndent	= m_indentMultiplier * info.m_nLevel;
	item.state		= getStateImageState(m_tree.size() - 1, info.m_bCollapsed);
    item.stateMask	= LVIS_STATEIMAGEMASK;
	item.lParam		= nItem;

	if (info.m_nLevel == 0)
	{
		ListCtrlSelNoFocus::InsertItem(&item);
	}

    // If adding item with nonzero level, check if parent items state needs to change
    // (to indicate it now has children)
    // This only works for first level collapsed nodes..
    if (info.m_nLevel == 1 && m_tree.size() >= 2)
    {
        DWORD parentIndex = m_tree.size() - 2;
        tree_list_info& candidateParent = m_tree.at(parentIndex);
        if (0 == candidateParent.m_nLevel)
        {
            DWORD state = getStateImageState(parentIndex, candidateParent.m_bCollapsed);
            int nItem = GetItemCount() - 1;
            SetItemState(nItem, state, LVIS_STATEIMAGEMASK);
        }
    }

	return nItem; //item.iItem;
}

BOOL  CTreeListCtrl::SetVItemText
	(
	int			vItem,
	int			nSubItem,
	LPCTSTR		lpszText
	)
{
	m_tree.at(vItem).m_lstCols[nSubItem] = lpszText;

	// If it is currently displayed then update it
	int iPos = findItem(vItem);
	if (iPos==-1)
	{
		// not displayed
		return true;
	}
	
	return ListCtrlSelNoFocus::SetItemText(iPos, nSubItem, lpszText);
}

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrl protected functions

int CTreeListCtrl::InsertItem
	(
	int				nItem,
	int				nPosArray,
	tree_list_info&	info
	)
{
	LVITEM			item;

	item.mask		= LVIF_TEXT | LVIF_IMAGE | LVIF_INDENT | LVIF_STATE | LVIF_PARAM;
	item.iItem		= nItem;
	item.iSubItem	= 0;
	item.pszText	= (LPTSTR)(LPCTSTR)info.m_lstCols[0];
	item.iImage		= info.m_nImage;
	item.iIndent	= m_indentMultiplier * info.m_nLevel;
	item.state		= getStateImageState(nPosArray, info.m_bCollapsed);
	item.stateMask	= LVIS_STATEIMAGEMASK;
	item.lParam		= nPosArray;

	int	nItemRes = ListCtrlSelNoFocus::InsertItem(&item);

    // If these are different, it's because someone has flagged the style
    // of this list control to be sorted alphabetically.  This class will
    // not work in this case...
    ASSERT(nItemRes == nItem);

	for (int i = 1; i < static_cast<int>(info.m_lstCols.size()); i++)
	{
		ListCtrlSelNoFocus::SetItemText(nItemRes, i, info.m_lstCols[i]);
	}
	return nItemRes;
}

BOOL CTreeListCtrl::DeleteAllItems()
{
	BOOL result = ListCtrlSelNoFocus::DeleteAllItems();

    // Clear local information tree afterwards, in case LVN_DELETEITEM
    // notifications query this class for virtual index information
	m_tree.clear();

    return result;
}

void CTreeListCtrl::Collapse
	(
	int		nPos,
	int		nItem
	)
{
	int				nLevel;
	int				nLast;
	LVITEM			item;
	
	tree_list_info&	info = m_tree[nPos];
	info.m_bCollapsed = true;

	SetRedraw(0);
	nLevel	= info.m_nLevel;
	nLast	= GetItemCount();
	item.mask		= LVIF_PARAM;
	item.iSubItem	= 0;

	int nCounter = nItem + 1;
	if (nCounter < nLast)
	{
		do
		{
			item.iItem		= nCounter;
			GetItem(&item);
			if (m_tree[item.lParam].m_nLevel > nLevel)
				DeleteItem(nItem + 1);
		}
		while (m_tree[item.lParam].m_nLevel > nLevel && GetItemCount() > nCounter);
	}

	SetRedraw(1);
}


bool CTreeListCtrl::isVItemCollapsed(int vItem)
{
	tree_list_info&	info	= m_tree[vItem];
	return info.m_bCollapsed;
}


int CTreeListCtrl::GetActualIndexFromVirtual(int vItem)
{
    for (int i = 0; i < GetItemCount(); i ++)
    {
        if (vItem == static_cast<int>(ListCtrlSelNoFocus::GetItemData(i)))
        {
            return i;
        }
    }

    return -1;
}


void CTreeListCtrl::Expand(int nItem)
{    
    int vItem = GetVirtualIndexFromActual(nItem);
    
    ASSERT(isVItemCollapsed(vItem));

    int	nInsert = nItem;
	SetRedraw(0);
	Expand(vItem, false, nInsert);
	SetRedraw(1);
	SetItemState(nItem, getStateImageState(vItem, false), LVIS_STATEIMAGEMASK);
}


int CTreeListCtrl::getVItemLevel(int vItem)
{
    tree_list_info&	info	= m_tree[vItem];
    return info.m_nLevel; 
}


int CTreeListCtrl::Expand
	(
	int		nItem,
	bool	bRecursive,
	int&	nCounterInsert
	)
{
	tree_list_info&	info	= m_tree[nItem];
	info.m_bCollapsed		= false;

	int				nCounter;
	int				nLevel;
	
	nCounter		= nItem + 1;
	nCounterInsert	= nCounterInsert + 1;
	nLevel			= info.m_nLevel;
	while (nCounter < static_cast<int>(m_tree.size()) && m_tree[nCounter].m_nLevel > nLevel)
	{
		if (m_tree[nCounter].m_nLevel > nLevel)
		{
			if (bRecursive)
			{
				m_tree[nCounter].m_bCollapsed = false;
			}
			InsertItem(nCounterInsert, nCounter, m_tree[nCounter]);
		}

		if (bRecursive || !m_tree[nCounter].m_bCollapsed)
		{
			nCounter = Expand(nCounter, bRecursive, nCounterInsert);
		}
		else
		{
			int	nSonLevel;

			nSonLevel = m_tree[nCounter].m_nLevel;
			while (++nCounter < static_cast<int>(m_tree.size()) && m_tree[nCounter].m_nLevel > nSonLevel)
			{
			}

			nCounterInsert++;
		}		
	}
	
	return nCounter;
}

/////////////////////////////////////////////////////////////////////////////
// CTreeListCtrl message handlers

void CTreeListCtrl::OnClick
	(
	NMHDR*		pNMHDR,
	LRESULT*	pResult
	)
{
	LPNMITEMACTIVATE	pItemActivate = (LPNMITEMACTIVATE)pNMHDR;

	CRect				rect;

	GetItemRect(pItemActivate->iItem, rect, LVIR_ICON);
		
	if (pItemActivate->ptAction.x < rect.left)
	{
		LVITEM	item;

		item.mask		= LVIF_INDENT | LVIF_PARAM;
		item.iItem		= pItemActivate->iItem;
		item.iSubItem	= 0;
		GetItem(&item);

		if (static_cast<unsigned long>(pItemActivate->ptAction.x) > (item.iIndent / m_indentMultiplier) * 16)
		{
			if (m_tree[item.lParam].m_bCollapsed)
			{	
                Expand(pItemActivate->iItem);
			}
			else
			{				
				SetRedraw(0);
				Collapse(item.lParam, pItemActivate->iItem);
				SetRedraw(1);
				SetItemState(pItemActivate->iItem, getStateImageState(item.lParam, true), LVIS_STATEIMAGEMASK);
			}
		}
	}
	
	*pResult = 0;
}

void CTreeListCtrl::OnKeyDown
	(
	UINT	nChar,
	UINT	nRepCnt,
	UINT	nFlags
	)
{
	int		nItem	=	GetNextItem(-1, LVNI_SELECTED);	

	if (nItem == -1)
	{
		ListCtrlSelNoFocus::OnKeyDown(nChar, nRepCnt, nFlags);
		return;
	}
	
	LVITEM		item;

	item.mask		= LVIF_INDENT | LVIF_PARAM;
	item.iItem		= nItem;
	item.iSubItem	= 0;
	GetItem(&item);

	switch (nChar)
	{
		case VK_ADD:
			if (m_tree[item.lParam].m_bCollapsed)
			{	
				int	nInsert = nItem;
				SetRedraw(0);
				Expand(item.lParam, false, nInsert);
				SetRedraw(1);
				SetItemState(nItem, getStateImageState(item.lParam, false), LVIS_STATEIMAGEMASK);
			}
			break;
		case VK_SUBTRACT:
			if (!m_tree[item.lParam].m_bCollapsed)
			{				
				SetRedraw(0);
				Collapse(item.lParam, nItem);
				SetRedraw(1);
				SetItemState(nItem, getStateImageState(item.lParam, true), LVIS_STATEIMAGEMASK);
			}
			break;
		case VK_RIGHT:
			if (m_tree[item.lParam].m_bCollapsed)
			{	
				int	nInsert = nItem;
				SetRedraw(0);
				Expand(item.lParam, false, nInsert);
				SetRedraw(1);
				SetItemState(nItem, getStateImageState(item.lParam, false), LVIS_STATEIMAGEMASK);
			}
			else
			{
				// If any child, move to the first one
				int nNextItem	= item.lParam + 1;
				if (nNextItem < static_cast<int>(m_tree.size()) && m_tree[nNextItem].m_nLevel > m_tree[item.lParam].m_nLevel)
				{
					SetItemState(nItem + 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
				}
			}
			break;
		case VK_LEFT:
			if (!m_tree[item.lParam].m_bCollapsed)
			{				
				SetRedraw(0);
				Collapse(item.lParam, nItem);
				SetRedraw(1);
				SetItemState(nItem, getStateImageState(item.lParam, true), LVIS_STATEIMAGEMASK);
			}
			else
			{
				// Move to our parent
				int nPrevItem	= item.lParam - 1;
				int	nLevel		= m_tree[item.lParam].m_nLevel;

				while (nPrevItem >= 0 && nLevel <= m_tree[nPrevItem].m_nLevel)
				{
					--nPrevItem;
				}

				if (nPrevItem >= 0)
				{
					LVFINDINFO		info;
					
					info.flags		= LVFI_PARAM;
					info.lParam		= nPrevItem;
			
					SetItemState(FindItem(&info), LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
				}
			}
			break;
		default:
			ListCtrlSelNoFocus::OnKeyDown(nChar, nRepCnt, nFlags);
			break;
	}
}

void CTreeListCtrl::OnChar
	(
	UINT	nChar,
	UINT	nRepCnt,
	UINT	nFlags
	) 
{
	int		nItem	=	GetNextItem(-1, LVNI_SELECTED);	

	if (nItem != -1)
	{
		LVITEM		item;

		item.mask		= LVIF_INDENT | LVIF_PARAM;
		item.iItem		= nItem;
		item.iSubItem	= 0;
		GetItem(&item);

		if (nChar == '*')
		{
			// TODO: Recursively expands items 
			if (m_tree[item.lParam].m_bCollapsed)
			{	
				int	nInsert = nItem;
				SetRedraw(0);
				Expand(item.lParam, true, nInsert);
				SetRedraw(1);
				SetItemState(nItem, getStateImageState(item.lParam, false), LVIS_STATEIMAGEMASK);
			}
		}	
	}

	ListCtrlSelNoFocus::OnChar(nChar, nRepCnt, nFlags);
}




int CTreeListCtrl::findItem(int nItem)
{
	int iPos = -1;

	for (iPos=0;iPos<GetItemCount();iPos++)
	{
		if (ListCtrlSelNoFocus::GetItemData(iPos)==static_cast<unsigned long>(nItem))
		{
			return iPos;
		}
	}

	// Not found
	return -1;
}


void CTreeListCtrl::setupIndentWithoutIcons(DWORD indentPixels)
{
    m_indentMultiplier = indentPixels;

    if (0 == m_dummyImageList.GetSafeHandle() )
    {
        // Load up dummy icon, that is small enough such that user won't percieve it
    	m_dummyImageList.Create(IDB_EMPTY, 1, 1, RGB(255, 0, 0));	
	    SetImageList(&m_dummyImageList, LVSIL_SMALL);
    }
}


DWORD CTreeListCtrl::getStateImageState(DWORD indexIntoTree, bool showCollapsed)
{        
    bool hasChildren = false;

    DWORD nextIndex = indexIntoTree + 1;
    // Check that there is a item one level deeper immediately after us in array
    if (nextIndex < m_tree.size() &&    
        m_tree[nextIndex].m_nLevel > m_tree[indexIntoTree].m_nLevel)
    {
        hasChildren = true;
    }
    
    if (hasChildren)
    {
        // Show different images depending on collapsed state
        return INDEXTOSTATEIMAGEMASK(showCollapsed ? 1 : 2);
    }
    else
    {
        // Otherwise this is a leaf node
        return INDEXTOSTATEIMAGEMASK(3);
    }
}


std::vector<DWORD> CTreeListCtrl::fetchExpandedNodeItemData()
{
    std::vector<DWORD> result;

    for (int vIndex = 0; vIndex < GetVItemCount(); ++vIndex)
    {
        if (!isVItemCollapsed(vIndex))
        {
            // This node is expanded
            result.push_back(GetVItemData(vIndex));
        }
    }

    return result;
}
