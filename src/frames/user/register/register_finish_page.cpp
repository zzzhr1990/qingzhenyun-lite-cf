//
// Created by zzzhr on 2018/11/2.
//

#include "register_finish_page.h"

#include "../../../api_model/api_user_model.h"
#include "../changeusernamedialog.h"
/*
 * WizardPage2 type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage2, wxWizardPageSimple )


/*
 * WizardPage2 event table definition
 */

BEGIN_EVENT_TABLE( WizardPage2, wxWizardPageSimple )

////@begin WizardPage2 event table entries
////@end WizardPage2 event table entries

END_EVENT_TABLE()


/*
 * WizardPage2 constructors
 */

WizardPage2::WizardPage2()
{
    Init();
}

WizardPage2::WizardPage2( wxWizard* parent )
{
    Init();
    Create( parent );
}


/*
 * WizardPage2 creator
 */

bool WizardPage2::Create( wxWizard* parent )
{
////@begin WizardPage2 creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, NULL, NULL, wizardBitmap );

    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage2 creation
    return true;
}


/*
 * WizardPage2 destructor
 */

WizardPage2::~WizardPage2()
{
////@begin WizardPage2 destruction
////@end WizardPage2 destruction
}


/*
 * Member initialisation
 */

void WizardPage2::Init()
{
////@begin WizardPage2 member initialisation
////@end WizardPage2 member initialisation
}


/*
 * Control creation for WizardPage2
 */

void WizardPage2::CreateControls()
{
////@begin WizardPage2 content construction
    WizardPage2* itemWizardPageSimple1 = this;

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemWizardPageSimple1->SetSizer(itemBoxSizer4);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer4->Add(itemBoxSizer5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemWizardPageSimple1, wxID_STATIC, _("Registration Successful."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemStaticText6, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( itemWizardPageSimple1, wxID_STATIC, _("Thank you for registering. \nUse your account in compliance with local laws and regulations."), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
    itemBoxSizer5->Add(itemStaticText7, 0, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer5->Add(itemBoxSizer7, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText8 = new wxStaticText( itemWizardPageSimple1, wxID_STATIC, _("Your user name is"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer7->Add(itemStaticText8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    usernameTextCtrl = new wxTextCtrl( itemWizardPageSimple1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
    itemBoxSizer7->Add(usernameTextCtrl, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton11 = new wxButton( itemWizardPageSimple1, wxID_ANY, _("Change a new user name"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemButton11, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    this->Bind(wxEVT_WIZARD_PAGE_CHANGING,&WizardPage2::OnWizardPageChanging,this);
    itemButton11->Bind(wxEVT_BUTTON, &WizardPage2::ChangeNameBtnClicked,this);
////@end WizardPage2 content construction
}


/*
 * Should we show tooltips?
 */

bool WizardPage2::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap WizardPage2::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage2 bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage2 bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon WizardPage2::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage2 icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage2 icon retrieval
}

void WizardPage2::RefreshName() {
    auto info = qingzhen::api::api_user_model::instance().get_user_info();
    if(info.has_field(_XPLATSTR("name"))){
        usernameTextCtrl->SetValue(info.at(_XPLATSTR("name")).as_string());
        this->success = true;
    }
}

void WizardPage2::OnWizardPageChanging(wxWizardEvent &event) {

    if ( ! event.GetDirection() ){
        if(this->success){
            wxMessageBox(_("You already register an account, just close this window."),_("Register Finished"));
            event.Veto();
        }
    }
}

void WizardPage2::Terminate() {
    change_name_cancellation_token_source.cancel();
}

void WizardPage2::ChangeNameBtnClicked(wxCommandEvent &event) {
    auto* changeNameDlg = new ChangeUsernameDialog(this);
    if(wxID_OK == changeNameDlg->ShowModal()){
        utility::string_t name = changeNameDlg->GetUserNameInput();
        if(!name.empty()){
            this->change_name_cancellation_token_source.cancel();
            this->change_name_cancellation_token_source = pplx::cancellation_token_source();
            auto task = qingzhen::api::api_user_model::instance().change_username_and_get(this->change_name_cancellation_token_source, name);
            task.then([this](response_entity entity){
                if(!entity.is_cancelled() && entity.success)
                    this->CallAfter([this, entity]{
                        auto data = entity.result;
                        if(data.has_field(_XPLATSTR("name"))){
                            qingzhen::api::api_user_model::instance().set_user_info(data);
                            this->usernameTextCtrl->SetValue(data.at(_XPLATSTR("name")).as_string());
                        }
                    });
            });
        }
    }
}
