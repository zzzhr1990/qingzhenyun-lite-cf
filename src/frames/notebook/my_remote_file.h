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
#include "../userfile/add_directory_dialog.h"
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
#define ID_BITMAPBUTTON7 10023
#define ID_DOWNLOAD_FILE 6404

////@end control identifiers

#include "../video/videopreviewframe.h"
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

	void OnUserRemoteFileDClick(wxMouseEvent & event);

	void OnUserRemoteFileActivated(wxListEvent & event);

	void RefreshBtnClicked(wxCommandEvent & event);

	void NewDirectoryBtnClicked(wxCommandEvent & event);

	void ParentBtnClicked(wxCommandEvent & event);

	void PrevBtnClicked(wxCommandEvent & event);

	void NextBtnClicked(wxCommandEvent & event);

	void ResetCurrentPathDisplay();

	void OnPageInputDClick(wxMouseEvent & event);

	void OnPageInputKillFocus(wxFocusEvent & event);

	void RefreshListData(const ResponseEntity& res);
    void OnCtrlListMenuClicked(const wxCommandEvent &event);
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
	void UpdateSpaceCapacity(const long& spaceUsed = 0, const long& spaceCapacity = 0);

////@begin NyRemoteFilePanel member variables
private:
    wxListCtrl* mainListCtrl = nullptr;
    void OnSizeChanged(wxSizeEvent &event);
	void OnStartDrag(wxListEvent &event);
	void OnEndDrag(wxListEvent &event);
	bool drag = false;
	wxBitmapButton* prevPageBtn = nullptr;
	wxBitmapButton* nextPageBtn = nullptr;
	wxTextCtrl* currentPageInput = nullptr;
	wxTextCtrl* pathInput = nullptr;
	wxBitmapButton* parentBtn = nullptr;
	AddDirectoryDialog * addDirectoryDialog = nullptr;
    void OnItemRightClick(const wxListEvent & event);
	long spaceUsed = 0;
	long spaceCapacity = 0;
	wxStaticText* capacityText = nullptr;
	VideoPreviewFrame * videoPreviewFrame = nullptr;
    wxMenu* menu = nullptr;
////@end NyRemoteFilePanel member variables
};

#endif
    // _MY_REMOTE_FILE_H_
