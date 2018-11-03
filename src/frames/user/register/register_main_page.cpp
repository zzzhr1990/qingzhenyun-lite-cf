//
// Created by zzzhr on 2018/11/2.
//

#include "register_main_page.h"
#include "./userregisterdialog.h"
#include "../../../common/common_constants_wx.h"
#include "../../../api_model/api_user_model.h"
#include "../../../common/common_util.hpp"

/*
 * WizardPage1 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage1, wxWizardPageSimple )


/*
 * WizardPage1 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage1, wxWizardPageSimple )

////@begin WizardPage1 event table entries
////@end WizardPage1 event table entries

END_EVENT_TABLE()


/*
 * WizardPage1 constructors
 */

WizardPage1::WizardPage1()
{
    Init();
}

WizardPage1::WizardPage1( wxWizard* parent )
{
    Init();
    Create( parent );
}


/*
 * WizardPage1 creator
 */

bool WizardPage1::Create( wxWizard* parent )
{
////@begin WizardPage1 creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxWizardPageSimple::Create( parent, nullptr, nullptr, wxNullBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage1 creation
    return true;
}


/*
 * WizardPage1 destructor
 */

WizardPage1::~WizardPage1()
{
////@begin WizardPage1 destruction
////@end WizardPage1 destruction
}


/*
 * Member initialisation
 */

void WizardPage1::Init()
{
////@begin WizardPage1 member initialisation
////@end WizardPage1 member initialisation
}


/*
 * Control creation for WizardPage1
 */

