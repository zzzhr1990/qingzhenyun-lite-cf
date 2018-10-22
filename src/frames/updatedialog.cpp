/////////////////////////////////////////////////////////////////////////////
// Name:        updatedialog.cpp
// Purpose:
// Author:
// Modified by:
// Created:     Fri 19 Oct 15:25:41 2018
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".


////@begin includes
////@end includes

#include "updatedialog.h"
#include "../model/update_model.h"
////@begin XPM images
////@end XPM images


/*
 * UpdateDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( UpdateDialog, wxDialog )


/*
 * UpdateDialog event table definition
 */

BEGIN_EVENT_TABLE( UpdateDialog, wxDialog )

////@begin UpdateDialog event table entries
////@end UpdateDialog event table entries

END_EVENT_TABLE()


/*
 * UpdateDialog constructors
 */

UpdateDialog::UpdateDialog()
{
    Init();
}

UpdateDialog::UpdateDialog( wxWindow* parent, const web::json::value& updateData,wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, updateData, id, caption, pos, size, style);
}


/*
 * UpdateDialog creator
 */

bool UpdateDialog::Create( wxWindow* parent, const web::json::value& updateData,wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin UpdateDialog creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls(updateData);
    Centre();
////@end UpdateDialog creation
    return true;
}


/*
 * UpdateDialog destructor
 */

UpdateDialog::~UpdateDialog()
{
////@begin UpdateDialog destruction
////@end UpdateDialog destruction
}


/*
 * Member initialisation
 */

void UpdateDialog::Init()
{
////@begin UpdateDialog member initialisation
////@end UpdateDialog member initialisation
}


/*
 * Control creation for UpdateDialog
 */

void UpdateDialog::CreateControls(const web::json::value& updateData)
{
////@begin UpdateDialog content construction
    UpdateDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer3, 1, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("New version available"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl5 = new wxTextCtrl( itemDialog1, wxID_ANY,  updateData.at(_XPLATSTR("description")).as_string(), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
    itemBoxSizer3->Add(itemTextCtrl5, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer4, 0, wxGROW|wxALL, 5);

    auto versionStr = updateData.at(_XPLATSTR("displayVersion")).as_string();
    auto currentVersionStr = UpdateModel::Instance().GetDisplayVersion();
    auto currentVersionCompare = _("Current Version: %s | New Version: %s");

    wxStaticText* itemStaticText5 = new wxStaticText( itemDialog1, wxID_STATIC, wxString::Format(currentVersionCompare,currentVersionStr,versionStr), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemStaticText5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer1, 0, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer2 = new wxStdDialogButtonSizer;

    itemBoxSizer1->Add(itemStdDialogButtonSizer2, 0, wxALIGN_RIGHT|wxALL, 5);
    //wxButton* itemButton5 = new wxButton( itemDialog1, wxID_OK, _("&Ignore this update"), wxDefaultPosition, wxDefaultSize, 0 );
    //itemStdDialogButtonSizer2->AddButton(itemButton5);

    wxButton* itemButton3 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer2->AddButton(itemButton3);

    wxButton* itemButton4 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer2->AddButton(itemButton4);

    itemStdDialogButtonSizer2->Realize();

////@end UpdateDialog content construction
}


/*
 * Should we show tooltips?
 */

bool UpdateDialog::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap UpdateDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin UpdateDialog bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end UpdateDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon UpdateDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin UpdateDialog icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end UpdateDialog icon retrieval
}
