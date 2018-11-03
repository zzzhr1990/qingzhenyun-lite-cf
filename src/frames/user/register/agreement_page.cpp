//
// Created by zzzhr on 2018/11/2.
//

#include "agreement_page.h"

/*
 * WizardPage type definition
 */

IMPLEMENT_DYNAMIC_CLASS( WizardPage, wxWizardPageSimple )


/*
 * WizardPage event table definition
 */

BEGIN_EVENT_TABLE( WizardPage, wxWizardPageSimple )

////@begin WizardPage event table entries
////@end WizardPage event table entries

END_EVENT_TABLE()


/*
 * WizardPage constructors
 */

WizardPage::WizardPage()
{
    Init();
}

WizardPage::WizardPage( wxWizard* parent )
{
    Init();
    Create( parent );
}


/*
 * WizardPage creator
 */

bool WizardPage::Create( wxWizard* parent )
{
////@begin WizardPage creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxBitmap wizardBitmap(wxNullBitmap);
    wxWizardPageSimple::Create( parent, nullptr, nullptr, wizardBitmap );

    CreateControls();

    if (GetSizer())
        GetSizer()->Fit(this);
////@end WizardPage creation
    return true;
}


/*
 * WizardPage destructor
 */

WizardPage::~WizardPage()
{
////@begin WizardPage destruction
////@end WizardPage destruction
}


/*
 * Member initialisation
 */

void WizardPage::Init()
{
////@begin WizardPage member initialisation
////@end WizardPage member initialisation
}


/*
 * Control creation for WizardPage
 */

void WizardPage::CreateControls()
{
////@begin WizardPage content construction
    WizardPage* itemWizardPageSimple1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    itemWizardPageSimple1->SetSizer(itemBoxSizer1);

    wxStaticText* itemStaticText2 = new wxStaticText( itemWizardPageSimple1, wxID_STATIC, _("PLEASE READ THIS AGREEMENT"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add(itemStaticText2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl3 = new wxTextCtrl( itemWizardPageSimple1, wxID_ANY, _("Obey or die \nLoading agreements for your language..."), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
    itemBoxSizer1->Add(itemTextCtrl3, 1, wxGROW|wxALL, 5);

    agreeCheckBox = new wxCheckBox( itemWizardPageSimple1, wxID_ANY, _("I agree with this agreement"), wxDefaultPosition, wxDefaultSize, 0 );
    agreeCheckBox->SetValue(false);
    itemBoxSizer1->Add(agreeCheckBox, 0, wxALIGN_LEFT|wxALL, 5);


////@end WizardPage content construction
}


/*
 * Should we show tooltips?
 */

bool WizardPage::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap WizardPage::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin WizardPage bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end WizardPage bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon WizardPage::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin WizardPage icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end WizardPage icon retrieval
}

bool WizardPage::TransferDataFromWindow() {
    //return wxWizardPage::TransferDataFromWindow();
    /*
    auto fowardBtn = this->GetParent()->FindWindow(wxID_FORWARD);
    if(fowardBtn != nullptr){
        fowardBtn->Disable();
    }
     */
    if(agreeCheckBox->GetValue()){
        return true;
    }else{
        wxMessageBox(_("You must agree with the agreements before you register"),_("Please agree with the agreements"));
        return false;
    }

}
