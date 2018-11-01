/////////////////////////////////////////////////////////////////////////////
// Name:        add_offline_task.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     06/09/2018 00:11:30
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 06/09/2018 00:11:30

// For compilers that support precompilation, includes "wx/wx.h".


////@begin includes
#include "wx/imaglist.h"
////@end includes

#include "add_offline_task.h"
#include "../file/remove_file_select.h"

////@begin XPM images
////@end XPM images


/*
 * AddOfflineTask type definition
 */

IMPLEMENT_DYNAMIC_CLASS( AddOfflineTask, wxDialog )


/*
 * AddOfflineTask event table definition
 */

BEGIN_EVENT_TABLE( AddOfflineTask, wxDialog )

////@begin AddOfflineTask event table entries
////@end AddOfflineTask event table entries

END_EVENT_TABLE()


/*
 * AddOfflineTask constructors
 */

AddOfflineTask::AddOfflineTask()
{
	Init();
}

AddOfflineTask::AddOfflineTask( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
	Init();
	Create(parent, id, caption, pos, size, style);
}


/*
 * AddOfflineTask creator
 */

bool AddOfflineTask::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin AddOfflineTask creation
	SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
	wxDialog::Create( parent, id, caption, pos, size, style );

	CreateControls();
	Centre();
////@end AddOfflineTask creation
	return true;
}


/*
 * AddOfflineTask destructor
 */

AddOfflineTask::~AddOfflineTask()
{
////@begin AddOfflineTask destruction
////@end AddOfflineTask destruction
}


/*
 * Member initialisation
 */

void AddOfflineTask::Init()
{
////@begin AddOfflineTask member initialisation
////@end AddOfflineTask member initialisation
}


/*
 * Control creation for AddOfflineTask
 */

void AddOfflineTask::CreateControls()
{
////@begin AddOfflineTask content construction
	AddOfflineTask* itemDialog1 = this;

	wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	itemDialog1->SetSizer(itemBoxSizer2);

	wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer2->Add(itemBoxSizer1, 1, wxGROW|wxALL, 5);

	wxStaticText* itemStaticText2 = new wxStaticText( itemDialog1, wxID_STATIC, _("Add urls or upload torrents to start offline task."), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer1->Add(itemStaticText2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

	mainNotebook = new wxNotebook( itemDialog1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );

	wxPanel* itemPanel4 = new wxPanel( mainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	itemPanel4->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
	wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxVERTICAL);
	itemPanel4->SetSizer(itemBoxSizer5);

	downloadUrlInput = new wxTextCtrl( itemPanel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	itemBoxSizer5->Add(downloadUrlInput, 1, wxGROW|wxALL, 5);

	wxStaticText* itemStaticText7 = new wxStaticText( itemPanel4, wxID_STATIC, _("Support http,ftp,magnet,thunder,ed2k...links"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer5->Add(itemStaticText7, 0, wxALIGN_LEFT|wxALL, 5);

	wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer5->Add(itemBoxSizer4, 0, wxGROW|wxALL, 5);
	wxStaticText* itemStaticText5 = new wxStaticText( itemPanel4, wxID_STATIC, _("If this url need password, please input here:  "), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer4->Add(itemStaticText5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxTextCtrl* itemTextCtrl7 = new wxTextCtrl( itemPanel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer4->Add(itemTextCtrl7, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	mainNotebook->AddPage(itemPanel4, _("Offline Urls"));

	wxPanel* itemPanel8 = new wxPanel( mainNotebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	itemPanel8->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
	wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxVERTICAL);
	itemPanel8->SetSizer(itemBoxSizer9);

	wxBoxSizer* itemBoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer9->Add(itemBoxSizer10, 1, wxGROW|wxALL, 5);
	wxTextCtrl* itemTextCtrl8 = new wxTextCtrl( itemPanel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer10->Add(itemTextCtrl8, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxButton* itemButton9 = new wxButton( itemPanel8, wxID_ANY, _("Browse in my computer"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer10->Add(itemButton9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	mainNotebook->AddPage(itemPanel8, _("Upload Torrents"));

	itemBoxSizer1->Add(mainNotebook, 1, wxGROW, 5);

	wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer1->Add(itemBoxSizer3, 0, wxGROW|wxALL, 5);

	wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, _("Download To:"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	downloadDirTextCtrl = new wxTextCtrl( itemDialog1, wxID_ANY, wxT("/"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer3->Add(downloadDirTextCtrl, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxButton* changeDirectoryButton = new wxButton( itemDialog1, wxID_ANY, _("Change"), wxDefaultPosition, wxDefaultSize, 0 );
	itemBoxSizer3->Add(changeDirectoryButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxStdDialogButtonSizer* itemStdDialogButtonSizer12 = new wxStdDialogButtonSizer;

	itemBoxSizer2->Add(itemStdDialogButtonSizer12, 0, wxALIGN_RIGHT|wxALL, 5);
	wxButton* itemButton13 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
	itemStdDialogButtonSizer12->AddButton(itemButton13);

	wxButton* itemButton14 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	itemStdDialogButtonSizer12->AddButton(itemButton14);

	itemStdDialogButtonSizer12->Realize();

	changeDirectoryButton->Bind(wxEVT_BUTTON, &AddOfflineTask::OnChangeBtnClicked, this);

////@end AddOfflineTask content construction
}


/*
 * Should we show tooltips?
 */

bool AddOfflineTask::ShowToolTips()
{
	return true;
}

/*
 * Get bitmap resources
 */

wxBitmap AddOfflineTask::GetBitmapResource( const wxString& name )
{
	// Bitmap retrieval
////@begin AddOfflineTask bitmap retrieval
	wxUnusedVar(name);
	return wxNullBitmap;
////@end AddOfflineTask bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon AddOfflineTask::GetIconResource( const wxString& name )
{
	// Icon retrieval
////@begin AddOfflineTask icon retrieval
	wxUnusedVar(name);
	return wxNullIcon;
////@end AddOfflineTask icon retrieval
}

void AddOfflineTask::OnChangeBtnClicked(wxCommandEvent &event) {
	WXUNUSED(event);
	auto removeFileSelect = new RemoteFileSelect(this);
	if(removeFileSelect->ShowModal() == wxID_OK){
		auto data = removeFileSelect->GetUserInput();
		if(!data.empty()){
			this->downloadDirTextCtrl->SetValue(data);
		}
	}

}

bool AddOfflineTask::IsTorrentPageSelected() {
	return mainNotebook->GetSelection() == 1;
}

wxString AddOfflineTask::GetDownloadDir() {
	return downloadDirTextCtrl->GetValue();
}

wxString AddOfflineTask::GetDownloadUrl() {
	return downloadUrlInput->GetValue();
}
