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
#include <cpprest/details/basic_types.h>
#include <cpprest/json.h>
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
#define SYMBOL_REMOTEFILESELECT_SIZE wxSize(600, 400)
#define SYMBOL_REMOTEFILESELECT_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * remotefileselect class declaration
 */

class simple_directory_info : public wxTreeItemData {
public:
    explicit simple_directory_info(utility::string_t path) : wxTreeItemData() {
        this->path = std::move(path);
    }

    simple_directory_info(utility::string_t &path, utility::string_t &name) : wxTreeItemData() {
        //this->path = std::move(path);
        //this->info = info;
        //this->list = list;
        this->path = path;
        this->name = name;
        this->inited = false;
    }

    bool get_inited() {
        return inited;
    }

    void set_inited(bool init) {
        this->inited = init;
    }

    utility::string_t get_path(){
        return this->path;
    }

    utility::string_t get_name(){
        return this->name;
    }

private:
    utility::string_t path;
    utility::string_t name;
    bool inited = false;
};


class RemoteFileSelect: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( RemoteFileSelect )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    RemoteFileSelect();

    explicit RemoteFileSelect( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& caption = SYMBOL_REMOTEFILESELECT_TITLE, const wxPoint& pos = SYMBOL_REMOTEFILESELECT_POSITION, const wxSize& size = SYMBOL_REMOTEFILESELECT_SIZE, long style = SYMBOL_REMOTEFILESELECT_STYLE );

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
    wxString GetUserInput();

private:
    pplx::cancellation_token_source get_path_cancellation = pplx::cancellation_token_source();
    void EndModal(int retCode) override;
    wxTreeCtrl* mainTreeCtrl = nullptr;
    void AddRootDirectory();
    void OnTreeExpanding(wxTreeEvent &evt);
    // OnTreeSelectChanged
    void OnTreeSelectChanged(wxTreeEvent &evt);
	void OnTreeSelectActivated(wxTreeEvent & evt);
    void OnDirectoryDataReceived(web::json::value info, wxTreeItemId selection);
    void OnCreateDirectoryBtnClicked(wxCommandEvent &event);

    wxTextCtrl* pathInput = nullptr;
////@begin remotefileselect member variables
////@end remotefileselect member variables
};

#endif
// _REMOTEFILESELECT_H_
