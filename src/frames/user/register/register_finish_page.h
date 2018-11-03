//
// Created by zzzhr on 2018/11/2.
//

#include "../../../common/common_wx.h"
#include "wx/wizard.h"
#include <pplx/pplxtasks.h>
#ifndef QINGZHENYUN_LITE_REGISTER_FINISH_PAGE_H
#define QINGZHENYUN_LITE_REGISTER_FINISH_PAGE_H


/*!
 * WizardPage2 class declaration
 */

class WizardPage2: public wxWizardPageSimple
{

DECLARE_DYNAMIC_CLASS( WizardPage2 )
DECLARE_EVENT_TABLE()

public:
    /// Constructors
    WizardPage2();

    WizardPage2( wxWizard* parent );

    /// Creation
    bool Create( wxWizard* parent );

    /// Destructor
    ~WizardPage2();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin WizardPage2 event handler declarations

////@end WizardPage2 event handler declarations

////@begin WizardPage2 member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end WizardPage2 member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

    void RefreshName();

    void Terminate();

////@begin WizardPage2 member variables
private:
    wxTextCtrl* usernameTextCtrl = nullptr;
    bool success = false;
    void OnWizardPageChanging(wxWizardEvent &event);
    void ChangeNameBtnClicked(wxCommandEvent &event);
    pplx::cancellation_token_source change_name_cancellation_token_source = pplx::cancellation_token_source();
////@end WizardPage2 member variables
};

#endif //QINGZHENYUN_LITE_REGISTER_FINISH_PAGE_H
