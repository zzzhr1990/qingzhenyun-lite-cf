//
// Created by zzzhr on 2018/11/3.
//

#ifndef QINGZHENYUN_LITE_ABOUTDIALOG_H
#define QINGZHENYUN_LITE_ABOUTDIALOG_H




/*!
 * Includes
 */

////@begin includes
#include "../../common/common_wx.h"
#include "wx/notebook.h"
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

#define SYMBOL_ABOUTDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_ABOUTDIALOG_TITLE _("AboutDialog")
#define SYMBOL_ABOUTDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_ABOUTDIALOG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * AboutDialog class declaration
 */

class AboutDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( AboutDialog )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    AboutDialog();
    AboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& caption = SYMBOL_ABOUTDIALOG_TITLE, const wxPoint& pos = SYMBOL_ABOUTDIALOG_POSITION, const wxSize& size = SYMBOL_ABOUTDIALOG_SIZE, long style = SYMBOL_ABOUTDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& caption = SYMBOL_ABOUTDIALOG_TITLE, const wxPoint& pos = SYMBOL_ABOUTDIALOG_POSITION, const wxSize& size = SYMBOL_ABOUTDIALOG_SIZE, long style = SYMBOL_ABOUTDIALOG_STYLE );

    /// Destructor
    ~AboutDialog();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin AboutDialog event handler declarations

////@end AboutDialog event handler declarations

////@begin AboutDialog member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end AboutDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin AboutDialog member variables
////@end AboutDialog member variables
};



#endif //QINGZHENYUN_LITE_ABOUTDIALOG_H
