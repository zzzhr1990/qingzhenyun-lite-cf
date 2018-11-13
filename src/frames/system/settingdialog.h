//
// Created by zzzhr on 2018/11/4.
//

#ifndef QINGZHENYUN_LITE_SETTINGDIALOG_H
#define QINGZHENYUN_LITE_SETTINGDIALOG_H

#include "../../common/common_wx.h"

/*!
 * Includes
 */

////@begin includes
#include "wx/spinctrl.h"
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
#define ID_SETTINGDIALOG 10000
#define ID_CHECKBOX2 10005
#define ID_CHECKBOX 10002
#define ID_SPINCTRL 10003
#define ID_SPINCTRL1 10004
#define ID_SPINCTRL2 10008
#define ID_CHOICE 10006
#define ID_BUTTON1 10007
#define ID_BUTTON 10001
#define SYMBOL_SETTINGDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_SETTINGDIALOG_TITLE _("SettingDialog")
#define SYMBOL_SETTINGDIALOG_IDNAME ID_SETTINGDIALOG
#define SYMBOL_SETTINGDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_SETTINGDIALOG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * SettingDialog class declaration
 */

class SettingDialog: public wxDialog
{
DECLARE_DYNAMIC_CLASS( SettingDialog )
DECLARE_EVENT_TABLE()

public:
    /// Constructors
    SettingDialog();
    SettingDialog( wxWindow* parent, wxWindowID id = SYMBOL_SETTINGDIALOG_IDNAME, const wxString& caption = SYMBOL_SETTINGDIALOG_TITLE, const wxPoint& pos = SYMBOL_SETTINGDIALOG_POSITION, const wxSize& size = SYMBOL_SETTINGDIALOG_SIZE, long style = SYMBOL_SETTINGDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_SETTINGDIALOG_IDNAME, const wxString& caption = SYMBOL_SETTINGDIALOG_TITLE, const wxPoint& pos = SYMBOL_SETTINGDIALOG_POSITION, const wxSize& size = SYMBOL_SETTINGDIALOG_SIZE, long style = SYMBOL_SETTINGDIALOG_STYLE );

    /// Destructor
    ~SettingDialog();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin SettingDialog event handler declarations

////@end SettingDialog event handler declarations

////@begin SettingDialog member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end SettingDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin SettingDialog member variables
////@end SettingDialog member variables
};


#endif //QINGZHENYUN_LITE_SETTINGDIALOG_H
