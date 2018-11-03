//
// Created by zzzhr on 2018/11/2.
//

#ifndef QINGZHENYUN_LITE_AGREEMENT_PAGE_H
#define QINGZHENYUN_LITE_AGREEMENT_PAGE_H

#include "../../../common/common_wx.h"
#include "wx/wizard.h"

class WizardPage: public wxWizardPageSimple
{
DECLARE_DYNAMIC_CLASS( WizardPage )
DECLARE_EVENT_TABLE()

public:
    /// Constructors
    WizardPage();

    WizardPage( wxWizard* parent );

    /// Creation
    bool Create( wxWizard* parent );

    /// Destructor
    ~WizardPage();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin WizardPage event handler declarations

////@end WizardPage event handler declarations

////@begin WizardPage member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end WizardPage member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

    bool TransferDataFromWindow() override;
////@begin WizardPage member variables
private:
    wxCheckBox* agreeCheckBox = nullptr;
////@end WizardPage member variables
};


#endif //QINGZHENYUN_LITE_AGREEMENT_PAGE_H
