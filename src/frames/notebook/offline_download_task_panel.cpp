/////////////////////////////////////////////////////////////////////////////
// Name:        offline_download_task_panel.cpp
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     02/09/2018 17:48:31
// RCS-ID:      
// Copyright:   for free
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
#include "wx/imaglist.h"
////@end includes

#include "offline_download_task_panel.h"

////@begin XPM images
#include "../../resources/new_task.xpm"
#include "../../resources/delete_trash.xpm"
#include "../../resources/left_btn.xpm"
#include "../../resources/right_btn.xpm"
////@end XPM images


/*
 * OfflineDownloadTaskPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( OfflineDownloadTaskPanel, wxPanel )


/*
 * OfflineDownloadTaskPanel event table definition
 */

BEGIN_EVENT_TABLE( OfflineDownloadTaskPanel, wxPanel )

////@begin OfflineDownloadTaskPanel event table entries
////@end OfflineDownloadTaskPanel event table entries

END_EVENT_TABLE()


/*
 * OfflineDownloadTaskPanel constructors
 */

OfflineDownloadTaskPanel::OfflineDownloadTaskPanel()
{
    Init();
}

OfflineDownloadTaskPanel::OfflineDownloadTaskPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{
    Init();
    Create(parent, id, pos, size, style);
}


/*
 * OfflineDownloadTaskPanel creator
 */

bool OfflineDownloadTaskPanel::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{
////@begin OfflineDownloadTaskPanel creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxPanel::Create(parent, id, pos, size, style);
    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end OfflineDownloadTaskPanel creation
    return true;
}


/*
 * OfflineDownloadTaskPanel destructor
 */

OfflineDownloadTaskPanel::~OfflineDownloadTaskPanel()
{
////@begin OfflineDownloadTaskPanel destruction
////@end OfflineDownloadTaskPanel destruction
}


/*
 * Member initialisation
 */

void OfflineDownloadTaskPanel::Init()
{
////@begin OfflineDownloadTaskPanel member initialisation
////@end OfflineDownloadTaskPanel member initialisation
}


/*
 * Control creation for OfflineDownloadTaskPanel
 */

void OfflineDownloadTaskPanel::CreateControls()
{    
////@begin OfflineDownloadTaskPanel content construction
    OfflineDownloadTaskPanel* itemPanel2 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    itemPanel2->SetSizer(itemBoxSizer1);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer1->Add(itemBoxSizer5, 0, wxGROW, 5);

    itemBoxSizer5->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSearchCtrl* itemSearchCtrl2 = new wxSearchCtrl( itemPanel2, ID_SEARCHCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemSearchCtrl2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton3 = new wxBitmapButton( itemPanel2, ID_BITMAPBUTTON9, itemPanel2->GetBitmapResource(wxT("new_task.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBoxSizer5->Add(itemBitmapButton3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxListCtrl* itemListCtrl12 = new wxListCtrl( itemPanel2, ID_LISTCTRL1, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT );
    itemBoxSizer1->Add(itemListCtrl12, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer1->Add(itemBoxSizer8, 0, wxGROW, 5);

    wxCheckBox* itemCheckBox9 = new wxCheckBox( itemPanel2, ID_CHECKBOX1, _("Select All"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox9->SetValue(false);
    itemBoxSizer8->Add(itemCheckBox9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText10 = new wxStaticText( itemPanel2, wxID_STATIC, _("Selected:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(itemStaticText10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton11 = new wxBitmapButton( itemPanel2, ID_BITMAPBUTTON4, itemPanel2->GetBitmapResource(wxT("delete_trash.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBitmapButton11->SetHelpText(_("Delete"));
    if (OfflineDownloadTaskPanel::ShowToolTips())
        itemBitmapButton11->SetToolTip(_("Delete Select Files"));
    itemBoxSizer8->Add(itemBitmapButton11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer12 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer8->Add(itemBoxSizer12, 1, wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText13 = new wxStaticText( itemPanel2, wxID_STATIC, _("0 / 1024 Task this month"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemStaticText13, 0, wxALIGN_CENTER_HORIZONTAL, 5);

    wxBitmapButton* itemBitmapButton15 = new wxBitmapButton( itemPanel2, ID_BITMAPBUTTON8, itemPanel2->GetBitmapResource(wxT("left_btn.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBoxSizer8->Add(itemBitmapButton15, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl16 = new wxTextCtrl( itemPanel2, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(itemTextCtrl16, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton17 = new wxBitmapButton( itemPanel2, ID_BITMAPBUTTON12, itemPanel2->GetBitmapResource(wxT("right_btn.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBoxSizer8->Add(itemBitmapButton17, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

////@end OfflineDownloadTaskPanel content construction
}


/*
 * Should we show tooltips?
 */

bool OfflineDownloadTaskPanel::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap OfflineDownloadTaskPanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin OfflineDownloadTaskPanel bitmap retrieval
    wxUnusedVar(name);
    if (name == wxT("new_task.xpm"))
    {
        wxBitmap bitmap(new_task_xpm);
        return bitmap;
    }
    else if (name == wxT("delete_trash.xpm"))
    {
        wxBitmap bitmap(delete_trash_xpm);
        return bitmap;
    }
    else if (name == wxT("left_btn.xpm"))
    {
        wxBitmap bitmap(left_btn_xpm);
        return bitmap;
    }
    else if (name == wxT("right_btn.xpm"))
    {
        wxBitmap bitmap(right_btn_xpm);
        return bitmap;
    }
    return wxNullBitmap;
////@end OfflineDownloadTaskPanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon OfflineDownloadTaskPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin OfflineDownloadTaskPanel icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end OfflineDownloadTaskPanel icon retrieval
}
