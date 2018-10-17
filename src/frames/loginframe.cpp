/////////////////////////////////////////////////////////////////////////////
// Name:        loginframe.cpp
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     02/09/2018 17:17:00
// RCS-ID:      
// Copyright:   for free
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".


#include "loginframe.h"
#include "../model/user_model.h"
////@begin XPM images
////@end XPM images


/*
 * LoginFrame type definition
 */

IMPLEMENT_DYNAMIC_CLASS( LoginFrame, wxDialog )


/*
 * LoginFrame event table definition
 */

BEGIN_EVENT_TABLE( LoginFrame, wxDialog )

////@begin LoginFrame event table entries
////@end LoginFrame event table entries

END_EVENT_TABLE()


/*
 * LoginFrame constructors
 */

LoginFrame::LoginFrame()
{
    Init();
}

LoginFrame::LoginFrame( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * LoginFrame creator
 */

bool LoginFrame::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin LoginFrame creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end LoginFrame creation
    return true;
}


/*
 * LoginFrame destructor
 */

LoginFrame::~LoginFrame()
{
////@begin LoginFrame destruction
////@end LoginFrame destruction
}


/*
 * Member initialisation
 */

void LoginFrame::Init()
{
////@begin LoginFrame member initialisation
////@end LoginFrame member initialisation
}


/*
 * Control creation for LoginFrame
 */

void LoginFrame::CreateControls()
{    
////@begin LoginFrame content construction
    LoginFrame* itemDialog1 = this;
    //wxWindow &fr = *this;
    //wxWindow frr = fr;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer1, 1, wxGROW|wxALL, 5);

    //wxStaticText* itemStaticText2 = new wxStaticText( itemDialog1, wxID_STATIC, _("User Login"), wxDefaultPosition, wxDefaultSize, 0 );
    //itemBoxSizer1->Add(itemStaticText2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxNotebook* itemNotebook3 = new wxNotebook( itemDialog1, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    wxPanel* itemPanel1 = new wxPanel( itemNotebook3, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    itemPanel1->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer3);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer4, 1, wxGROW|wxALL, 5);
    wxFlexGridSizer* itemFlexGridSizer5 = new wxFlexGridSizer(2, 2, 0, 0);
    itemBoxSizer4->Add(itemFlexGridSizer5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxStaticText* itemStaticText6 = new wxStaticText( itemPanel1, wxID_STATIC, _("User/Phone"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer5->Add(itemStaticText6, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    inputTextCtrl = new wxTextCtrl( itemPanel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer5->Add(inputTextCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText8 = new wxStaticText( itemPanel1, wxID_STATIC, _("Password"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer5->Add(itemStaticText8, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    passwordTextCtrl = new wxTextCtrl( itemPanel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,wxTE_PASSWORD );

    itemFlexGridSizer5->Add(passwordTextCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer5->AddGrowableCol(1);

    itemNotebook3->AddPage(itemPanel1, _("Normal Login"));

    itemBoxSizer1->Add(itemNotebook3, 1, wxGROW|wxALL, 5);

    tipsText = new wxStaticText( itemDialog1, wxID_STATIC, _("See our agreememts"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add(tipsText, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer1->Add(itemBoxSizer5, 0, wxGROW|wxALL, 5);

    itemBoxSizer5->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer7 = new wxStdDialogButtonSizer;

    itemBoxSizer5->Add(itemStdDialogButtonSizer7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxButton* itemButton8 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer7->AddButton(itemButton8);

    wxButton* itemButton9 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer7->AddButton(itemButton9);

    itemStdDialogButtonSizer7->Realize();

////@end LoginFrame content construction
}


/*
 * Should we show tooltips?
 */

bool LoginFrame::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap LoginFrame::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin LoginFrame bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end LoginFrame bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon LoginFrame::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin LoginFrame icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end LoginFrame icon retrieval
}

wxString LoginFrame::getUserInput() {
    return inputTextCtrl->GetValue();
}

wxString LoginFrame::getUserPassword() {
    return passwordTextCtrl->GetValue();
}

void LoginFrame::SetTips(const wxString &str) {
    tipsText->SetLabel(str);
}
