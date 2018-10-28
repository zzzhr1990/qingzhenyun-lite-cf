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



////@begin includes
#include "../common/common_wx.h"
////@end includes

#include "mainframe.h"

////@begin XPM images
#include "../resources/if_cloud_main.xpm"
#include "../resources/user.xpm"
#include "../resources/settings.xpm"
////@end XPM images

#include "../model/user_model.h"
#include "../api_model/api_user_model.h"
#include "../common/common_event_ids.h"
#include "../util/common_util.h"
#include "../model/sync_model.h"
#include "../model/update_model.h"
#include "../common/common_util.hpp"
#include "../local_model/config_model.h"
#include "userlogindialog.h"
#include "updatedialog.h"
#include "userdialog.h"
#include <wx/utils.h>
#include <wx/stdpaths.h>

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


    mainNotebook = new MainNotebook( itemFrame1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
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
		auto & user_model = qingzhen::api::api_user_model::instance();
		if(user_model.is_user_login()){
		    // Show
		    auto * userDialog = new UserDialog(this,user_model.get_user_info());
            userDialog->ShowModal();
            if(userDialog->GetContinueLogin()){
                globalTimer.Expire();
                showLoginFrame(_("Login"));
            }
		}else{
            showLoginFrame(_("Login"));
		}
	}
}

void MainFrame::showLoginFrame(const wxString& text) {
    auto * loginDialog = new UserLoginDialog(this, wxID_ANY, text);
    if(wxID_OK == loginDialog->ShowModal()) {
        //std::cout << "Try login" << std::endl;
        if(loginDialog->GetNoteCurrentSelection() == 0){
            // Login By User Id
            this->TryLogin(loginDialog->GetPasswordCountryCode(),loginDialog->GetUserInput(),loginDialog->GetUsePassword());
        }else{
            this->TryLoginByMessage(loginDialog->GetPhoneInfo(), loginDialog->GetMessageCodeInput());
        }
    }

    /*
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
        const auto &userInputStaticText = loginFrame->getUserInput();
        const auto &userPassword = loginFrame->getUserPassword();
        TryLogin(userInputStaticText, Utf8MD5(userPassword));
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
     */
}

