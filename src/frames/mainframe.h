/////////////////////////////////////////////////////////////////////////////
// Name:        mainframe.h
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     01/09/2018 23:54:25
// RCS-ID:      
// Copyright:   for free
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _MAINFRAME_H_
#define _MAINFRAME_H_


/*!
 * Includes
 */
#include "../common/common_wx.h"
////@begin includes
#include "wx/frame.h"
#include "wx/toolbar.h"
#include "wx/statusbr.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
#include "./notebook/mainnotebook.h"
#include "../entity/response_entity.h"
#include "../util/simple_timer.h"

////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_MAINFRAME 10000
#define ID_TOOLBAR 10002
#define ID_USER_TOOL 10003
#define ID_SETTING_TOOL 10005
#define ID_STATUSBAR 10010
#define SYMBOL_MAINFRAME_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxMINIMIZE_BOX|wxMAXIMIZE_BOX|wxCLOSE_BOX
#define SYMBOL_MAINFRAME_TITLE _("MainFrame")
#define SYMBOL_MAINFRAME_IDNAME ID_MAINFRAME
#define SYMBOL_MAINFRAME_SIZE wxSize(800, 600)
#define SYMBOL_MAINFRAME_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * MainFrame class declaration
 */

class MainFrame: public wxFrame
{    
    DECLARE_CLASS( MainFrame )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    MainFrame();
    MainFrame( wxWindow* parent, wxWindowID id = SYMBOL_MAINFRAME_IDNAME, const wxString& caption = SYMBOL_MAINFRAME_TITLE, const wxPoint& pos = SYMBOL_MAINFRAME_POSITION, const wxSize& size = SYMBOL_MAINFRAME_SIZE, long style = SYMBOL_MAINFRAME_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_MAINFRAME_IDNAME, const wxString& caption = SYMBOL_MAINFRAME_TITLE, const wxPoint& pos = SYMBOL_MAINFRAME_POSITION, const wxSize& size = SYMBOL_MAINFRAME_SIZE, long style = SYMBOL_MAINFRAME_STYLE );

    /// Destructor
    ~MainFrame();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

	void OnToolClick(const wxCommandEvent & event);

////@begin MainFrame event handler declarations

////@end MainFrame event handler declarations

////@begin MainFrame member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );

    void OnClose(wxCloseEvent& event);
////@end MainFrame member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

    //void MainFrame::ShowLogWindow(wxCommandEvent& WXUNUSED(event));


    void DoOpenFiles(const wxArrayString & fileNames );

    void Terminate();




////@begin MainFrame member variables
private:
    MainNotebook* mainNotebook = nullptr;
    void showLoginFrame(const wxString& text);
    void OnWindowCreate(wxIdleEvent& event);
    void TryLogin(const wxString &countryCode, const wxString & input, const wxString & password);
    void TryLoginByMessage(const wxString &phoneInfo, const wxString & code);
    void OnLoginSuccess(const web::json::value &value, bool update = true);
    bool terminated = false;
    SimpleTimer globalTimer;
	void FindConfigPath();
	bool IsDirAvailable(wxString config_path);
	void UpdateUserInfo();
	time_t last_user_refresh_time;
	void CheckInterval();
	pplx::cancellation_token_source normal_login_source = pplx::cancellation_token_source();
	pplx::cancellation_token_source message_login_source = pplx::cancellation_token_source();
	pplx::cancellation_token_source check_login_source = pplx::cancellation_token_source();
	void OnMainMenu(wxCommandEvent& evt);
////@end MainFrame member variables
};

#endif
    // _MAINFRAME_H_
