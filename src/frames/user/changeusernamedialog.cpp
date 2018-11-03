//
// Created by zzzhr on 2018/11/3.
//

////@begin includes
////@end includes

#include "changeusernamedialog.h"

////@begin XPM images
////@end XPM images


/*
 * ChangeUsernameDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( ChangeUsernameDialog, wxDialog )


/*
 * ChangeUsernameDialog event table definition
 */

BEGIN_EVENT_TABLE( ChangeUsernameDialog, wxDialog )

////@begin ChangeUsernameDialog event table entries
////@end ChangeUsernameDialog event table entries

END_EVENT_TABLE()


/*
 * ChangeUsernameDialog constructors
 */

ChangeUsernameDialog::ChangeUsernameDialog()
{
    Init();
}

ChangeUsernameDialog::ChangeUsernameDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * ChangeUsernameDialog creator
 */

bool ChangeUsernameDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin ChangeUsernameDialog creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end ChangeUsernameDialog creation
    return true;
}


/*
 * ChangeUsernameDialog destructor
 */

ChangeUsernameDialog::~ChangeUsernameDialog()
{
////@begin ChangeUsernameDialog destruction
////@end ChangeUsernameDialog destruction
}


/*
 * Member initialisation
 */

void ChangeUsernameDialog::Init()
{
////@begin ChangeUsernameDialog member initialisation
////@end ChangeUsernameDialog member initialisation
}


/*
 * Control creation for ChangeUsernameDialog
 */

void ChangeUsernameDialog::CreateControls()
{
////@begin ChangeUsernameDialog content construction
    ChangeUsernameDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer1);

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer1->Add(itemBoxSizer2, 1, wxGROW, 5);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 1, wxGROW|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer4, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    auto userNameStatic = new wxStaticText( itemDialog1, wxID_STATIC, _("New username"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(userNameStatic, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    userNameInput = new wxTextCtrl( itemDialog1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
    userNameInput->SetMaxLength(128);
    itemBoxSizer4->Add(userNameInput, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( itemDialog1, wxID_STATIC, _("1.Maximum username length is 30 characters.\n2.Username shoud not contain spam or racial discrimination words. \n3.Any illegal username will be reset to random words."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemStaticText7, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticLine* itemStaticLine8 = new wxStaticLine( itemDialog1, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer2->Add(itemStaticLine8, 0, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer9 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer9, 0, wxALIGN_RIGHT|wxALL, 5);
    wxButton* itemButton10 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer9->AddButton(itemButton10);

    wxButton* itemButton11 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer9->AddButton(itemButton11);

    itemStdDialogButtonSizer9->Realize();

////@end ChangeUsernameDialog content construction
}


/*
 * Should we show tooltips?
 */

bool ChangeUsernameDialog::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap ChangeUsernameDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin ChangeUsernameDialog bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end ChangeUsernameDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon ChangeUsernameDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin ChangeUsernameDialog icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end ChangeUsernameDialog icon retrieval
}

wxString ChangeUsernameDialog::GetUserNameInput() {
    return userNameInput->GetValue();
}
