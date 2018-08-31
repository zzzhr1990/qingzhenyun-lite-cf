#include "main_frame.h"
MainFrame::MainFrame(const wxString& title, int w, int h)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(w, h)) {

	fileMenu = new wxMenu();

	auto userMenu = new wxMenu();
	//auto userMenuLoginId = wxID_ANY;
	userMenu->Append(wxID_ANY, _T("&Login\tAlt-U"), _T("Change user to login"));

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
	// Events
	this->Bind(wxEVT_IDLE, &MainFrame::OnWindowCreate,this);
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
}

void MainFrame::OnClose(wxCloseEvent& event) {
	event.Skip();

}