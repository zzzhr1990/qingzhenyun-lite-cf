/////////////////////////////////////////////////////////////////////////////
// Name:        RemoteFileSelect.h
// Purpose:
// Author:
// Modified by:
// Created:     Tue 30 Oct 02:43:54 2018
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////

#ifndef _REMOTEFILESELECT_H_
#define _REMOTEFILESELECT_H_

#include "../../common/common_wx.h"
/*!
 * Includes
 */

////@begin includes
#include "wx/treectrl.h"
#include "wx/statline.h"
#include <pplx/pplxtasks.h>
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

#define SYMBOL_REMOTEFILESELECT_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_REMOTEFILESELECT_TITLE _("Remote file select")
#define SYMBOL_REMOTEFILESELECT_SIZE wxSize(400, 300)
#define SYMBOL_REMOTEFILESELECT_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * remotefileselect class declaration
 */

class RemoteFileSelect: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( RemoteFileSelect )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    RemoteFileSelect();
    RemoteFileSelect( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& caption = SYMBOL_REMOTEFILESELECT_TITLE, const wxPoint& pos = SYMBOL_REMOTEFILESELECT_POSITION, const wxSize& size = SYMBOL_REMOTEFILESELECT_SIZE, long style = SYMBOL_REMOTEFILESELECT_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& caption = SYMBOL_REMOTEFILESELECT_TITLE, const wxPoint& pos = SYMBOL_REMOTEFILESELECT_POSITION, const wxSize& size = SYMBOL_REMOTEFILESELECT_SIZE, long style = SYMBOL_REMOTEFILESELECT_STYLE );

    /// Destructor
    ~RemoteFileSelect();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin remotefileselect event handler declarations

////@end remotefileselect event handler declarations

////@begin remotefileselect member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end remotefileselect member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

private:
    pplx::cancellation_token_source get_path_cancellation = pplx::cancellation_token_source();
    void OnClose(wxCloseEvent& event);
////@begin remotefileselect member variables
////@end remotefileselect member variables
};

#endif
// _REMOTEFILESELECT_H_
