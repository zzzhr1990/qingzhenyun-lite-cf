/////////////////////////////////////////////////////////////////////////////
// Name:        loginframe.h
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     02/09/2018 17:17:00
// RCS-ID:      
// Copyright:   for free
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _LOGINFRAME_H_
#define _LOGINFRAME_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/notebook.h"
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
#define ID_LOGINFRAME 10000
#define ID_NOTEBOOK 10001
#define ID_PANEL 10002
#define ID_TEXTCTRL1 10004
#define ID_TEXTCTRL 10003
#define SYMBOL_LOGINFRAME_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_LOGINFRAME_TITLE _("LoginFrame")
#define SYMBOL_LOGINFRAME_IDNAME ID_LOGINFRAME
#define SYMBOL_LOGINFRAME_SIZE wxSize(400, 300)
#define SYMBOL_LOGINFRAME_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * LoginFrame class declaration
 */

class LoginFrame: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( LoginFrame )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    LoginFrame();
    LoginFrame( wxWindow* parent, wxWindowID id = SYMBOL_LOGINFRAME_IDNAME, const wxString& caption = SYMBOL_LOGINFRAME_TITLE, const wxPoint& pos = SYMBOL_LOGINFRAME_POSITION, const wxSize& size = SYMBOL_LOGINFRAME_SIZE, long style = SYMBOL_LOGINFRAME_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_LOGINFRAME_IDNAME, const wxString& caption = SYMBOL_LOGINFRAME_TITLE, const wxPoint& pos = SYMBOL_LOGINFRAME_POSITION, const wxSize& size = SYMBOL_LOGINFRAME_SIZE, long style = SYMBOL_LOGINFRAME_STYLE );

    /// Destructor
    ~LoginFrame();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin LoginFrame event handler declarations

////@end LoginFrame event handler declarations

////@begin LoginFrame member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end LoginFrame member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin LoginFrame member variables
////@end LoginFrame member variables
};

#endif
    // _LOGINFRAME_H_
