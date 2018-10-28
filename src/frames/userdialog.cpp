/////////////////////////////////////////////////////////////////////////////
// Name:        userdialog.cpp
// Purpose:
// Author:
// Modified by:
// Created:     Fri 19 Oct 15:02:06 2018
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".

////@begin includes
#include "wx/imaglist.h"
////@end includes

#include "userdialog.h"
#include "../util/common_util.h"
#include "../model/user_model.h"
#include "../api_model/api_user_model.h"
////@begin XPM images
////@end XPM images


/*
 * UserDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( UserDialog, wxDialog )


/*
 * UserDialog event table definition
 */

BEGIN_EVENT_TABLE( UserDialog, wxDialog )

////@begin UserDialog event table entries
////@end UserDialog event table entries

END_EVENT_TABLE()


/*
 * UserDialog constructors
 */

UserDialog::UserDialog()
{
    Init();
}

UserDialog::UserDialog( wxWindow* parent, const web::json::value & userData,wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent,userData, id, caption, pos, size, style);
	this->Bind(wxEVT_CLOSE_WINDOW, &UserDialog::OnClose, this);
}


/*
 * UserDialog creator
 */

bool UserDialog::Create( wxWindow* parent,const web::json::value & userData, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin UserDialog creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls(userData);
    Centre();
////@end UserDialog creation
    return true;
}


/*
 * UserDialog destructor
 */

UserDialog::~UserDialog()
{
////@begin UserDialog destruction
////@end UserDialog destruction
}


/*
 * Member initialisation
 */

void UserDialog::Init()
{
////@begin UserDialog member initialisation
////@end UserDialog member initialisation
}


/*
 * Control creation for UserDialog
 */

