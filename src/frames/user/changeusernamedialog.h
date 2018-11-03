//
// Created by zzzhr on 2018/11/3.
//

#ifndef QINGZHENYUN_LITE_CHANGEUSERNAMEDIALOG_H
#define QINGZHENYUN_LITE_CHANGEUSERNAMEDIALOG_H


/*!
 * Includes
 */

////@begin includes
#include "../../common/common_wx.h"
#include "wx/statline.h"
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

#define SYMBOL_CHANGEUSERNAMEDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CHANGEUSERNAMEDIALOG_TITLE _("ChangeUsernameDialog")
#define SYMBOL_CHANGEUSERNAMEDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_CHANGEUSERNAMEDIALOG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * ChangeUsernameDialog class declaration
 */

class ChangeUsernameDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( ChangeUsernameDialog )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    ChangeUsernameDialog();
    ChangeUsernameDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& caption = SYMBOL_CHANGEUSERNAMEDIALOG_TITLE, const wxPoint& pos = SYMBOL_CHANGEUSERNAMEDIALOG_POSITION, const wxSize& size = SYMBOL_CHANGEUSERNAMEDIALOG_SIZE, long style = SYMBOL_CHANGEUSERNAMEDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& caption = SYMBOL_CHANGEUSERNAMEDIALOG_TITLE, const wxPoint& pos = SYMBOL_CHANGEUSERNAMEDIALOG_POSITION, const wxSize& size = SYMBOL_CHANGEUSERNAMEDIALOG_SIZE, long style = SYMBOL_CHANGEUSERNAMEDIALOG_STYLE );

    /// Destructor
    ~ChangeUsernameDialog();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin ChangeUsernameDialog event handler declarations

////@end ChangeUsernameDialog event handler declarations

////@begin ChangeUsernameDialog member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end ChangeUsernameDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

    wxString GetUserNameInput();

////@begin ChangeUsernameDialog member variables
private:
    wxTextCtrl* userNameInput = nullptr;

////@end ChangeUsernameDialog member variables
};

#endif //QINGZHENYUN_LITE_CHANGEUSERNAMEDIALOG_H
