////@begin includes
////@end includes

#include "userregisterdialog.h"
#include "./agreement_page.h"
#include "./register_main_page.h"
#include "./register_finish_page.h"
#include "../../../common/common_constants_wx.h"
////@begin XPM images
////@end XPM images


/*
 * UserRegisterDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( UserRegisterDialog, wxWizard )


/*
 * UserRegisterDialog event table definition
 */

BEGIN_EVENT_TABLE( UserRegisterDialog, wxWizard )

////@begin UserRegisterDialog event table entries
////@end UserRegisterDialog event table entries

END_EVENT_TABLE()


/*
 * UserRegisterDialog constructors
 */

UserRegisterDialog::UserRegisterDialog()
{
    //Init();
}

UserRegisterDialog::UserRegisterDialog( wxWindow* parent, wxWindowID id, const wxPoint& pos )
{
    //Init();
    Create(parent, id, pos);
}


/*
 * UserRegisterDialog creator
 */

bool UserRegisterDialog::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos )
{
////@begin UserRegisterDialog creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS|wxWIZARD_EX_HELPBUTTON);
    wxWizard::Create( parent, id, _("UserRegisterDialog"), wxNullBitmap, pos, wxDEFAULT_DIALOG_STYLE|wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX );
    CreateControls();
////@end UserRegisterDialog creation
    return true;
}


/*
 * UserRegisterDialog destructor
 */

UserRegisterDialog::~UserRegisterDialog()
{
////@begin UserRegisterDialog destruction
////@end UserRegisterDialog destruction
}


/*
 * Member initialisation
 */

/*
void UserRegisterDialog::Init()
{
////@begin UserRegisterDialog member initialisation
////@end UserRegisterDialog member initialisation
}

*/

/*
 * Control creation for UserRegisterDialog
 */

void UserRegisterDialog::Terminate() {
    auto mainDlPage = (WizardPage1 *)this->mainPage;
    mainDlPage->Terminate();

    auto finDlPage = (WizardPage2 *)this->lastPage;
    finDlPage->Terminate();
}


void UserRegisterDialog::CreateControls()
{
////@begin UserRegisterDialog content construction
    UserRegisterDialog* itemWizard1 = this;

    WizardPage* itemWizardPageSimple1 = new WizardPage( itemWizard1 );
    firstPage = itemWizardPageSimple1;
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple1);


    this->GetPageAreaSizer()->SetMinSize(540,360);
    auto * registerPage = new WizardPage1( itemWizard1 );
    this->mainPage = registerPage;
    itemWizardPageSimple1->Chain(registerPage);
    this->GetPageAreaSizer()->Add(registerPage);
    auto * finishPage = new WizardPage2(itemWizard1);
    registerPage->Chain(finishPage);
    this->GetPageAreaSizer()->Add(finishPage);
    lastPage = finishPage;
    //GetPageAreaSizer()->Add(firstPage);
    //wxWizardPageSimple::Chain(itemWizard1,itemWizardPageSimple1);
    /*


    WizardPage1* itemWizardPageSimple1 = new WizardPage1( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple1);

    WizardPage2* itemWizardPageSimple1 = new WizardPage2( itemWizard1 );
    itemWizard1->GetPageAreaSizer()->Add(itemWizardPageSimple1);

    wxWizardPageSimple* lastPage = NULL;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple1);
    lastPage = itemWizardPageSimple1;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple1);
    lastPage = itemWizardPageSimple1;
    if (lastPage)
        wxWizardPageSimple::Chain(lastPage, itemWizardPageSimple1);
    lastPage = itemWizardPageSimple1;
     */
////@end UserRegisterDialog content construction
}


/*
 * Runs the wizard.
 */



/*
 * Should we show tooltips?
 */

bool UserRegisterDialog::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap UserRegisterDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin UserRegisterDialog bitmap retrieval
    wxUnusedVar(name);
    if (name == wxT("wizard.png"))
    {
        wxBitmap bitmap(wxT("wizard.png"), wxBITMAP_TYPE_PNG);
        return bitmap;
    }
    return wxNullBitmap;
////@end UserRegisterDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon UserRegisterDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin UserRegisterDialog icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end UserRegisterDialog icon retrieval
}

bool UserRegisterDialog::Run()
{
    this->RunWizard(firstPage);
    return false;
}

void UserRegisterDialog::LockForward(bool lock) {
    auto forwardBtn = this->FindWindow(wxID_FORWARD);
    if(forwardBtn != nullptr){
        if(lock){
            forwardBtn->Disable();
        } else{
            forwardBtn->Enable();
        }
    }
}

void UserRegisterDialog::LockBack(bool lock) {
    auto forwardBtn = this->FindWindow(wxID_BACKWARD);
    if(forwardBtn != nullptr){
        if(lock){
            forwardBtn->Disable();
        } else{
            forwardBtn->Enable();
        }
    }
}

bool UserRegisterDialog::GotoLastPage() {
    this->ShowPage(lastPage, false);
    return true;
}

void UserRegisterDialog::RefreshName() {
    auto p = (WizardPage2 *)lastPage;
    p->RefreshName();
}

void UserRegisterDialog::OnRegisterSuccess() {
    success = true;
}

bool UserRegisterDialog::IsRegisterSuccess() {
    return success;
}


