/////////////////////////////////////////////////////////////////////////////
// Name:        userlogindialog.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     16/10/2018 22:40:32
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 16/10/2018 22:40:32

// For compilers that support precompilation, includes "wx/wx.h".


////@begin includes
#include "wx/imaglist.h"
////@end includes

#include "userlogindialog.h"
#include "../api_model/api_user_model.h"
#include "../common/common_util.hpp"
////@begin XPM images
////@end XPM images


/*
 * UserLoginDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( UserLoginDialog, wxDialog )


/*
 * UserLoginDialog event table definition
 */

BEGIN_EVENT_TABLE( UserLoginDialog, wxDialog )

////@begin UserLoginDialog event table entries
////@end UserLoginDialog event table entries

END_EVENT_TABLE()


/*
 * UserLoginDialog constructors
 */

UserLoginDialog::UserLoginDialog()
{
	Init();
}

UserLoginDialog::UserLoginDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
	Init();
	Create(parent, id, caption, pos, size, style);
}


/*
 * UserLoginDialog creator
 */

bool UserLoginDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin UserLoginDialog creation
	SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
	wxDialog::Create( parent, id, caption, pos, size, style );

	CreateControls();
	Centre();
////@end UserLoginDialog creation
	return true;
}


/*
 * UserLoginDialog destructor
 */

UserLoginDialog::~UserLoginDialog()
{
////@begin UserLoginDialog destruction
timer.Expire();
////@end UserLoginDialog destruction
}


/*
 * Member initialisation
 */

void UserLoginDialog::Init()
{
////@begin UserLoginDialog member initialisation
////@end UserLoginDialog member initialisation
}


/*
 * Control creation for UserLoginDialog
 */

