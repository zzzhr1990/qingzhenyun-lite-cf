/////////////////////////////////////////////////////////////////////////////
// Name:        userdialog.h
// Purpose:
// Author:
// Modified by:
// Created:     Fri 19 Oct 15:02:06 2018
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////

#ifndef _USERDIALOG_H_
#define _USERDIALOG_H_


/*!
 * Includes
 */

////@begin includes
#include "../../common/common_wx.h"
#include "wx/notebook.h"
#include "wx/statline.h"
#include <cpprest/http_client.h>
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_MY_ACCOUNT wxID_ANY
#define ID_LOGIN_NOTEBOOK wxID_ANY
#define ID_MY_ACCOUNT_PANEL wxID_ANY
#define ID_TEXTCTRL wxID_ANY
#define CHANGE_USER_ID wxID_ANY
#define ID_QUOTA_PANEL wxID_ANY

#define ID_SECURITY wxID_ANY
#define SYMBOL_USERDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_USERDIALOG_TITLE _("UserDialog")
#define SYMBOL_USERDIALOG_IDNAME ID_MY_ACCOUNT
#define SYMBOL_USERDIALOG_SIZE wxSize(500, 330)
#define SYMBOL_USERDIALOG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * UserDialog class declaration
 */

class UserDialog: public wxDialog
{
DECLARE_DYNAMIC_CLASS( UserDialog )
DECLARE_EVENT_TABLE()

public:
    /// Constructors
    UserDialog();
    UserDialog( wxWindow* parent, const web::json::value & userData, wxWindowID id = SYMBOL_USERDIALOG_IDNAME, const wxString& caption = SYMBOL_USERDIALOG_TITLE, const wxPoint& pos = SYMBOL_USERDIALOG_POSITION, const wxSize& size = SYMBOL_USERDIALOG_SIZE, long style = SYMBOL_USERDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent,const web::json::value & userData, wxWindowID id = SYMBOL_USERDIALOG_IDNAME, const wxString& caption = SYMBOL_USERDIALOG_TITLE, const wxPoint& pos = SYMBOL_USERDIALOG_POSITION, const wxSize& size = SYMBOL_USERDIALOG_SIZE, long style = SYMBOL_USERDIALOG_STYLE );

    /// Destructor
    ~UserDialog();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls(const web::json::value & userData);

////@begin UserDialog event handler declarations

////@end UserDialog event handler declarations

////@begin UserDialog member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end UserDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

    bool GetContinueLogin() {
        return continueLogin;
    }

////@begin UserDialog member variables
private:
    void EndModal(int retCode) override;
    void LogoutBtnClicked(wxCommandEvent &event);
    bool continueLogin = false;
	pplx::cancellation_token_source logout_cancel_source = pplx::cancellation_token_source();
	void OnClose(wxCloseEvent& event);
////@end UserDialog member variables
};

#endif
// _USERDIALOG_H_