void UserDialog::CreateControls(const web::json::value & userData)
{
////@begin UserDialog content construction
    UserDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer1);

    wxNotebook* itemNotebook2 = new wxNotebook( itemDialog1, ID_LOGIN_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    wxPanel* itemPanel3 = new wxPanel( itemNotebook2, ID_MY_ACCOUNT_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    itemPanel3->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
    itemPanel3->SetSizer(itemBoxSizer4);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer4->Add(itemBoxSizer5, 1, wxGROW|wxALL, 5);
    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer5->Add(itemBoxSizer6, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxFlexGridSizer* itemFlexGridSizer7 = new wxFlexGridSizer(2, 2, 0, 0);
    itemBoxSizer6->Add(itemFlexGridSizer7, 1, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText8 = new wxStaticText( itemPanel3, wxID_STATIC, _("User name"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer7->Add(itemStaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer7->Add(itemBoxSizer3, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxTextCtrl* itemTextCtrl4 = new wxTextCtrl( itemPanel3, ID_TEXTCTRL, userData.at(_XPLATSTR("name")).as_string(), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemTextCtrl4, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton3 = new wxButton( itemPanel3, wxID_ANY, _("Change"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemButton3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText10 = new wxStaticText( itemPanel3, wxID_STATIC, _("Extra"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer7->Add(itemStaticText10, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText5 = new wxStaticText( itemPanel3, CHANGE_USER_ID, _("No more information"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer7->Add(itemStaticText5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer7->AddGrowableCol(1);

    itemNotebook2->AddPage(itemPanel3, _("My account"));

    wxPanel* itemPanel12 = new wxPanel( itemNotebook2, ID_QUOTA_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    itemPanel12->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxBoxSizer* itemBoxSizer13 = new wxBoxSizer(wxVERTICAL);
    itemPanel12->SetSizer(itemBoxSizer13);

    wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer13->Add(itemBoxSizer14, 1, wxGROW|wxALL, 5);
    wxBoxSizer* itemBoxSizer15 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer14->Add(itemBoxSizer15, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxFlexGridSizer* itemFlexGridSizer16 = new wxFlexGridSizer(3, 2, 0, 0);
    itemBoxSizer15->Add(itemFlexGridSizer16, 1, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText17 = new wxStaticText( itemPanel12, wxID_STATIC, _("Storage"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer16->Add(itemStaticText17, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemFlexGridSizer16->Add(itemBoxSizer2, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    auto usedSize = userData.at(_XPLATSTR("spaceUsed")).as_number().to_int64();
    auto spaceCapacity = userData.at(_XPLATSTR("spaceCapacity")).as_number().to_int64();

    auto usedPercent = 0;
    if(spaceCapacity > 0){
        usedPercent = static_cast<int>(usedSize * 100 / spaceCapacity);
        if(usedPercent > 100){
            usedPercent = 100;
        }
    }
    auto text = wxString::Format(wxT("%s/%s (%d%%)"),ConvertSizeToDisplay(usedSize),ConvertSizeToDisplay(spaceCapacity),usedPercent);
    wxGauge* itemGauge3 = new wxGauge( itemPanel12, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
    itemGauge3->SetValue(usedPercent);
    itemBoxSizer2->Add(itemGauge3, 0, wxGROW|wxALL, 5);


    wxStaticText* itemStaticText4 = new wxStaticText( itemPanel12, wxID_STATIC, text, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    itemBoxSizer2->Add(itemStaticText4, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText19 = new wxStaticText( itemPanel12, wxID_STATIC, _("Traffic"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer16->Add(itemStaticText19, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxVERTICAL);
    wxStaticLine* itemStaticLineLogoff = new wxStaticLine( itemPanel3, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer6->Add(itemStaticLineLogoff, 0, wxGROW|wxALL, 5);

    wxButton* logoutButton = new wxButton( itemPanel3, wxID_ANY, _("Logout / Log in use another account"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(logoutButton, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    logoutButton->Bind(wxEVT_BUTTON, &UserDialog::LogoutBtnClicked, this);

    //itemButton2->SetFocus();
    itemFlexGridSizer16->Add(itemBoxSizer7, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxGauge* itemGauge8 = new wxGauge( itemPanel12, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
    itemGauge8->SetValue(1);
    itemBoxSizer7->Add(itemGauge8, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText9 = new wxStaticText( itemPanel12, wxID_STATIC, _("0.00GB/0.00GB"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    itemBoxSizer7->Add(itemStaticText9, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText21 = new wxStaticText( itemPanel12, wxID_STATIC, _("Offline"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer16->Add(itemStaticText21, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer(wxVERTICAL);
    itemFlexGridSizer16->Add(itemBoxSizer10, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxGauge* itemGauge11 = new wxGauge( itemPanel12, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
    itemGauge11->SetValue(1);
    itemBoxSizer10->Add(itemGauge11, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText12 = new wxStaticText( itemPanel12, wxID_STATIC, _("0.00GB/0.00GB"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    itemBoxSizer10->Add(itemStaticText12, 0, wxGROW|wxALL, 5);

    itemFlexGridSizer16->AddGrowableCol(1);

    wxButton* itemButton1 = new wxButton( itemPanel12, wxID_STATIC, _("Extend"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer15->Add(itemButton1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemNotebook2->AddPage(itemPanel12, _("Quota"));

    wxPanel* itemPanel13 = new wxPanel( itemNotebook2, ID_SECURITY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    itemPanel13->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxBoxSizer* itemBoxSizer16 = new wxBoxSizer(wxVERTICAL);
    itemPanel13->SetSizer(itemBoxSizer16);

    wxBoxSizer* itemBoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer16->Add(itemBoxSizer17, 1, wxGROW|wxALL, 5);
    wxBoxSizer* itemBoxSizer18 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer17->Add(itemBoxSizer18, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxButton* itemButton19 = new wxButton( itemPanel13, wxID_STATIC, _("Change Login Phone"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer18->Add(itemButton19, 0, wxGROW|wxALL, 5);

    wxButton* itemButton20 = new wxButton( itemPanel13, wxID_STATIC, _("Change Password"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer18->Add(itemButton20, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText22 = new wxStaticText( itemPanel13, wxID_STATIC, _("Dangerous Area"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer18->Add(itemStaticText22, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticLine* itemStaticLine23 = new wxStaticLine( itemPanel13, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer18->Add(itemStaticLine23, 0, wxGROW|wxALL, 5);

    wxButton* itemButton24 = new wxButton( itemPanel13, wxID_ANY, _("Erase My Account"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer18->Add(itemButton24, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemNotebook2->AddPage(itemPanel13, _("Security"));

    itemBoxSizer1->Add(itemNotebook2, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer24 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer1->Add(itemBoxSizer24, 0, wxGROW|wxALL, 5);

    /*
    wxStdDialogButtonSizer* itemStdDialogButtonSizer25 = new wxStdDialogButtonSizer;

    itemBoxSizer24->Add(itemStdDialogButtonSizer25, 0, wxALIGN_RIGHT|wxALL, 5);
    wxButton* itemButton26 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer25->AddButton(itemButton26);

    wxButton* itemButton27 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer25->AddButton(itemButton27);

    itemStdDialogButtonSizer25->Realize();
     */

////@end UserDialog content construction
}


/*
 * Should we show tooltips?
 */

bool UserDialog::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap UserDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin UserDialog bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end UserDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon UserDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin UserDialog icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end UserDialog icon retrieval
}

void UserDialog::LogoutBtnClicked(wxCommandEvent &event) {
    //this->CallAfter()
    //UserModel::Instance().Logout();
	logout_cancel_source.cancel();
    qingzhen::api::api_user_model user_model = qingzhen::api::api_user_model::instance();
    std::function<void(response_entity)> task2 = [this](response_entity entity)->void {
        this->CallAfter([this,entity](){
            if(entity.success || entity.code == _XPLATSTR("CREDENTIALS_REQUIRED")){
                this->continueLogin = true;
                this->Close();
            }
        });
    };
	logout_cancel_source = pplx::cancellation_token_source();
    user_model.logout(task2, logout_cancel_source);
}

void UserDialog::OnClose(wxCloseEvent & event)
{
	logout_cancel_source.cancel();
	event.Skip();

}
