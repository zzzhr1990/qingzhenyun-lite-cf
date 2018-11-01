/////////////////////////////////////////////////////////////////////////////
// Name:        addtaskresultdialog.h
// Purpose:
// Author:
// Modified by:
// Created:     Wed 31 Oct 23:02:11 2018
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////

#ifndef _ADDTASKRESULTDIALOG_H_
#define _ADDTASKRESULTDIALOG_H_


/*!
 * Includes
 */

////@begin includes
#include <cpprest/json.h>
#include "../../common/common_wx.h"
#include "wx/statline.h"
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

#define SYMBOL_ADDTASKRESULTDIALOG_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_ADDTASKRESULTDIALOG_TITLE _("AddTaskResultDialog")
#define SYMBOL_ADDTASKRESULTDIALOG_IDNAME ID_ADDTASKRESULTDIALOG
#define SYMBOL_ADDTASKRESULTDIALOG_SIZE wxSize(500, 400)
#define SYMBOL_ADDTASKRESULTDIALOG_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * AddTaskResultDialog class declaration
 */

class AddTaskResultDialog: public wxDialog
{
    DECLARE_DYNAMIC_CLASS( AddTaskResultDialog )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    AddTaskResultDialog();
    AddTaskResultDialog( wxWindow* parent,wxArrayString& checkLists, wxWindowID id = wxID_ANY, const wxString& caption = SYMBOL_ADDTASKRESULTDIALOG_TITLE, const wxPoint& pos = SYMBOL_ADDTASKRESULTDIALOG_POSITION, const wxSize& size = SYMBOL_ADDTASKRESULTDIALOG_SIZE, long style = SYMBOL_ADDTASKRESULTDIALOG_STYLE );

    /// Creation
    bool Create( wxWindow* parent,wxArrayString& checkLists, wxWindowID id = wxID_ANY, const wxString& caption = SYMBOL_ADDTASKRESULTDIALOG_TITLE, const wxPoint& pos = SYMBOL_ADDTASKRESULTDIALOG_POSITION, const wxSize& size = SYMBOL_ADDTASKRESULTDIALOG_SIZE, long style = SYMBOL_ADDTASKRESULTDIALOG_STYLE );

    /// Destructor
    ~AddTaskResultDialog();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls(wxArrayString& checkLists);

////@begin AddTaskResultDialog event handler declarations

////@end AddTaskResultDialog event handler declarations

////@begin AddTaskResultDialog member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end AddTaskResultDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

    utility::string_t GetItemsSelectString();

////@begin AddTaskResultDialog member variables
private:
    wxCheckListBox* mainCheckListBox = nullptr;
    void SelectAllItems(bool select);

    void OnCheckListBoxChanged(wxCommandEvent& evt);
////@end AddTaskResultDialog member variables
};

#endif
// _ADDTASKRESULTDIALOG_H_
