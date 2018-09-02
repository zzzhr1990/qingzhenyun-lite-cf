/////////////////////////////////////////////////////////////////////////////
// Name:        mainnotebook.h
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     02/09/2018 17:42:23
// RCS-ID:      
// Copyright:   for free
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _MAINNOTEBOOK_H_
#define _MAINNOTEBOOK_H_


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
class NyRemoteFilePanel;
class OfflineDownloadTaskPanel;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_NOTEBOOK 10012
#define ID_SYNC_TASK_PANEL 10025
#define SYMBOL_MAINNOTEBOOK_STYLE wxNB_DEFAULT
#define SYMBOL_MAINNOTEBOOK_IDNAME ID_NOTEBOOK
#define SYMBOL_MAINNOTEBOOK_SIZE wxDefaultSize
#define SYMBOL_MAINNOTEBOOK_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * MainNotebook class declaration
 */

class MainNotebook: public wxNotebook
{    
    DECLARE_DYNAMIC_CLASS( MainNotebook )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    MainNotebook();
    MainNotebook(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxBK_DEFAULT);

    /// Creation
    bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxBK_DEFAULT);

    /// Destructor
    ~MainNotebook();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin MainNotebook event handler declarations

////@end MainNotebook event handler declarations

////@begin MainNotebook member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end MainNotebook member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin MainNotebook member variables
////@end MainNotebook member variables
};

#endif
    // _MAINNOTEBOOK_H_