void MainFrame::OnWindowCreate(wxIdleEvent& event){
    this->Unbind(wxEVT_IDLE, &MainFrame::OnWindowCreate, this);
    event.Skip();

    
	this->FindConfigPath();
	UpdateModel::Instance().CheckUpdate(this);
    qingzhen::api::api_user_model::instance().async_read_token().then([this](utility::string_t token){
        if(token.empty()){
            this->CallAfter([this](){this->showLoginFrame(_("User login"));});
        }else{
            //std::cout << "Read the token:" << token << std::endl; login by token
			check_login_source.cancel();
			check_login_source = pplx::cancellation_token_source();
			qingzhen::api::api_user_model::instance().check_user_info(check_login_source).then([this](response_entity resp){
				if (!resp.is_cancelled()) {
					if (resp.success) {
						this->OnLoginSuccess(resp);
					}else{
						this->CallAfter([this]() { this->showLoginFrame(_("Login Failed")); });
					}
				}
			});
        }
    });

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

void MainFrame::TryLogin(const wxString &countryCode, const wxString &input, const wxString &password) {
    //UserModel::Instance().TryLogin(this,input,password);
	normal_login_source.cancel();
    auto & user_model = qingzhen::api::api_user_model::instance();
    utility::string_t _cc = wxString2CpprestString(countryCode);
    utility::string_t _ip = wxString2CpprestString(input);
    utility::string_t _pwd = wxString2CpprestString(password);
	normal_login_source = pplx::cancellation_token_source();
    pplx::task<response_entity> task = user_model.login(_cc, _ip, _pwd, normal_login_source);
    task.then([this](response_entity entity)->void {
        if(entity.success){
            this->OnLoginSuccess(entity);
        }else{
			if (entity.is_cancelled()) {
				return;
			}
            auto onFailed = [this]()-> void {
                //std::cout << "Login Success" << std::endl;
                this->showLoginFrame(_("Login Failed"));
            };
            this->CallAfter(onFailed);

        }
    });
}

void MainFrame::OnThreadEvent(wxThreadEvent &event) {
    if(this->terminated){
        return;
    }
    switch (event.GetInt()){
        case USER_LOGIN_RESPONSE:{
            SetStatusText(_("User login..."), 0);
            const response_entity &r = event.GetPayload<response_entity>();
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
            const response_entity &r = event.GetPayload<response_entity>();
            UserModel::Instance().Logout();
            showLoginFrame(_T("Login failed, please login again."));
            break;
        }

		case USER_REFRESH_RESPONSE: {
			
            break;
		}
        case PROGRAM_UPDATE_INFO:{
            const response_entity &r = event.GetPayload<response_entity>();
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
    globalTimer.Expire();
	check_login_source.cancel();
	normal_login_source.cancel();
	message_login_source.cancel();
}

void MainFrame::TryLoginByMessage(const wxString &phoneInfo, const wxString &code) {
    auto & user_model = qingzhen::api::api_user_model::instance();

    if(phoneInfo.empty()){
        return;
    }
    if(code.empty()){
        wxMessageBox(_("Code cannot be empty"),_("Code cannot be empty"));
        return;
    }
	message_login_source.cancel();
    utility::string_t _phoneInfo = wxString2CpprestString(phoneInfo);
    utility::string_t _code = wxString2CpprestString(code);
	message_login_source = pplx::cancellation_token_source();
    pplx::task<response_entity> task = user_model.login_by_message(_phoneInfo, _code, message_login_source);
    task.then([this](response_entity entity)->void {
        if(entity.success){
            this->OnLoginSuccess(entity);
        }else{
			if (entity.is_cancelled()) {
				return;
			}
            auto onFailed = [this]()-> void {
                this->showLoginFrame(_("Login Failed"));
            };
            this->CallAfter(onFailed);
        }
    });
}

void MainFrame::OnLoginSuccess(response_entity entity) {
    // std::cout << "Login Success" << std::endl;
    qingzhen::api::api_user_model::instance().set_user_info(entity.result);
    auto checkFunction = [this](){
		if (qingzhen::api::api_user_model::instance().is_user_login()) {
			// tick current page
			mainNotebook->RefreshTimerTick();
		}
		
    };
	mainNotebook->RefreshTimerTick();
    globalTimer.StartTimer(5000,checkFunction);
	this->CallAfter([this]() {
		this->UpdateUserInfo();
	});
    //
}

void MainFrame::FindConfigPath()
{
	auto config_path = wxStandardPaths::Get().GetUserDataDir() + wxFileName::GetPathSeparator() + wxT("qingzhenyun");
	//auto config_path = wxT("C:\\Program Files (x86)\\qingzhen");
	auto succ = false;
	if (!this->IsDirAvailable(config_path)) {
		config_path = wxStandardPaths::Get().GetAppDocumentsDir() + wxFileName::GetPathSeparator() + wxT("qingzhenyun");
		succ = this->IsDirAvailable(config_path);
	}
	else {
		succ = true;
	}
	if (!succ) {
		wxMessageBox(_("Cannot get config directory, your configuration may not saved."), _("Cannot get config directory"));
	}
	else {
		utility::string_t s = config_path;
		qingzhen::model::config_model::instance().set_config_path(s);
	}
}

bool MainFrame::IsDirAvailable(wxString config_path) {
	auto succ = false;
	//wxFileName config_path_name = wxFileName(config_path);
	if (!wxFileName::Exists(config_path, wxFILE_EXISTS_DIR)) {
		//wxMessageBox(config_path, "Disk readable!");
		succ = wxFileName::Mkdir(config_path, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
	}
	else {
		succ = wxFileName::IsDirReadable(config_path) && wxFileName::IsDirWritable(config_path);
	}
	return succ;
}

void MainFrame::UpdateUserInfo() {
	long d = qingzhen::util::get_current_linux_timestamp();
	time_t time = d;
	SetStatusText(wxString::Format(_("User info update at...%s"), ConvertTimeToDisplay(time), "%Y-%m-%d %H:%M"));
	auto user_info = qingzhen::api::api_user_model::instance().get_user_info();
	if (user_info.has_field(U("spaceUsed"))) {
		mainNotebook->UpdateSpaceCapacity(user_info.at(U("spaceUsed")).as_number().to_int64(), user_info.at(U("spaceCapacity")).as_number().to_int64());
	}
}