void WizardPage1::CreateControls()
{
////@begin WizardPage1 content construction
    WizardPage1* itemWizardPageSimple1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    itemWizardPageSimple1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer3, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer4 = new wxFlexGridSizer(4, 2, 0, 0);
    itemBoxSizer3->Add(itemFlexGridSizer4, 1, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText5 = new wxStaticText( itemWizardPageSimple1, wxID_STATIC, _("Phone"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    itemFlexGridSizer4->Add(itemBoxSizer6, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    messageCountryCodeSelection = new wxChoice( itemWizardPageSimple1, wxID_ANY, wxDefaultPosition, wxSize(100, -1), qingzhen::app::common_constants::get_country_code_array(), 0 );
    itemBoxSizer6->Add(messageCountryCodeSelection, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    messagePhoneInput = new wxTextCtrl( itemWizardPageSimple1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(messagePhoneInput, 1, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM, 5);

    wxStaticText* itemStaticText9 = new wxStaticText( itemWizardPageSimple1, wxID_STATIC, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText9, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    sendMessageButton = new wxButton( itemWizardPageSimple1, wxID_ANY, _("Click to send message"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(sendMessageButton, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText11 = new wxStaticText( itemWizardPageSimple1, wxID_STATIC, _("Code"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText11, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    messageCodeInput = new wxTextCtrl( itemWizardPageSimple1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(messageCodeInput, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText12 = new wxStaticText( itemWizardPageSimple1, wxID_STATIC, _("Password"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    userPasswordInput = new wxTextCtrl( itemWizardPageSimple1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
    itemFlexGridSizer4->Add(userPasswordInput, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer4->AddGrowableCol(1);

    wxStaticText* itemStaticText13 = new wxStaticText( itemWizardPageSimple1, wxID_STATIC, _("We use SSL to protect your information"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    itemBoxSizer3->Add(itemStaticText13, 0, wxGROW|wxALL, 5);

    this->Bind(wxEVT_WIZARD_PAGE_CHANGING,&WizardPage1::OnWizardPageChanging,this);
    this->ResetTimerClick();
    sendMessageButton->Bind(wxEVT_BUTTON, &WizardPage1::SendMessageButtonClicked, this);
////@end WizardPage1 content construction
}


/*
 * Should we show tooltips?
 */

bool WizardPage1::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap WizardPage1::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage1 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage1 bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon WizardPage1::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage1 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage1 icon retrieval
}



void WizardPage1::SendMessageButtonClicked(wxCommandEvent &event) {
    utility::string_t countryCode = qingzhen::app::common_constants::get_country_code(this->messageCountryCodeSelection);
    auto phone = messagePhoneInput->GetValue();
    if(phone.IsEmpty() || (!phone.IsNumber())){
        wxMessageBox(_("Phone must be number"),_("Validate error"),wxICON_WARNING | wxOK, this);
        return;
    }
    //auto phone = this->
    this->SendTextMessage();
    utility::string_t phoneToSend = phone;
    send_message_cancellation_token_source.cancel();
    send_message_cancellation_token_source = pplx::cancellation_token_source();
    qingzhen::api::api_user_model::instance().send_register_message(countryCode, phoneToSend, send_message_cancellation_token_source)
            .then([this](response_entity r){
                if(!r.success){
                    this->CallAfter([this,r](){
                        timer.Expire();
                        wxMessageBox(wxString::Format(_("Send message failed.\n%s"),r.message),_("Send text message error"),wxICON_ERROR | wxOK);
                        this->ResetTimerClick();
                    });
                }else{
                    this->phoneInfo = r.result.as_string();
                }
            });
    //sendMessageButton->SetLabel()
}

void WizardPage1::ResetTimerClick() {
    timer.Expire();
    sendMessageButton->Enable();
    sendMessageButton->SetLabel(_("Click to send message"));
}

void WizardPage1::SendTextMessage() {
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

void WizardPage1::OnWizardPageChanging(wxWizardEvent &event) {
    if(success){
        return;
    }
    if ( event.GetDirection() ){
        auto code = messageCodeInput->GetValue();
        auto password = userPasswordInput->GetValue();

        if(this->phoneInfo.empty()){
            wxMessageBox(_("Please click send message."),_("Cannot continue"),wxICON_WARNING | wxOK,this);
            event.Veto();
            return;
        }
        if(password.empty()){
            wxMessageBox(_("Please fill password."),_("Cannot continue"),wxICON_WARNING | wxOK,this);
            event.Veto();
            return;
        }
        if(code.empty()){
            wxMessageBox(_("Please click send message and fill code."),_("Cannot continue"),wxICON_WARNING | wxOK,this);
            event.Veto();
            return;
        }


        //Send Messages...
        auto *userLoginDialog = (UserRegisterDialog*)this->GetParent();
        userLoginDialog->LockForward();
        event.Veto();
        this->DoRegister(code,password);
        return;
    }
}

void WizardPage1::DoRegister(wxString &code,wxString &password) {
    send_message_cancellation_token_source.cancel();
    send_message_cancellation_token_source = pplx::cancellation_token_source();
    // send message
    utility::string_t c = code;
    utility::string_t p = password;
    auto task = qingzhen::api::api_user_model::instance().register_by_message(this->phoneInfo, c,p,send_message_cancellation_token_source);
    task.then([this](response_entity entity){
        if(!entity.is_cancelled()){
            this->CallAfter([this, entity](){
                if(entity.success){
                    // Goto success..
                    timer.Expire();
                    auto *userLoginDialog = (UserRegisterDialog*)this->GetParent();
                    userLoginDialog->LockForward(false);
                    userLoginDialog->LockBack(true);
                    userLoginDialog->OnRegisterSuccess();
                    userLoginDialog->GotoLastPage();
                    qingzhen::api::api_user_model::instance().set_user_info(entity.result);
                    userLoginDialog->RefreshName();
                    this->success = true;
                }else{
                    auto *userLoginDialog = (UserRegisterDialog*)this->GetParent();
                    userLoginDialog->LockForward(false);
                    wxMessageBox(wxString::Format(_("Register failed\n%s"),entity.message),_("Register Failed"),wxICON_ERROR | wxOK,this);
                }
            });
        }
    });
}

void WizardPage1::Terminate() {
    send_message_cancellation_token_source.cancel();
}

