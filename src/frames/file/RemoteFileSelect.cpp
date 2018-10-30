/////////////////////////////////////////////////////////////////////////////
// Name:        RemoteFileSelect.cpp
// Purpose:
// Author:
// Modified by:
// Created:     Tue 30 Oct 02:43:54 2018
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".

////@begin includes
#include "wx/imaglist.h"
////@end includes

#include "RemoteFileSelect.h"

////@begin XPM images
////@end XPM images


/*
 * RemoteFileSelect type definition
 */

IMPLEMENT_DYNAMIC_CLASS( RemoteFileSelect, wxDialog )


/*
 * RemoteFileSelect event table definition
 */

BEGIN_EVENT_TABLE( RemoteFileSelect, wxDialog )

////@begin remotefileselect event table entries
////@end remotefileselect event table entries

END_EVENT_TABLE()


/*
 * RemoteFileSelect constructors
 */

RemoteFileSelect::RemoteFileSelect()
{
    Init();
}

RemoteFileSelect::RemoteFileSelect( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
    this->Bind(wxEVT_CLOSE_WINDOW, &RemoteFileSelect::OnClose, this);
}

void RemoteFileSelect::OnClose(wxCloseEvent & event)
{
    get_path_cancellation.cancel();
    event.Skip();
}


/*
 * RemoteFileSelect creator
 */

bool RemoteFileSelect::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin remotefileselect creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end remotefileselect creation
    return true;
}


/*
 * RemoteFileSelect destructor
 */

RemoteFileSelect::~RemoteFileSelect()
{
////@begin remotefileselect destruction
////@end remotefileselect destruction
}


/*
 * Member initialisation
 */

void RemoteFileSelect::Init()
{
////@begin remotefileselect member initialisation
////@end remotefileselect member initialisation
}


/*
 * Control creation for RemoteFileSelect
 */

void RemoteFileSelect::CreateControls()
{
////@begin remotefileselect content construction
    RemoteFileSelect* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer1, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText2 = new wxStaticText( itemDialog1, wxID_STATIC, _("Current"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add(itemStaticText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl3 = new wxTextCtrl( itemDialog1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add(itemTextCtrl3, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton4 = new wxButton( itemDialog1, wxID_ANY, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add(itemButton4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTreeCtrl* itemTreeCtrl5 = new wxTreeCtrl( itemDialog1, wxID_ANY, wxDefaultPosition, wxSize(100, 100), wxTR_SINGLE );
    itemBoxSizer2->Add(itemTreeCtrl5, 1, wxGROW|wxALL, 5);

    wxStaticLine* itemStaticLine6 = new wxStaticLine( itemDialog1, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer2->Add(itemStaticLine6, 0, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer7 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer7, 0, wxGROW|wxALL, 5);
    wxButton* itemButton8 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer7->AddButton(itemButton8);

    wxButton* itemButton9 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer7->AddButton(itemButton9);

    itemStdDialogButtonSizer7->Realize();

////@end remotefileselect content construction
}


/*
 * Should we show tooltips?
 */

bool RemoteFileSelect::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap RemoteFileSelect::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin remotefileselect bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end remotefileselect bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon RemoteFileSelect::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin remotefileselect icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end remotefileselect icon retrieval
}
