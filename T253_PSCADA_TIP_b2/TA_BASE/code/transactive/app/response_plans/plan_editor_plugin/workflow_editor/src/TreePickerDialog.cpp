// src/TreePickerDialog.cpp : implementation file
//

#include "stdafx.h"
#include "app/response_plans/plan_editor_plugin/workflow_element/src/IActivityParameter.h"
#include "SingleTreeDialog.h"
#include "MultipleTreeDialog.h"
#include "TreePickerDialog.h"


// TreePickerDialog dialog
TreePickerDialog::TreePickerDialog( ITreePicker& refPicker, const std::string& strName, CWnd* pParent, const int nRow ) :
Title( "" ),
DisplayValue( "" ),
ListUpdated( false ),
m_nRow( nRow ),
m_strName( strName ),
m_pParent( pParent ),
m_refPicker( refPicker )
{
}

TreePickerDialog::~TreePickerDialog()
{
}

int TreePickerDialog::DoModal()
{
    int nAction = 0;

    std::vector<TreeItem> vecSourceItems;
    std::vector<unsigned int> vecSelected;
    unsigned int unMaxItems = 0u;

    m_refPicker.getInputTreeItems( m_strName, vecSourceItems, vecSelected, unMaxItems );

    if ( 1u == unMaxItems )
    {
        SingleTreeDialog dlgPopup( m_refPicker, m_strName, vecSourceItems, vecSelected, m_pParent, m_nRow );
        dlgPopup.Title = Title;

        nAction = dlgPopup.DoModal();

        DisplayValue = dlgPopup.DisplayValue.c_str();
        ListUpdated = dlgPopup.ListUpdated;
    }
    else
    {
        MultipleTreeDialog dlgPopup( m_refPicker, m_strName, vecSourceItems, vecSelected, unMaxItems, m_pParent, m_nRow );
        dlgPopup.Title = Title;

        nAction = dlgPopup.DoModal();

        DisplayValue = dlgPopup.DisplayValue.c_str();
        ListUpdated = dlgPopup.ListUpdated;
    }

    return nAction;
}
