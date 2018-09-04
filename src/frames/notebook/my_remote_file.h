/////////////////////////////////////////////////////////////////////////////
// Name:        my_remote_file.h
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     02/09/2018 17:46:18
// RCS-ID:      
// Copyright:   for free
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _MY_REMOTE_FILE_H_
#define _MY_REMOTE_FILE_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/listctrl.h"
#include "../../entity/response_entity.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class MyRemoteFilePanel;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_MY_REMOTE_FILE_PANEL 10011
#define ID_TEXTCTRL 10013
#define ID_BITMAPBUTTON 10014
#define ID_BITMAPBUTTON5 10026
#define ID_BITMAPBUTTON1 10015
#define ID_BITMAPBUTTON23 10001
#define ID_LISTCTRL 10016
#define ID_CHECKBOX 10008
#define ID_BITMAPBUTTON2 10017
#define ID_BITMAPBUTTON3 10018
#define ID_BITMAPBUTTON6 10021
#define ID_TEXTCTRL1 10022
#define ID_BITMAPBUTTON7 10023
#define SYMBOL_NYREMOTEFILEPANEL_STYLE wxSUNKEN_BORDER|wxTAB_TRAVERSAL
#define SYMBOL_NYREMOTEFILEPANEL_IDNAME ID_MY_REMOTE_FILE_PANEL
#define SYMBOL_NYREMOTEFILEPANEL_SIZE wxDefaultSize
#define SYMBOL_NYREMOTEFILEPANEL_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * NyRemoteFilePanel class declaration
 */

class MyRemoteFilePanel: public wxPanel
{    
    DECLARE_DYNAMIC_CLASS( MyRemoteFilePanel )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    MyRemoteFilePanel();
    MyRemoteFilePanel(wxWindow* parent, wxWindowID id = ID_MY_REMOTE_FILE_PANEL, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSUNKEN_BORDER|wxTAB_TRAVERSAL);

    /// Creation
    bool Create(wxWindow* parent, wxWindowID id = ID_MY_REMOTE_FILE_PANEL, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSUNKEN_BORDER|wxTAB_TRAVERSAL);

    /// Destructor
    ~MyRemoteFilePanel();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

    void RefreshData();

    void OnThreadEvent(wxThreadEvent& event);

    void RefreshListData(const ResponseEntity& res);
////@begin NyRemoteFilePanel event handler declarations

////@end NyRemoteFilePanel event handler declarations

////@begin NyRemoteFilePanel member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end NyRemoteFilePanel member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin NyRemoteFilePanel member variables
private:
    wxListCtrl* mainListCtrl = nullptr;
    void OnSizeChanged(wxSizeEvent &event);
////@end NyRemoteFilePanel member variables
};

#endif
    // _MY_REMOTE_FILE_H_
