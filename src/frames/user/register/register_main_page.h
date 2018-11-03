//
// Created by zzzhr on 2018/11/2.
//

#ifndef QINGZHENYUN_LITE_REGISTER_MAIN_PAGE_H
#define QINGZHENYUN_LITE_REGISTER_MAIN_PAGE_H

#include <cpprest/details/basic_types.h>
#include <pplx/pplxtasks.h>
#include "../../../common/common_wx.h"
#include "wx/wizard.h"
#include "../../../util/simple_timer.h"

class WizardPage1: public wxWizardPageSimple
{
DECLARE_DYNAMIC_CLASS( WizardPage1 )
DECLARE_EVENT_TABLE()

public:
    /// Constructors
    WizardPage1();

    WizardPage1( wxWizard* parent );

    /// Creation
    bool Create( wxWizard* parent );

    /// Destructor
    ~WizardPage1();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin WizardPage1 event handler declarations

////@end WizardPage1 event handler declarations

////@begin WizardPage1 member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end WizardPage1 member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

    void Terminate();

////@begin WizardPage1 member variables
private:
    wxChoice* messageCountryCodeSelection = nullptr;
    utility::string_t phoneInfo = utility::string_t();
    wxTextCtrl* messagePhoneInput = nullptr;
    pplx::cancellation_token_source send_message_cancellation_token_source = pplx::cancellation_token_source();
    time_t last_send_message_time = 0;
    void ResetTimerClick();
    void SendMessageButtonClicked(wxCommandEvent &event);
    wxButton* sendMessageButton = nullptr;
    SimpleTimer timer = SimpleTimer();
    void SendTextMessage();
    wxTextCtrl* messageCodeInput = nullptr;
    wxTextCtrl* userPasswordInput = nullptr;
    void OnWizardPageChanging(wxWizardEvent& event);
    bool success = false;
    void DoRegister(wxString& code,wxString &password);
////@end WizardPage1 member variables
};

#endif //QINGZHENYUN_LITE_REGISTER_MAIN_PAGE_H
