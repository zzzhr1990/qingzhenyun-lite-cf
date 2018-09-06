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

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

 ////@begin includes
#include "wx/imaglist.h"
////@end includes

////@begin includes
#include "wx/srchctrl.h"
#include "wx/listctrl.h"
#include "../../entity/response_entity.h"
#include "../../frames/offline/add_offline_task.h"
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

#define SYMBOL_OFFLINEDOWNLOADTASKPANEL_STYLE wxSUNKEN_BORDER|wxTAB_TRAVERSAL
#define SYMBOL_OFFLINEDOWNLOADTASKPANEL_IDNAME ID_OFFLINE_DOWNLOAD_PANEL
#define SYMBOL_OFFLINEDOWNLOADTASKPANEL_SIZE wxDefaultSize
#define SYMBOL_OFFLINEDOWNLOADTASKPANEL_POSITION wxDefaultPosition
#define ID_COPY_URL_TO_CLIP 6401
#define ID_VIEW_TASK_DETAIL 6402
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
    OfflineDownloadTaskPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSUNKEN_BORDER|wxTAB_TRAVERSAL);

    /// Creation
    bool Create(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSUNKEN_BORDER|wxTAB_TRAVERSAL);

    /// Destructor
    ~OfflineDownloadTaskPanel();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin OfflineDownloadTaskPanel event handler declarations

////@end OfflineDownloadTaskPanel event handler declarations

////@begin OfflineDownloadTaskPanel member function declarations

	

	void OnSizeChanged( wxSizeEvent & event);

	void OnUserRemoteTaskActivated(const wxListEvent & event);

	/// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );

	void OnPageInputDClick(const wxMouseEvent & event);

	void RefreshBtnClicked(const wxCommandEvent & event);
	
////@end OfflineDownloadTaskPanel member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();
	void RefreshData();

	

////@begin OfflineDownloadTaskPanel member variables
////@end OfflineDownloadTaskPanel member variables
private:
	void OnCtrlListMenuClicked(const wxCommandEvent & event);
	void OnItemRightClick(const wxListEvent & event);
	void OnPageInputKillFocus(const wxFocusEvent & event);
	void OnThreadEvent(wxThreadEvent & event);
	void RefreshListData(const ResponseEntity & payload);
	void PrevBtnClicked(const wxCommandEvent & event);
	void StartDownloadUrl(const wxString & str);
	void NextBtnClicked(const wxCommandEvent & event);
	void NewTaskBtnClicked(const wxCommandEvent & event);
	void ResetCurrentPathDisplay();
	void OnStartDrag( wxListEvent & event);
	void OnEndDrag( wxListEvent & event);
	//	void RefreshListData(const ResponseEntity & payload);
	
	bool drag = false;
	wxListCtrl* mainListCtrl = nullptr;
	wxBitmapButton* prevPageBtn = nullptr;
	wxBitmapButton* nextPageBtn = nullptr;
	wxTextCtrl* currentPageInput = nullptr;
	AddOfflineTask* addOfflineTask = nullptr;
	wxString currentDownloadPath = _T("/");
	wxMenu* menu = nullptr;
};

#endif
    // _OFFLINE_DOWNLOAD_TASK_PANEL_H_
