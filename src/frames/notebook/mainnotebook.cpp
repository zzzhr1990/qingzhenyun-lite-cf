/////////////////////////////////////////////////////////////////////////////
// Name:        mainnotebook.cpp
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     02/09/2018 17:42:23
// RCS-ID:      
// Copyright:   for free
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
#include "wx/imaglist.h"
#include "my_remote_file.h"
#include "offline_download_task_panel.h"
#include "sync_panel.h"
////@end includes

#include "mainnotebook.h"
#include "../../common/common_event_ids.h"
#include "../../model/remote_file_model.h"
#include "wx/mediactrl.h"   // for wxMediaCtrl
#include "../../model/sync_model.h"
#include "../../model/user_model.h"
#include "../mainframe.h"
#include "../../util/common_util.h"

////@begin XPM images
////@end XPM images


/*
 * MainNotebook type definition
 */

IMPLEMENT_DYNAMIC_CLASS( MainNotebook, wxNotebook )


/*
 * MainNotebook event table definition
 */

BEGIN_EVENT_TABLE( MainNotebook, wxNotebook )

////@begin MainNotebook event table entries
////@end MainNotebook event table entries

END_EVENT_TABLE()


/*
 * MainNotebook constructors
 */

MainNotebook::MainNotebook()
{
    Init();
}

MainNotebook::MainNotebook(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{
    Init();
    Create(parent, id, pos, size, style);
}


/*
 * MainNotebook creator
 */

bool MainNotebook::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{
////@begin MainNotebook creation
    wxNotebook::Create(parent, id, pos, size, style);
    CreateControls();
////@end MainNotebook creation
    return true;
}


/*
 * MainNotebook destructor
 */

MainNotebook::~MainNotebook()
{
////@begin MainNotebook destruction
    timer.Expire();
////@end MainNotebook destruction
}


/*
 * Member initialisation
 */

void MainNotebook::Init()
{
////@begin MainNotebook member initialisation

////@end MainNotebook member initialisation
}


/*
 * Control creation for MainNotebook
 */

void MainNotebook::CreateControls()
{    
////@begin MainNotebook content construction
    MainNotebook* itemNotebook1 = this;

    myRemoteFilePanel = new MyRemoteFilePanel( itemNotebook1, ID_MY_REMOTE_FILE_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    myRemoteFilePanel->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    myRemoteFilePanel->SetName(wxT("MyRemoteFiles"));
    this->AddPage(myRemoteFilePanel, _("My Remote Files"));

    offlineDownloadTaskPanel = new OfflineDownloadTaskPanel( itemNotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
	offlineDownloadTaskPanel->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    this->AddPage(offlineDownloadTaskPanel, _("Offline Download Task"));

    syncPanel = new SyncPanel( itemNotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    syncPanel->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    this->AddPage(syncPanel, _("Sync Task"));

    /*
    wxPanel* itemPanel21 = new wxPanel( itemNotebook1, ID_SYNC_TASK_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    itemPanel21->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxBoxSizer* itemBoxSizer22 = new wxBoxSizer(wxVERTICAL);
    itemPanel21->SetSizer(itemBoxSizer22);

    wxBoxSizer* itemBoxSizer23 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer22->Add(itemBoxSizer23, 1, wxGROW, 5);
    wxBoxSizer* itemBoxSizer7 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer23->Add(itemBoxSizer7, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    wxStaticText* itemStaticText8 = new wxStaticText( itemPanel21, wxID_STATIC, _("This function is not available now."), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer7->Add(itemStaticText8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);


    this->AddPage(itemPanel21, _("Sync Task"));
     */
	offlineDownloadTaskPanel->Bind(wxEVT_THREAD, &MainNotebook::OnThreadEvent, this);

		// you could specify a macro backend here like
		//  wxMEDIABACKEND_WMP10);
		//        wxT("wxPDFMediaBackend"));
    auto task = [this](){
        wxThreadEvent event(wxEVT_THREAD);
        auto ts = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        event.SetTimestamp(ts);
        //event.SetId(this->GetId());
        event.SetInt(PAGE_TIMER_TICK);
        //event.SetPayload(v);
        //std::cout << "Tick0" << std::endl;
        wxQueueEvent(this->offlineDownloadTaskPanel, event.Clone());
    };
    timer.StartTimer(2000,task);
////@end MainNotebook content construction
}


/*
 * Should we show tooltips?
 */
void MainNotebook::OnThreadEvent(wxThreadEvent &event) {
	switch (event.GetInt()) {
	case USER_GOTO_DIRECTORY: {
		auto& path = event.GetString();
		auto &model = RemoteFileModel::Instance();
		model.SetCurrentPage(1);
		model.SetCurrentPath(path);
		this->ChangeSelection(0);
		RefreshCurrentPage();
		break;
	}
	case PAGE_TIMER_TICK:{
        TimerTick();
        break;
	}
	case USER_SYNC_SPEED_REFRESH:{
        const auto & data = event.GetPayload<ResponseEntity>();
        auto* main = (MainFrame*)this->GetParent();
        const auto & value = data.result;
        auto upSpeed = value.at(U("upSpeed")).as_number().to_uint64();
        auto downSpeed = value.at(U("downSpeed")).as_number().to_uint64();

        auto upCount = value.at(U("upCount")).as_integer();
        auto downCount = value.at(U("downCount")).as_integer();
        auto cs = (upCount == 0 && downCount == 0) ? _T("Wait") : _T("Sync");
        main->SetStatusText(wxString::Format(_T("%s - Up(%d):%s/s, Down(%d):%s/s"),cs,
                upCount,ConvertSizeToDisplay(upSpeed),
                downCount, ConvertSizeToDisplay(downSpeed)),1);

	    break;
	}
	default:
		event.Skip();
	}
	//
}
bool MainNotebook::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap MainNotebook::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin MainNotebook bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end MainNotebook bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon MainNotebook::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin MainNotebook icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end MainNotebook icon retrieval
}

void MainNotebook::RefreshCurrentPage(int selection) {
	if (!inited) {
		inited = true;
		this->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &MainNotebook::OnNoteBookChange, this);
	}
	if(selection < 0){
        selection = this->GetSelection();
	}
    switch (selection){
        case 0:
            myRemoteFilePanel->RefreshData(true);
            break;
		case 1:
			offlineDownloadTaskPanel->RefreshData();
			break;
        case 2:
            syncPanel->RefreshData();
            break;
        default:
            return;
    }
}

void MainNotebook::OnNoteBookChange(wxBookCtrlEvent &event) {
	event.Skip();
	RefreshCurrentPage(event.GetSelection());

}

void MainNotebook::UpdateSpaceCapacity(const long long & spaceUsed, const long long & spaceCapacity) {
	myRemoteFilePanel->UpdateSpaceCapacity(spaceUsed, spaceCapacity);
}

void MainNotebook::TimerTick() {
    auto selection = this->GetSelection();
    switch (selection){
        case 0:
			if (UserModel::Instance().IsUserLogin()) {
				myRemoteFilePanel->RefreshData(false);
				break;
			}
        case 1:
            //offlineDownloadTaskPanel->RefreshData();
            break;
        case 2:
            syncPanel->RefreshData();
            break;
        default:
            break;
    }

    SyncModel::Instance().ReportSpeed(this->offlineDownloadTaskPanel);
}

void MainNotebook::DoOpenFiles(const wxArrayString &fileNames) {
    myRemoteFilePanel->DoOpenFiles(fileNames);
}
