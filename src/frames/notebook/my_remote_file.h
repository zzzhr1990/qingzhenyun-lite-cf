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
#include "../../common/common_wx.h"
#include "wx/listctrl.h"
#include "../../entity/response_entity.h"
#include "../file/add_directory_dialog.h"
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
#define ID_BITMAPBUTTON6 10021
#define ID_BITMAPBUTTON7 10023
#define ID_DOWNLOAD_FILE 6404
#define ID_DELETE_FILE 6405
#define ID_VIEW_FILE_DETAIL 6406

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
    ~MyRemoteFilePanel() override;

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

    void RefreshData(const bool& force = true);


	void OnUserRemoteFileDClick(wxMouseEvent & event);

	void OnUserRemoteFileActivated(wxListEvent & event);

	void RefreshBtnClicked(wxCommandEvent & event);

	void NewDirectoryBtnClicked(wxCommandEvent & event);



	void PrevBtnClicked(wxCommandEvent & event);

	void NextBtnClicked(wxCommandEvent & event);

	void ResetCurrentPathDisplay();

	void OnPageInputDClick(wxMouseEvent & event);

	void OnPageInputKillFocus(wxFocusEvent & event);

    void OnCtrlListMenuClicked(const wxCommandEvent &event);

	void DoOpenFiles(const wxArrayString &fileNames);
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
	void UpdateSpaceCapacity(const long long& spaceUsed = 0, const long long& spaceCapacity = 0);

	void Terminate();

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
	wxStaticText* capacityText = nullptr;
	//VideoPreviewFrame * videoPreviewFrame = nullptr;
    wxMenu* menu = nullptr;
	bool waitPage = false;
	VideoPreviewFrame* previewFrame = nullptr;

	void OnCurrentPageDataReceived(response_entity entity);

	void RefreshDataGridDisplay();

	void ParentBtnClicked(wxCommandEvent & event);

	void OnMoveBtnClicked(wxCommandEvent & event);


	// cancellation_token_source
	long last_list_size = 0;
	pplx::cancellation_token_source file_refresh_cancellation = pplx::cancellation_token_source();
    pplx::cancellation_token_source create_cancellation = pplx::cancellation_token_source();

    void GotoPath(utility::string_t path = _XPLATSTR(""), const int &page = -1,
                  const int &pageSize = -1, const int &type = -1);
    void GotoUUID(utility::string_t uuid = _XPLATSTR(""), const int &page = -1,
                  const int &pageSize = -1, const int &type = -1);

    void SelectAllItems(bool select);

    void OnCheckListBoxChanged(wxCommandEvent & evt);
////@end NyRemoteFilePanel member variables
};

#endif
    // _MY_REMOTE_FILE_H_
