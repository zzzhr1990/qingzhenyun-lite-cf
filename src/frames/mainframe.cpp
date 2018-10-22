/////////////////////////////////////////////////////////////////////////////
// Name:        mainframe.cpp
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     01/09/2018 23:54:25
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
////@end includes

#include "mainframe.h"

////@begin XPM images
#include "../resources/if_cloud_main.xpm"
#include "../resources/user.xpm"
#include "../resources/settings.xpm"
#include "../model/user_model.h"
#include "../common/common_event_ids.h"
#include "../util/common_util.h"
#include "../model/sync_model.h"
#include "../model/update_model.h"
#include "userlogindialog.h"
#include "updatedialog.h"
#include "userdialog.h"
#include <wx/utils.h>
////@end XPM images


/*
 * MainFrame type definition
 */

IMPLEMENT_CLASS( MainFrame, wxFrame )


/*
 * MainFrame event table definition
 */

BEGIN_EVENT_TABLE( MainFrame, wxFrame )

////@begin MainFrame event table entries
////@end MainFrame event table entries

END_EVENT_TABLE()


/*
 * MainFrame constructors
 */

MainFrame::MainFrame()
{
    Init();
}

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}


/*
 * MainFrame creator
 */

bool MainFrame::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin MainFrame creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    SetIcon(GetIconResource(wxT("if_cloud_main.xpm")));
    Centre();
////@end MainFrame creation
    return true;
}


/*
 * MainFrame destructor
 */

MainFrame::~MainFrame()
{
////@begin MainFrame destruction
////@end MainFrame destruction
}


/*
 * Member initialisation
 */

void MainFrame::Init()
{
////@begin MainFrame member initialisation
////@end MainFrame member initialisation
}


/*
 * Control creation for MainFrame
 */

