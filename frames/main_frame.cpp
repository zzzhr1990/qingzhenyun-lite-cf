#include "main_frame.h"
#include "../model/user_model.h"
#include "../util/common_util.h"
#include "../common/common_window_ids.h"
#include "./notebook/note_index.h"

MainFrame::MainFrame(const wxString& title, int w, int h)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(w, h)) {

	fileMenu = new wxMenu();

	auto userMenu = new wxMenu();
	//auto userMenuLoginId = wxID_ANY;
	userMenu->Append(ID_USER_LOGIN_MENU_ITEM, _T("&Login\tAlt-U"), _T("Change user to login"));
	
	// the "About" item should be in the help menu
	helpMenu = new wxMenu();

	helpMenu->Append(wxID_ABOUT, "&About\tF1", _T("Show about dialog"));
	fileMenu->Append(wxID_EXIT, "&Exit\tAlt-X", "Quit this program");
	fileMenu->Append(wxID_FILE1, "&Log\tAlt-L", "Show log window");


	// now append the freshly created menu to the menu bar...
	auto *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, "&File");
	menuBar->Append(userMenu, "&User");
	menuBar->Append(helpMenu, "&Help");
	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);

	mainNotebook = new NoteIndex(this, wxID_ANY);
	wxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(mainNotebook, 1, wxGROW);
	SetSizerAndFit(mainSizer);

	// Events
	this->Bind(wxEVT_THREAD,&MainFrame::OnThreadEvent,this);
	this->Bind(wxEVT_IDLE, &MainFrame::OnWindowCreate,this);
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
	this->Bind(wxEVT_THREAD, &MainFrame::OnThreadEvent, this);
	CreateStatusBar(2);
	SetStatusText(_T("Waiting..."));
	UserModel::Instance().StartUserCheckLoop(this, this->GetId());
}

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}


void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox(wxString::Format
	(
		_T("Welcome to %s!\n")
		_T("\n")
		_T("Access https://www.qingzhenyun.com\n")
		_T("for more information.\n\n")
		_T("running under %s."),
		_T("Halal Cloud Disk"),
		wxGetOsDescription()
	),
		_T("Halal Cloud Disk"),
		wxOK | wxICON_INFORMATION,
		this);
}

void MainFrame::OnWindowCreate(wxIdleEvent& WXUNUSED(event)) {
	this->Unbind(wxEVT_IDLE, &MainFrame::OnWindowCreate, this);
	if (!UserModel::Instance().IsUserLogin()) {
		ShowLoginFrame();
	}
	else {
		//refresh
		// OnUserLogin();
		if (UserModel::Instance().CheckUserLogin(this, this->GetId())) {
			SetStatusText(_T("Checking login..."));
		}
		else {
			ShowLoginFrame();
		}
	}
	
}

void MainFrame::DoRefreshInterface() {
	((NoteIndex*)this->mainNotebook)->RefreshUserCurrentData();
}

void MainFrame::OnClose(wxCloseEvent& event) {
	UserModel::Instance().terminate();
	event.Skip();
}

void MainFrame::ShowLoginFrame() {
	if (this->loginFrame == nullptr) {
		loginFrame = new LoginFrame(this, wxID_ANY);
		loginFrame ->Iconize(false);
	}

	loginFrame->Raise();  // doesn't seem to work
	loginFrame->SetFocus();  // does nothing
	loginFrame->ShowModal(); // this by itself doesn't work
	loginFrame->RequestUserAttention();
}

void MainFrame::OnUserLogin() {
	// ((NoteIndex*)this->main_notebook)->RefreshUserCurrentData();
	DoRefreshInterface();
	SetStatusText(_T("User Login"));
	
}

void MainFrame::OnLoginMenuClick(wxCommandEvent &WXUNUSED(event)) {
	ShowLoginFrame();
}

void MainFrame::OnThreadEvent(wxThreadEvent& event)
{
	// true is to force the frame to close
	// Close(true);
	int eventType = event.GetInt();
	if (eventType == USER_REFRESH_RESPONSE) {
		long d = event.GetTimestamp();
		time_t time = d;
		SetStatusText(wxString::Format(_T("User info update at...%s"), ConvertTimeToDisplay(time), "%Y-%m-%d %H:%M"));
	}
	else if(eventType == NEED_NEED_RELOGIN_RESPONSE) {
		ShowLoginFrame();
	}
	else if (eventType == USER_CHECKED_OK) {
		DoRefreshInterface();
	}
	else {
		SetStatusText(wxString::Format(_T("Unknown event type...%d"), eventType));
	}
}