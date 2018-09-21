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
class MyRemoteFilePanel;
class OfflineDownloadTaskPanel;
class SyncPanel;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#include "../../util/simple_timer.h"
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

    void DoOpenFiles(const wxArrayString &fileNames);

////@begin MainNotebook event handler declarations

////@end MainNotebook event handler declarations

////@begin MainNotebook member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end MainNotebook member function declarations

	void OnThreadEvent(wxThreadEvent & event);

	/// Should we show tooltips?
    static bool ShowToolTips();

    void RefreshCurrentPage(int selection = -1);

	void UpdateSpaceCapacity(const long long & spaceUsed, const long long & spaceCapacity);

private:
	void OnNoteBookChange(wxBookCtrlEvent & event);
	
    MyRemoteFilePanel* myRemoteFilePanel = nullptr;
	OfflineDownloadTaskPanel* offlineDownloadTaskPanel = nullptr;
    SyncPanel* syncPanel = nullptr;
	bool inited = false;
	SimpleTimer timer;
	void TimerTick();
////@begin MainNotebook member variables
////@end MainNotebook member variables
};

#endif
    // _MAINNOTEBOOK_H_
