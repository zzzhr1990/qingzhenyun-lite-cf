/////////////////////////////////////////////////////////////////////////////
// Name:        my_remote_file.cpp
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     02/09/2018 17:46:18
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

#include "my_remote_file.h"

////@begin XPM images
#include "../../resources/refresh.xpm"
#include "../../resources/up_level.xpm"
#include "../../resources/search.xpm"
#include "../../resources/new_directory.xpm"
#include "../../resources/delete_trash.xpm"
#include "../../resources/copy.xpm"
#include "../../resources/left_btn.xpm"
#include "../../resources/right_btn.xpm"
////@end XPM images


/*
 * NyRemoteFilePanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( NyRemoteFilePanel, wxPanel )


/*
 * NyRemoteFilePanel event table definition
 */

BEGIN_EVENT_TABLE( NyRemoteFilePanel, wxPanel )

////@begin NyRemoteFilePanel event table entries
////@end NyRemoteFilePanel event table entries

END_EVENT_TABLE()


/*
 * NyRemoteFilePanel constructors
 */

NyRemoteFilePanel::NyRemoteFilePanel()
{
    Init();
}

NyRemoteFilePanel::NyRemoteFilePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{
    Init();
    Create(parent, id, pos, size, style);
}


/*
 * NyRemoteFilePanel creator
 */

bool NyRemoteFilePanel::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{
////@begin NyRemoteFilePanel creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxPanel::Create(parent, id, pos, size, style);
    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end NyRemoteFilePanel creation
    return true;
}


/*
 * NyRemoteFilePanel destructor
 */

NyRemoteFilePanel::~NyRemoteFilePanel()
{
////@begin NyRemoteFilePanel destruction
////@end NyRemoteFilePanel destruction
}


/*
 * Member initialisation
 */

void NyRemoteFilePanel::Init()
{
////@begin NyRemoteFilePanel member initialisation
////@end NyRemoteFilePanel member initialisation
}


/*
 * Control creation for NyRemoteFilePanel
 */

void NyRemoteFilePanel::CreateControls()
{    
////@begin NyRemoteFilePanel content construction
    NyRemoteFilePanel* itemPanel1 = this;

    this->SetName(wxT("MyRemoteFiles"));
    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxGROW, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemPanel1, wxID_STATIC, _("Current Path"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl5 = new wxTextCtrl( itemPanel1, ID_TEXTCTRL, _("/"), wxDefaultPosition, wxDefaultSize, 0 );
    itemTextCtrl5->Enable(false);
    itemBoxSizer3->Add(itemTextCtrl5, 1, wxGROW|wxALL, 5);

    wxBitmapButton* itemBitmapButton6 = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON, itemPanel1->GetBitmapResource(wxT("refresh.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBitmapButton6->SetHelpText(_("Refresh"));
    if (NyRemoteFilePanel::ShowToolTips())
        itemBitmapButton6->SetToolTip(_("Refresh"));
    itemBoxSizer3->Add(itemBitmapButton6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton2 = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON5, itemPanel1->GetBitmapResource(wxT("up_level.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBitmapButton2->SetHelpText(_("Refresh"));
    if (NyRemoteFilePanel::ShowToolTips())
        itemBitmapButton2->SetToolTip(_("Refresh"));
    itemBoxSizer3->Add(itemBitmapButton2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton7 = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON1, itemPanel1->GetBitmapResource(wxT("search.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBitmapButton7->SetHelpText(_("Search"));
    if (NyRemoteFilePanel::ShowToolTips())
        itemBitmapButton7->SetToolTip(_("Search"));
    itemBoxSizer3->Add(itemBitmapButton7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton1 = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON23, itemPanel1->GetBitmapResource(wxT("new_directory.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBitmapButton1->SetHelpText(_("New directory"));
    if (NyRemoteFilePanel::ShowToolTips())
        itemBitmapButton1->SetToolTip(_("New directory"));
    itemBoxSizer3->Add(itemBitmapButton1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxListCtrl* itemListCtrl1 = new wxListCtrl( itemPanel1, ID_LISTCTRL, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT );
    itemBoxSizer2->Add(itemListCtrl1, 1, wxGROW|wxALL, 5);
	itemListCtrl1->AppendColumn(_("Type"),wxLIST_FORMAT_CENTER,120);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer4, 0, wxGROW, 5);

    wxCheckBox* itemCheckBox1 = new wxCheckBox( itemPanel1, ID_CHECKBOX, _("Select All"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox1->SetValue(false);
    itemBoxSizer4->Add(itemCheckBox1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText2 = new wxStaticText( itemPanel1, wxID_STATIC, _("Selected:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemStaticText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton5 = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON2, itemPanel1->GetBitmapResource(wxT("delete_trash.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBitmapButton5->SetHelpText(_("Delete"));
    if (NyRemoteFilePanel::ShowToolTips())
        itemBitmapButton5->SetToolTip(_("Delete Select Files"));
    itemBoxSizer4->Add(itemBitmapButton5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton8 = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON3, itemPanel1->GetBitmapResource(wxT("copy.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBoxSizer4->Add(itemBitmapButton8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer4->Add(itemBoxSizer6, 1, wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( itemPanel1, wxID_STATIC, _("0 / 1024 MB"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(itemStaticText7, 0, wxALIGN_CENTER_HORIZONTAL, 5);

    wxBitmapButton* itemBitmapButton12 = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON6, itemPanel1->GetBitmapResource(wxT("left_btn.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBoxSizer4->Add(itemBitmapButton12, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl13 = new wxTextCtrl( itemPanel1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemTextCtrl13, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton14 = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON7, itemPanel1->GetBitmapResource(wxT("right_btn.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBoxSizer4->Add(itemBitmapButton14, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

////@end NyRemoteFilePanel content construction
}


/*
 * Should we show tooltips?
 */

bool NyRemoteFilePanel::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap NyRemoteFilePanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin NyRemoteFilePanel bitmap retrieval
    wxUnusedVar(name);
    if (name == wxT("refresh.xpm"))
    {
        wxBitmap bitmap(refresh_xpm);
        return bitmap;
    }
    else if (name == wxT("up_level.xpm"))
    {
        wxBitmap bitmap(up_level_xpm);
        return bitmap;
    }
    else if (name == wxT("search.xpm"))
    {
        wxBitmap bitmap(search_xpm);
        return bitmap;
    }
    else if (name == wxT("new_directory.xpm"))
    {
        wxBitmap bitmap(new_directory_xpm);
        return bitmap;
    }
    else if (name == wxT("delete_trash.xpm"))
    {
        wxBitmap bitmap(delete_trash_xpm);
        return bitmap;
    }
    else if (name == wxT("copy.xpm"))
    {
        wxBitmap bitmap(copy_xpm);
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
////@end NyRemoteFilePanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon NyRemoteFilePanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin NyRemoteFilePanel icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end NyRemoteFilePanel icon retrieval
}
