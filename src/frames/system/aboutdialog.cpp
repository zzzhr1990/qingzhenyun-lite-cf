//
// Created by zzzhr on 2018/11/3.
//

////@begin includes
#include "wx/imaglist.h"
////@end includes

#include "aboutdialog.h"

////@begin XPM images
////@end XPM images


/*
 * AboutDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( AboutDialog, wxDialog )


/*
 * AboutDialog event table definition
 */

BEGIN_EVENT_TABLE( AboutDialog, wxDialog )

////@begin AboutDialog event table entries
////@end AboutDialog event table entries

END_EVENT_TABLE()


/*
 * AboutDialog constructors
 */

AboutDialog::AboutDialog()
{
    Init();
}

AboutDialog::AboutDialog( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * AboutDialog creator
 */

bool AboutDialog::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin AboutDialog creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end AboutDialog creation
    return true;
}


/*
 * AboutDialog destructor
 */

AboutDialog::~AboutDialog()
{
////@begin AboutDialog destruction
////@end AboutDialog destruction
}


/*
 * Member initialisation
 */

void AboutDialog::Init()
{
////@begin AboutDialog member initialisation
////@end AboutDialog member initialisation
}


/*
 * Control creation for AboutDialog
 */

void AboutDialog::CreateControls()
{
////@begin AboutDialog content construction
    AboutDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxNotebook* itemNotebook1 = new wxNotebook( itemDialog1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

    wxPanel* itemPanel2 = new wxPanel( itemNotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel2->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    itemPanel2->SetSizer(itemBoxSizer1);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer1->Add(itemBoxSizer3, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxStaticBitmap* itemStaticBitmap4 = new wxStaticBitmap( itemPanel2, wxID_STATIC, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticBitmap4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText6 = new wxStaticText( itemPanel2, wxID_STATIC, _("%s(%s)"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText6, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( itemPanel2, wxID_STATIC, _("Copyright %s"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText7, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer3->Add(itemBoxSizer9, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);
    wxStaticText* itemStaticText10 = new wxStaticText( itemPanel2, wxID_STATIC, _("Version %s"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer9->Add(itemStaticText10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton11 = new wxButton( itemPanel2, wxID_ANY, _("Check for update"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer9->Add(itemButton11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* itemButton13 = new wxButton( itemPanel2, wxID_ANY, _("Access our website"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemButton13, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    itemNotebook1->AddPage(itemPanel2, _("About"));

    wxPanel* itemPanel3 = new wxPanel( itemNotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    itemPanel3->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
    itemPanel3->SetSizer(itemBoxSizer4);

    wxStaticText* itemStaticText5 = new wxStaticText( itemPanel3, wxID_STATIC, _("You can also find license on install path /pravicy"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemStaticText5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl6 = new wxTextCtrl( itemPanel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
    itemBoxSizer4->Add(itemTextCtrl6, 1, wxGROW|wxALL, 5);

    itemNotebook1->AddPage(itemPanel3, _("Pravicy"));

    wxPanel* itemPanel7 = new wxPanel( itemNotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    itemPanel7->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxVERTICAL);
    itemPanel7->SetSizer(itemBoxSizer8);

    wxStaticText* itemStaticText9 = new wxStaticText( itemPanel7, wxID_STATIC, _("You can also find license on install path /license"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(itemStaticText9, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl10 = new wxTextCtrl( itemPanel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
    itemBoxSizer8->Add(itemTextCtrl10, 1, wxGROW|wxALL, 5);

    itemNotebook1->AddPage(itemPanel7, _("License"));

    itemBoxSizer2->Add(itemNotebook1, 1, wxGROW|wxALL, 5);

    wxStaticLine* itemStaticLine11 = new wxStaticLine( itemDialog1, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer2->Add(itemStaticLine11, 0, wxGROW|wxALL, 5);

    wxButton* itemButton12 = new wxButton( itemDialog1, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer2->Add(itemButton12, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

////@end AboutDialog content construction
}


/*
 * Should we show tooltips?
 */

bool AboutDialog::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap AboutDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin AboutDialog bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end AboutDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon AboutDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin AboutDialog icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end AboutDialog icon retrieval
}