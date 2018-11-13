//
// Created by zzzhr on 2018/11/4.
//

#include "settingdialog.h"

////@begin includes
////@end includes

#include "settingdialog.h"

////@begin XPM images
////@end XPM images


/*
 * SettingDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( SettingDialog, wxDialog )


/*
 * SettingDialog event table definition
 */

BEGIN_EVENT_TABLE( SettingDialog, wxDialog )

////@begin SettingDialog event table entries
////@end SettingDialog event table entries

END_EVENT_TABLE()


/*
 * SettingDialog constructors
 */

SettingDialog::SettingDialog()
{
    Init();
}

SettingDialog::SettingDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * SettingDialog creator
 */

bool SettingDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin SettingDialog creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
////@end SettingDialog creation
    return true;
}


/*
 * SettingDialog destructor
 */

SettingDialog::~SettingDialog()
{
////@begin SettingDialog destruction
////@end SettingDialog destruction
}


/*
 * Member initialisation
 */

void SettingDialog::Init()
{
////@begin SettingDialog member initialisation
////@end SettingDialog member initialisation
}


/*
 * Control creation for SettingDialog
 */

void SettingDialog::CreateControls()
{
////@begin SettingDialog content construction
    SettingDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer1);

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer1->Add(itemBoxSizer2, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer3->Add(itemBoxSizer4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxCheckBox* itemCheckBox5 = new wxCheckBox( itemDialog1, ID_CHECKBOX2, _("If there are tasks running, confirm when program exit"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox5->SetValue(false);
    itemBoxSizer4->Add(itemCheckBox5, 0, wxALIGN_LEFT|wxALL, 5);

    wxCheckBox* itemCheckBox6 = new wxCheckBox( itemDialog1, ID_CHECKBOX, _("Auto check for update"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox6->SetValue(false);
    itemBoxSizer4->Add(itemCheckBox6, 0, wxALIGN_LEFT|wxALL, 5);

    wxFlexGridSizer* itemFlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 0);
    itemBoxSizer4->Add(itemFlexGridSizer7, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText8 = new wxStaticText( itemDialog1, wxID_STATIC, _("Working tasks at same time"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer7->Add(itemStaticText8, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSpinCtrl* itemSpinCtrl9 = new wxSpinCtrl( itemDialog1, ID_SPINCTRL, wxT("2"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 5, 2 );
    itemFlexGridSizer7->Add(itemSpinCtrl9, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText10 = new wxStaticText( itemDialog1, wxID_STATIC, _("Max working threads for every task"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer7->Add(itemStaticText10, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSpinCtrl* itemSpinCtrl11 = new wxSpinCtrl( itemDialog1, ID_SPINCTRL1, wxT("2"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 5, 2 );
    itemFlexGridSizer7->Add(itemSpinCtrl11, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText12 = new wxStaticText( itemDialog1, wxID_STATIC, _("Max retry times for every task"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer7->Add(itemStaticText12, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSpinCtrl* itemSpinCtrl13 = new wxSpinCtrl( itemDialog1, ID_SPINCTRL2, wxT("5"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10, 5 );
    itemFlexGridSizer7->Add(itemSpinCtrl13, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText14 = new wxStaticText( itemDialog1, wxID_STATIC, _("Language"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer7->Add(itemStaticText14, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString itemChoice15Strings;
    itemChoice15Strings.Add(_("Default (English-US)"));
    itemChoice15Strings.Add(_("Chinese S"));
    itemChoice15Strings.Add(_("English"));
    wxChoice* itemChoice15 = new wxChoice( itemDialog1, ID_CHOICE, wxDefaultPosition, wxDefaultSize, itemChoice15Strings, 0 );
    itemChoice15->SetStringSelection(_("Default (English-US)"));
    itemFlexGridSizer7->Add(itemChoice15, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    itemFlexGridSizer7->AddGrowableCol(1);

    wxStaticText* itemStaticText16 = new wxStaticText( itemDialog1, wxID_STATIC, _("Note: If you changed language,  you may restart program to apply."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemStaticText16, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticLine* itemStaticLine4 = new wxStaticLine( itemDialog1, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer1->Add(itemStaticLine4, 0, wxGROW, 5);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer1->Add(itemBoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxButton* itemButton3 = new wxButton( itemDialog1, ID_BUTTON1, _("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemButton3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton6 = new wxButton( itemDialog1, ID_BUTTON, _("Close"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemButton6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);


////@end SettingDialog content construction
}


/*
 * Should we show tooltips?
 */

bool SettingDialog::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap SettingDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin SettingDialog bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end SettingDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon SettingDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin SettingDialog icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end SettingDialog icon retrieval
}
