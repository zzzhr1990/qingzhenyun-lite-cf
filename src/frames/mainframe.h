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

////@begin includes
#include "wx/frame.h"
#include "wx/toolbar.h"
#include "wx/statusbr.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class NyRemoteFilePanel;
class OfflineDownloadTaskPanel;
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

////@begin MainFrame event handler declarations

////@end MainFrame event handler declarations

////@begin MainFrame member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end MainFrame member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin MainFrame member variables
////@end MainFrame member variables
};

#endif
    // _MAINFRAME_H_