void MainFrame::CreateControls()
{    
////@begin MainFrame content construction
    MainFrame* itemFrame1 = this;

    auto* menuBar = new wxMenuBar;
    auto* itemMenu2 = new wxMenu;
    itemMenu2->Append(wxID_ANY, _("Login/Change User"), wxEmptyString, wxITEM_NORMAL);
    menuBar->Append(itemMenu2, _("User"));
    itemFrame1->SetMenuBar(menuBar);

    wxToolBar* mainToolBar = CreateToolBar( wxTB_FLAT|wxTB_HORIZONTAL, ID_TOOLBAR );
    wxBitmap itemtool5Bitmap(itemFrame1->GetBitmapResource(wxT("user.xpm")));
    wxBitmap itemtool5BitmapDisabled;
	mainToolBar->AddTool(ID_USER_TOOL, wxEmptyString, itemtool5Bitmap, itemtool5BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
	mainToolBar->Bind(wxEVT_TOOL, &MainFrame::OnToolClick, this);
	mainToolBar->AddSeparator();
    wxBitmap itemtool8Bitmap(itemFrame1->GetBitmapResource(wxT("settings.xpm")));
    wxBitmap itemtool8BitmapDisabled;
	mainToolBar->AddTool(ID_SETTING_TOOL, wxEmptyString, itemtool8Bitmap, itemtool8BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
	mainToolBar->Realize();
    itemFrame1->SetToolBar(mainToolBar);

    auto* itemBoxSizer14 = new wxBoxSizer(wxVERTICAL);
    itemFrame1->SetSizer(itemBoxSizer14);

    auto* itemBoxSizer15 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer14->Add(itemBoxSizer15, 1, wxGROW, 5);


    mainNotebook = new MainNotebook( itemFrame1, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
    itemBoxSizer15->Add(mainNotebook, 1, wxGROW, 5);

    wxStatusBar* itemStatusBar17 = new wxStatusBar( itemFrame1, ID_STATUSBAR, wxST_SIZEGRIP|wxNO_BORDER );
    itemStatusBar17->SetFieldsCount(2);
    itemStatusBar17->SetStatusText(_("Waiting..."), 0);
    //itemStatusBar17->SetStatusText(_("-"), 1);
    itemStatusBar17->SetStatusText(_("Sync"), 1);
    int itemStatusBar17Widths[2];
    itemStatusBar17Widths[0] = -1;
    itemStatusBar17Widths[1] = 200;
    // itemStatusBar17Widths[2] = 200;
    itemStatusBar17->SetStatusWidths(2, itemStatusBar17Widths);
    itemFrame1->SetStatusBar(itemStatusBar17);
    // when inited, check this box.
    this->Bind(wxEVT_THREAD, &MainFrame::OnThreadEvent, this);
    this->Bind(wxEVT_IDLE, &MainFrame::OnWindowCreate, this);
    this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
////@end MainFrame content construction
}
void MainFrame::OnToolClick(const wxCommandEvent& event) {
	if (event.GetId() == ID_USER_TOOL) {
		//showLoginFrame(_("Login"));
		auto & userModel = UserModel::Instance();
		if(userModel.IsUserLogin() && userModel.GetUserInfo().has_field(_XPLATSTR("uuid"))){
		    // Show
		    auto * userDialog = new UserDialog(this,userModel.GetUserInfo());
            userDialog->ShowModal();
		}else{
            showLoginFrame(_("Login"));
		}
	}
}
void MainFrame::showLoginFrame(const wxString& text){
    if (this->loginFrame == nullptr) {
        loginFrame = new LoginFrame(this, wxID_ANY);
        loginFrame->Iconize(false);
        //
    }
    loginFrame->SetLabel(text);
    loginFrame->SetTips(text);
    // login_frame->Show(true);
    // loginFrame->Raise();  // doesn't seem to work
    // loginFrame->SetFocus();  // does nothing
    auto const &result = loginFrame->ShowModal(); // this by itself doesn't work
    if(result == wxID_OK)
    {
        // check validate
        const auto &userInput = loginFrame->getUserInput();
        const auto &userPassword = loginFrame->getUserPassword();
        TryLogin(userInput, Utf8MD5(userPassword));
    }else{
		if (UserModel::Instance().GetToken().empty()) {
			Close();
		}
		else {
			UserModel::Instance().CheckToken(this);
		}
        
    }
    // std::cout << result << std::endl;
    // loginFrame->RequestUserAttention();

}

void MainFrame::OnWindowCreate(wxIdleEvent& event){
    this->Unbind(wxEVT_IDLE, &MainFrame::OnWindowCreate, this);
    event.Skip();
    if(UserModel::Instance().GetToken().empty()){
        showLoginFrame(_("You need to login first."));
    }else{
        // check token validate
        UserModel::Instance().CheckToken(this);
    }

    UpdateModel::Instance().CheckUpdate(this);

	//UserLoginDialog * userLogin = new UserLoginDialog(this);
	//userLogin->ShowModal();
	//Check Version
	

    //UserModel::Instance().IsUserLogin();
    // showLoginFrame(_("苟利国家"));
    // check login ...
    // user_model->terminate();
    //this->Disconnect(wxEVT_IDLE, wxIdleEventHandler(MainFrame::OnWindowCreate));
    /*
    if (!UserModel::instance().IsUserLogin()) {
        showLoginFrame();
    }else{
        //refresh
        OnUserLogin();
    }
     */
}


/*
 * Should we show tooltips?
 */

bool MainFrame::ShowToolTips()
{
    return true;
}

void MainFrame::OnClose(wxCloseEvent& event){
	if (!SyncModel::Instance().isAllFinished()) {
		if (wxOK != wxMessageBox(_("It seems you are syncing files, are you sure?"), _("Confirm close"), wxOK | wxCANCEL | wxICON_ASTERISK)) {
			event.Veto();
			return;
		}
	}
    event.Skip();
    this->Terminate();
    UserModel::Instance().Terminate();
    UpdateModel::Instance().Terminate();
}

/*
 * Get bitmap resources
 */

wxBitmap MainFrame::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin MainFrame bitmap retrieval
    wxUnusedVar(name);
    if (name == wxT("user.xpm"))
    {
        wxBitmap bitmap(user_xpm);
        return bitmap;
    }
    else if (name == wxT("settings.xpm"))
    {
        wxBitmap bitmap(settings_xpm);
        return bitmap;
    }
    return wxNullBitmap;
////@end MainFrame bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon MainFrame::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin MainFrame icon retrieval
    wxUnusedVar(name);
    if (name == wxT("if_cloud_main.xpm"))
    {
        wxIcon icon(if_cloud_xpm);
        return icon;
    }
    return wxNullIcon;
////@end MainFrame icon retrieval
}

void MainFrame::TryLogin(const wxString &input, const wxString &password) {
    UserModel::Instance().TryLogin(this,input,password);
}

void MainFrame::OnThreadEvent(wxThreadEvent &event) {
    if(this->terminated){
        return;
    }
    switch (event.GetInt()){
        case USER_LOGIN_RESPONSE:{
            SetStatusText(_("User login..."), 0);
            const ResponseEntity &r = event.GetPayload<ResponseEntity>();
            UserModel::Instance().SetUserInfo(r.result);
            UserModel::Instance().StartUserCheckLoop(this);
            mainNotebook->RefreshCurrentPage();
			if (r.result.has_field(U("spaceUsed"))) {
				mainNotebook->UpdateSpaceCapacity(r.result.at(U("spaceUsed")).as_number().to_int64(), r.result.at(U("spaceCapacity")).as_number().to_int64());
			}
			
            break;
        }

        case USER_LOGIN_FAILED_RESPONSE:
        {
            const ResponseEntity &r = event.GetPayload<ResponseEntity>();
            UserModel::Instance().Logout();
            showLoginFrame(_T("Login failed, please login again."));
            break;
        }

		case USER_REFRESH_RESPONSE: {
			const ResponseEntity &r = event.GetPayload<ResponseEntity>();
			long d = event.GetTimestamp();
			time_t time = d;
			SetStatusText(wxString::Format(_("User info update at...%s"), ConvertTimeToDisplay(time), "%Y-%m-%d %H:%M"));
			UserModel::Instance().SetUserInfo(r.result);
			if (r.result.has_field(U("spaceUsed"))) {
				mainNotebook->UpdateSpaceCapacity(r.result.at(U("spaceUsed")).as_number().to_int64(), r.result.at(U("spaceCapacity")).as_number().to_int64());
			}
            break;
		}
        case PROGRAM_UPDATE_INFO:{
            const ResponseEntity &r = event.GetPayload<ResponseEntity>();
            if(r.success){
                auto updateInfoList = r.result.as_array();
                if(updateInfoList.size() > 0){
                    auto updateInfo = updateInfoList.at(0);
                    auto *update = new UpdateDialog(this,updateInfo);
                    if(wxID_OK == update->ShowModal() ){
                        //std::cout << "Open New" << std::endl;
                        auto linkUrl = updateInfo.at((_XPLATSTR("linkUrl"))).as_string();
                        if(updateInfo.at((_XPLATSTR("action"))).as_integer() == 0){
                            wxLaunchDefaultBrowser(linkUrl);
                        }
                    }
                }

            }
            break;
        }
        default:
            event.Skip();
    }
    // 智障Windows，一半的代码都是给傻逼微软擦屁股
	
}

void MainFrame::DoOpenFiles(const wxArrayString &fileNames) {
    mainNotebook->DoOpenFiles(fileNames);
}

void MainFrame::Terminate() {
    this->terminated = true;
}
