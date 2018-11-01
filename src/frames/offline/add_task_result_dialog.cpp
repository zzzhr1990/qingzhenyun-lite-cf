/////////////////////////////////////////////////////////////////////////////
// Name:        addtaskresultdialog.cpp
// Purpose:
// Author:
// Modified by:
// Created:     Wed 31 Oct 23:02:11 2018
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////



////@begin includes
////@end includes

#include "add_task_result_dialog.h"

////@begin XPM images
////@end XPM images


/*
 * AddTaskResultDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( AddTaskResultDialog, wxDialog )


/*
 * AddTaskResultDialog event table definition
 */

BEGIN_EVENT_TABLE( AddTaskResultDialog, wxDialog )

////@begin AddTaskResultDialog event table entries
////@end AddTaskResultDialog event table entries

END_EVENT_TABLE()


/*
 * AddTaskResultDialog constructors
 */

AddTaskResultDialog::AddTaskResultDialog()
{
    Init();
}

AddTaskResultDialog::AddTaskResultDialog( wxWindow* parent, wxArrayString& checkLists,wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent,checkLists, id, caption, pos, size, style);
}


/*
 * AddTaskResultDialog creator
 */

bool AddTaskResultDialog::Create( wxWindow* parent,wxArrayString & checkLists, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin AddTaskResultDialog creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls(checkLists);
    Centre();
////@end AddTaskResultDialog creation
    return true;
}


/*
 * AddTaskResultDialog destructor
 */

AddTaskResultDialog::~AddTaskResultDialog()
{
////@begin AddTaskResultDialog destruction
////@end AddTaskResultDialog destruction
}


/*
 * Member initialisation
 */

void AddTaskResultDialog::Init()
{
////@begin AddTaskResultDialog member initialisation
////@end AddTaskResultDialog member initialisation
}


/*
 * Control creation for AddTaskResultDialog
 */

void AddTaskResultDialog::CreateControls(wxArrayString& checkLists)
{
////@begin AddTaskResultDialog content construction
    AddTaskResultDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer2->Add(itemBoxSizer1, 1, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText2 = new wxStaticText( itemDialog1, wxID_STATIC, _("Select files you want download"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add(itemStaticText2, 0, wxALIGN_LEFT|wxALL, 5);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer1->Add(itemBoxSizer3, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Files cached from server, click refresh to reload"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText4, 1, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxTOP|wxBOTTOM, 5);

    wxButton* itemButton5 = new wxButton( itemDialog1, wxID_ANY, _("Refresh"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemButton5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);


    mainCheckListBox = new wxCheckListBox( itemDialog1, wxID_ANY, wxDefaultPosition, wxDefaultSize, checkLists, wxLB_SINGLE );
    itemBoxSizer1->Add(mainCheckListBox, 1, wxGROW, 5);

    wxCheckBox* itemCheckBox6 = new wxCheckBox( itemDialog1, wxID_ANY, _("Select / Unselect all"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox6->SetValue(false);
    itemBoxSizer1->Add(itemCheckBox6, 0, wxALIGN_LEFT|wxALL, 5);

    wxStaticLine* itemStaticLine4 = new wxStaticLine( itemDialog1, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer1->Add(itemStaticLine4, 0, wxGROW|wxALL, 5);

    wxStdDialogButtonSizer* itemStdDialogButtonSizer5 = new wxStdDialogButtonSizer;

    itemBoxSizer1->Add(itemStdDialogButtonSizer5, 0, wxALIGN_RIGHT|wxALL, 5);
    wxButton* itemButton6 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer5->AddButton(itemButton6);

    wxButton* itemButton7 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer5->AddButton(itemButton7);

    itemStdDialogButtonSizer5->Realize();

    //mainCheckListBox->
    itemCheckBox6->Bind(wxEVT_CHECKBOX,&AddTaskResultDialog::OnCheckListBoxChanged, this);
    this->SelectAllItems(true);
////@end AddTaskResultDialog content construction
}


/*
 * Should we show tooltips?
 */

bool AddTaskResultDialog::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap AddTaskResultDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin AddTaskResultDialog bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end AddTaskResultDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon AddTaskResultDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin AddTaskResultDialog icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end AddTaskResultDialog icon retrieval
}

void AddTaskResultDialog::SelectAllItems(bool select) {
    for(unsigned int i = 0; i< this->mainCheckListBox->GetCount(); i++){
        this->mainCheckListBox->Check(i,select);
    }
}

void AddTaskResultDialog::OnCheckListBoxChanged(wxCommandEvent & evt) {
    SelectAllItems(evt.GetSelection() == 1);
}

utility::string_t AddTaskResultDialog::GetItemsSelectString() {
    bool allSelect = true;
    web::json::value arr = web::json::value::array();
    web::json::array::size_type count = 0;
    for(unsigned int i = 0; i< this->mainCheckListBox->GetCount(); i++){
        //this->mainCheckListBox->Check(i,select);
        if(this->mainCheckListBox->IsChecked(i)){
            arr[count] = web::json::value::number(i);
        }else{
            allSelect = false;
        }
        count ++;
    }
    if(allSelect){
        auto res = web::json::value::array();
        res[0] = web::json::value::string(_XPLATSTR("*"));
        return res.serialize();
    }
    return arr.serialize();
}
