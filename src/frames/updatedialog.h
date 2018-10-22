/////////////////////////////////////////////////////////////////////////////
// Name:        updatedialog.h
// Purpose:
// Author:
// Modified by:
// Created:     Fri 19 Oct 15:25:41 2018
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////

#ifndef _UPDATEDIALOG_H_
#define _UPDATEDIALOG_H_


/*!
 * Includes
 */

////@begin includes
#include "../common/common_wx.h"
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
#define SYMBOL_UPDATEDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_UPDATEDIALOG_TITLE _("Update Available")
#define SYMBOL_UPDATEDIALOG_SIZE wxSize(400, 300)
#define SYMBOL_UPDATEDIALOG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * UpdateDialog class declaration
 */

class UpdateDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( UpdateDialog )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    UpdateDialog();
    UpdateDialog( wxWindow* parent, const web::json::value& updateData, wxWindowID id = wxID_ANY, const wxString& caption = SYMBOL_UPDATEDIALOG_TITLE, const wxPoint& pos = SYMBOL_UPDATEDIALOG_POSITION, const wxSize& size = SYMBOL_UPDATEDIALOG_SIZE, long style = SYMBOL_UPDATEDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent,const web::json::value& updateData, wxWindowID id = wxID_ANY, const wxString& caption = SYMBOL_UPDATEDIALOG_TITLE, const wxPoint& pos = SYMBOL_UPDATEDIALOG_POSITION, const wxSize& size = SYMBOL_UPDATEDIALOG_SIZE, long style = SYMBOL_UPDATEDIALOG_STYLE );

    /// Destructor
    ~UpdateDialog();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls(const web::json::value& updateData);

////@begin UpdateDialog event handler declarations

////@end UpdateDialog event handler declarations

////@begin UpdateDialog member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end UpdateDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin UpdateDialog member variables
////@end UpdateDialog member variables
};

#endif
// _UPDATEDIALOG_H_
