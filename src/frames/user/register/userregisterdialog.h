/////////////////////////////////////////////////////////////////////////////
// Name:        user_register_dialog.h
// Purpose:
// Author:
// Modified by:
// Created:     Thu  1 Nov 18:04:38 2018
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////

#ifndef _USER_REGISTER_DIALOG_H_
#define _USER_REGISTER_DIALOG_H_


/*!
 * Includes
 */
#include "../../../common/common_wx.h"
////@begin includes
#include <wx/wizard.h>
#include <cpprest/details/basic_types.h>
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
/*
class WizardPage3;
class WizardPage4;
class WizardPage5;
class WizardPage6;
 */
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_USERREGISTERDIALOG 10000

////@end control identifiers


/*!
 * UserRegisterDialog class declaration
 */

class UserRegisterDialog: public wxWizard
{
DECLARE_DYNAMIC_CLASS( UserRegisterDialog )
DECLARE_EVENT_TABLE()

public:
    /// Constructors
    UserRegisterDialog();
    UserRegisterDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition );

    /// Destructor
    ~UserRegisterDialog();

    /// Initialises member variables
    //void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin UserRegisterDialog event handler declarations

////@end UserRegisterDialog event handler declarations

////@begin UserRegisterDialog member function declarations

    /// Runs the wizard

    bool Run();

    bool GotoLastPage();

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end UserRegisterDialog member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();


    void LockForward(bool lock = true);

    void LockBack(bool lock = true);

    void RefreshName();

    void OnRegisterSuccess();
    bool IsRegisterSuccess();

    void Terminate();

////@begin UserRegisterDialog member variables
private:
    wxWizardPage * firstPage = nullptr;
    wxWizardPage * lastPage = nullptr;
    wxWizardPage * mainPage = nullptr;
    bool success = false;

////@end UserRegisterDialog member variables
};

#endif
// _USER_REGISTER_DIALOG_H_
