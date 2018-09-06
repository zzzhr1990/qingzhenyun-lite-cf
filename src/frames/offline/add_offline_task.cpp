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
		// Generated by DialogBlocks, 06/09/2018 00:57:13 (unregistered)

	AddOfflineTask* itemDialog1 = this;

	wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	itemDialog1->SetSizer(itemBoxSizer2);

	wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
	itemBoxSizer2->Add(itemBoxSizer1, 1, wxGROW | wxALL, 5);

	wxStaticText* itemStaticText2 = new wxStaticText(itemDialog1, wxID_STATIC, _("Add urls or upload torrents to start offline task."), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer1->Add(itemStaticText2, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	wxNotebook* itemNotebook3 = new wxNotebook(itemDialog1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT);

	wxPanel* itemPanel4 = new wxPanel(itemNotebook3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL);
	itemPanel4->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
	wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxVERTICAL);
	itemPanel4->SetSizer(itemBoxSizer5);

	urlInput = new wxTextCtrl(itemPanel4, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	itemBoxSizer5->Add(urlInput, 1, wxGROW, 5);

	wxStaticText* itemStaticText7 = new wxStaticText(itemPanel4, wxID_STATIC, _("Support http,ftp,magnet,thunder,ed2k...links"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer5->Add(itemStaticText7, 0, wxALIGN_LEFT | wxALL, 5);

	itemNotebook3->AddPage(itemPanel4, _("Urls"));

	wxPanel* itemPanel8 = new wxPanel(itemNotebook3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxTAB_TRAVERSAL);
	itemPanel8->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
	wxBoxSizer* itemBoxSizer9 = new wxBoxSizer(wxVERTICAL);
	itemPanel8->SetSizer(itemBoxSizer9);

	wxBoxSizer* itemBoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer9->Add(itemBoxSizer10, 1, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	wxStaticText* itemStaticText11 = new wxStaticText(itemPanel8, wxID_STATIC, _("Torrent file not supported now."), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer10->Add(itemStaticText11, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	itemNotebook3->AddPage(itemPanel8, _("upload torrents"));

	itemBoxSizer1->Add(itemNotebook3, 1, wxGROW, 5);

	wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	itemBoxSizer1->Add(itemBoxSizer3, 0, wxGROW | wxALL, 5);

	wxStaticText* itemStaticText4 = new wxStaticText(itemDialog1, wxID_STATIC, _("Download To:"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	downloadPath = new wxTextCtrl(itemDialog1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer3->Add(downloadPath, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxButton* itemButton6 = new wxButton(itemDialog1, wxID_ANY, _("Change"), wxDefaultPosition, wxDefaultSize, 0);
	itemBoxSizer3->Add(itemButton6, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxStdDialogButtonSizer* itemStdDialogButtonSizer12 = new wxStdDialogButtonSizer;

	itemBoxSizer2->Add(itemStdDialogButtonSizer12, 0, wxALIGN_RIGHT | wxALL, 5);
	wxButton* itemButton13 = new wxButton(itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0);
	itemStdDialogButtonSizer12->AddButton(itemButton13);

	wxButton* itemButton14 = new wxButton(itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0);
	itemStdDialogButtonSizer12->AddButton(itemButton14);

	itemStdDialogButtonSizer12->Realize();

	////@end AddOfflineTask content construction
}

void AddOfflineTask::SetDownloadPath(const wxString& str) {
	this->downloadPath->SetValue(str);
}

wxString AddOfflineTask::GetDownloadPath() {
	return this->downloadPath->GetValue();
}

wxString AddOfflineTask::GetUrlInputStr()
{
	return this->urlInput->GetValue();
}

void AddOfflineTask::ClearUrlInputStr()
{
	this->urlInput->Clear();
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
