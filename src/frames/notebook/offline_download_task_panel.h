/////////////////////////////////////////////////////////////////////////////
// Name:        offline_download_task_panel.h
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     02/09/2018 17:48:31
// RCS-ID:      
// Copyright:   for free
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _OFFLINE_DOWNLOAD_TASK_PANEL_H_
#define _OFFLINE_DOWNLOAD_TASK_PANEL_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/srchctrl.h"
#include "wx/listctrl.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class OfflineDownloadTaskPanel;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_OFFLINE_DOWNLOAD_PANEL 10024
#define ID_SEARCHCTRL 10009
#define ID_BITMAPBUTTON9 10027
#define ID_LISTCTRL1 10028
#define ID_CHECKBOX1 10019
#define ID_BITMAPBUTTON4 10020
#define ID_BITMAPBUTTON8 10031
#define ID_TEXTCTRL2 10032
#define ID_BITMAPBUTTON12 10036
#define SYMBOL_OFFLINEDOWNLOADTASKPANEL_STYLE wxSUNKEN_BORDER|wxTAB_TRAVERSAL
#define SYMBOL_OFFLINEDOWNLOADTASKPANEL_IDNAME ID_OFFLINE_DOWNLOAD_PANEL
#define SYMBOL_OFFLINEDOWNLOADTASKPANEL_SIZE wxDefaultSize
#define SYMBOL_OFFLINEDOWNLOADTASKPANEL_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * OfflineDownloadTaskPanel class declaration
 */

class OfflineDownloadTaskPanel: public wxPanel
{    
    DECLARE_DYNAMIC_CLASS( OfflineDownloadTaskPanel )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    OfflineDownloadTaskPanel();
    OfflineDownloadTaskPanel(wxWindow* parent, wxWindowID id = ID_OFFLINE_DOWNLOAD_PANEL, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSUNKEN_BORDER|wxTAB_TRAVERSAL);

    /// Creation
    bool Create(wxWindow* parent, wxWindowID id = ID_OFFLINE_DOWNLOAD_PANEL, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSUNKEN_BORDER|wxTAB_TRAVERSAL);

    /// Destructor
    ~OfflineDownloadTaskPanel();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin OfflineDownloadTaskPanel event handler declarations

////@end OfflineDownloadTaskPanel event handler declarations

////@begin OfflineDownloadTaskPanel member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end OfflineDownloadTaskPanel member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin OfflineDownloadTaskPanel member variables
////@end OfflineDownloadTaskPanel member variables
};

#endif
    // _OFFLINE_DOWNLOAD_TASK_PANEL_H_