void UserLoginDialog::CreateControls()
{
////@begin UserLoginDialog content construction
    UserLoginDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    itemNotebook = new wxNotebook( itemDialog1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    wxPanel* itemPanel1 = new wxPanel( itemNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    itemPanel1->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer1);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer1->Add(itemBoxSizer4, 1, wxGROW|wxALL, 5);
    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer4->Add(itemBoxSizer5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxFlexGridSizer* itemFlexGridSizer6 = new wxFlexGridSizer(2, 2, 0, 0);
    itemBoxSizer5->Add(itemFlexGridSizer6, 1, wxGROW|wxALL, 5);
    wxStaticText* userInputStaticText = new wxStaticText( itemPanel1, wxID_STATIC, _("Phone/User"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6->Add(userInputStaticText, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer6->Add(itemBoxSizer8, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);
    //wxArrayString itemChoice9Strings;

    passwordCountryCodeSelection = new wxChoice( itemPanel1, wxID_ANY, wxDefaultPosition, wxSize(140, -1), this->GetCountryCodeArray(), 0 );
    //itemChoice9->SetStringSelection(_("Auto(PRC, +86)"));
    passwordCountryCodeSelection->SetSelection(0);
    itemBoxSizer8->Add(passwordCountryCodeSelection, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    userInput = new wxTextCtrl( itemPanel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(userInput, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5);

    wxStaticText* itemStaticText11 = new wxStaticText( itemPanel1, wxID_STATIC, _("Password"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer6->Add(itemStaticText11, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    userPasswordInput = new wxTextCtrl( itemPanel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
    itemFlexGridSizer6->Add(userPasswordInput, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer6->AddGrowableCol(1);

    wxStaticText* itemStaticText13 = new wxStaticText( itemPanel1, wxID_STATIC, _("We use SSL to protect your information"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    itemBoxSizer5->Add(itemStaticText13, 0, wxGROW|wxALL, 5);

    itemNotebook->AddPage(itemPanel1, _("Login By Password"));

    wxPanel* itemPanel2 = new wxPanel( itemNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    itemPanel2->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxBoxSizer* itemBoxSizer14 = new wxBoxSizer(wxVERTICAL);
    itemPanel2->SetSizer(itemBoxSizer14);

    wxBoxSizer* itemBoxSizer15 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer14->Add(itemBoxSizer15, 1, wxGROW|wxALL, 5);
    wxBoxSizer* itemBoxSizer16 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer15->Add(itemBoxSizer16, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxFlexGridSizer* itemFlexGridSizer17 = new wxFlexGridSizer(3, 2, 0, 0);
    itemBoxSizer16->Add(itemFlexGridSizer17, 1, wxGROW|wxALL, 5);
    wxStaticText* itemStaticText18 = new wxStaticText( itemPanel2, wxID_STATIC, _("Phone"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer17->Add(itemStaticText18, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer19 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer17->Add(itemBoxSizer19, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    messageCountryCodeSelection = new wxChoice( itemPanel2, wxID_ANY, wxDefaultPosition, wxSize(100, -1), this->GetCountryCodeArray(), 0 );
    messageCountryCodeSelection->SetSelection(0);
    itemBoxSizer19->Add(messageCountryCodeSelection, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    messagePhoneInput = new wxTextCtrl( itemPanel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer19->Add(messagePhoneInput, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5);

    wxStaticText* itemStaticText22 = new wxStaticText( itemPanel2, wxID_STATIC, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer17->Add(itemStaticText22, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    sendMessageButton = new wxButton( itemPanel2, wxID_ANY, _("Click to send message"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer17->Add(sendMessageButton, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText24 = new wxStaticText( itemPanel2, wxID_STATIC, _("Code"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer17->Add(itemStaticText24, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    messageCodeInput = new wxTextCtrl( itemPanel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer17->Add(messageCodeInput, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer17->AddGrowableCol(1);

    wxStaticText* itemStaticText26 = new wxStaticText( itemPanel2, wxID_STATIC, _("We use SSL to protect your information"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    itemBoxSizer16->Add(itemStaticText26, 0, wxGROW|wxALL, 5);

    itemNotebook->AddPage(itemPanel2, _("Login By Text Message"));

    itemBoxSizer2->Add(itemNotebook, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("No Account? click here to register one"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_RIGHT|wxALL, 5);

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer7, 0, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer8 = new wxStdDialogButtonSizer;

    itemBoxSizer7->Add(itemStdDialogButtonSizer8, 0, wxALIGN_RIGHT|wxALL, 5);
    wxButton* itemButton9 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer8->AddButton(itemButton9);

    wxButton* itemButton10 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer8->AddButton(itemButton10);

    itemStdDialogButtonSizer8->Realize();
    
    // Event Listeners
    this->ResetTimerClick();
    sendMessageButton->Bind(wxEVT_BUTTON, &UserLoginDialog::SendMessageButtonClicked, this);

    // Connect events and objects
    //itemStaticText4->Connect(wxID_STATIC, wxEVT_LEFT_UP, wxMouseEventHandler(UserLoginDialog::OnLeftUp), NULL, this);
////@end UserLoginDialog content construction
}


/*
 * Should we show tooltips?
 */

bool UserLoginDialog::ShowToolTips()
{
	return true;
}

/*
 * Get bitmap resources
 */

wxBitmap UserLoginDialog::GetBitmapResource( const wxString& name )
{
	// Bitmap retrieval
////@begin UserLoginDialog bitmap retrieval
	wxUnusedVar(name);
	return wxNullBitmap;
////@end UserLoginDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon UserLoginDialog::GetIconResource( const wxString& name )
{
	// Icon retrieval
////@begin UserLoginDialog icon retrieval
	wxUnusedVar(name);
	return wxNullIcon;
////@end UserLoginDialog icon retrieval
}


/*
 * wxEVT_LEFT_UP event handler for wxID_STATIC
 */

void UserLoginDialog::OnLeftUp( wxMouseEvent& event )
{
////@begin wxEVT_LEFT_UP event handler for wxID_STATIC in UserLoginDialog.
	// Before editing this code, remove the block markers.
	event.Skip();
////@end wxEVT_LEFT_UP event handler for wxID_STATIC in UserLoginDialog.
}

void UserLoginDialog::LogoutBtnClicked(wxCommandEvent &event) {

}

int UserLoginDialog::GetNoteCurrentSelection() {
    return itemNotebook->GetSelection();
}

wxString UserLoginDialog::GetUserInput() {
    return userInput->GetValue();
}

wxString UserLoginDialog::GetMessagePhoneInput() {
    return messagePhoneInput->GetValue();
}

wxString UserLoginDialog::GetPasswordCountryCode() {
    return GetCountryCode(this->passwordCountryCodeSelection);
}

void UserLoginDialog::FillCountryCodeInput(wxChoice *input) {
    if(input != nullptr){
        if(input->GetCount() > 0){
            input->Clear();
        }
        for(auto &p : DEFAULT_COUNTRY_CODE_PAIR){
            input->Append(p.first);
        }
    }
}

wxArrayString UserLoginDialog::GetCountryCodeArray() {
    wxArrayString arrayString;
    for(auto &p : DEFAULT_COUNTRY_CODE_PAIR){
        arrayString.Add(p.first);
    }
    return arrayString;
}

wxString UserLoginDialog::GetUsePassword() {
    return userPasswordInput->GetValue();
}

wxString UserLoginDialog::GetCountryCode(wxChoice *choice) {
    if(choice == nullptr){
        return wxString();
    }
    auto select = choice->GetSelection();
    if(select < (7 - 1)){
        return wxString();
    }
    return DEFAULT_COUNTRY_CODE_PAIR[select].second;
}

void UserLoginDialog::ResetTimerClick() {
    timer.Expire();
    sendMessageButton->Enable();
    sendMessageButton->SetLabel(_("Click to send message"));
}

void UserLoginDialog::SendTextMessage() {
    sendMessageButton->Enable(false);
    this->last_send_message_time = qingzhen::util::get_current_linux_timestamp();
    auto tick_fun = [this](){
        auto current = qingzhen::util::get_current_linux_timestamp();
        auto time_diff = last_send_message_time + 120 - current;
        if(time_diff < 0){
            this->CallAfter([this](){this->ResetTimerClick();});
        }else{
            this->CallAfter([this, time_diff]()-> void {
                int rest = static_cast<int>(time_diff);
                sendMessageButton->SetLabel(wxString::Format(_("Resend text message in %d seconds"),rest));
            });
        }
    };
    timer.StartTimer(500, tick_fun, true);
    //sendMessageButton->SetLabel()
}

void UserLoginDialog::SendMessageButtonClicked(wxCommandEvent &event) {
    utility::string_t countryCode = this->GetMessageCountryCode();
    auto phone = this->GetMessagePhoneInput();
    if(phone.IsEmpty() || (!phone.IsNumber())){
        wxMessageBox(_("Phone must be number"),_("Validate error"));
        return;
    }
    //auto phone = this->
    this->SendTextMessage();
    utility::string_t phoneToSend = phone;
    qingzhen::api::api_user_model::instance().send_login_message(countryCode, phoneToSend)
    .then([this](response_entity r){
        if(!r.success){
            this->CallAfter([this](){
                wxMessageBox(_("Send message failed."),_("Send text message error"));
                this->ResetTimerClick();
            });
        }else{
            this->phoneInfo = r.result.as_string();
        }
    });
}

wxString UserLoginDialog::GetMessageCountryCode() {
    return this->GetCountryCode(this->messageCountryCodeSelection);
}

wxString UserLoginDialog::GetMessageCodeInput() {
    return messageCodeInput->GetValue();
}

wxString UserLoginDialog::GetPhoneInfo() {
    return this->phoneInfo;
}


