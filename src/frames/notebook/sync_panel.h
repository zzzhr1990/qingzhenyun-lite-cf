//
// Created by zzzhr on 2018/9/14.
//

#ifndef QINGZHENYUN_LITE_SYNC_PANEL_H
#define QINGZHENYUN_LITE_SYNC_PANEL_H

#include "wx/wxprec.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/listctrl.h"
#include "../../entity/response_entity.h"

class SyncPanel;

#define ID_VIEW_D_TASK_DETAIL 6421
#define ID_VIEW_D_OPEN_IN_EXPLORER 6422

class SyncPanel : public wxPanel {
DECLARE_DYNAMIC_CLASS( SyncPanel )
DECLARE_EVENT_TABLE()

public:
    //SyncPanel();
    SyncPanel();
    SyncPanel(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSUNKEN_BORDER|wxTAB_TRAVERSAL);
    /// Creation
    bool Create(wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxSUNKEN_BORDER|wxTAB_TRAVERSAL);

    /// Destructor
    ~SyncPanel();

    /// Initialises member variables
    void Init();

    static bool ShowToolTips();
    /// Creates the controls and sizers
    void CreateControls();

    ////@begin SyncPanel event handler declarations

    ////@end SyncPanel event handler declarations

    ////@begin SyncPanel member function declarations


    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
    /// D
    void RefreshData();

private:
    void OnSizeChanged( wxSizeEvent & event);
    bool drag = false;
    wxListCtrl* mainListCtrl = nullptr;
    void OnStartDrag( wxListEvent & event);
    void OnEndDrag( wxListEvent & event);
    void OnThreadEvent(wxThreadEvent & event);
    wxMenu* menu = nullptr;
    void OnItemRightClick(const wxListEvent & event);
    void OnTaskActivated(const wxListEvent &event);
    void OnCtrlListMenuClicked(const wxCommandEvent & event);
    void RefreshListData(const ResponseEntity& payload, const bool& updateAll = false);
    void RefreshBtnClicked(const wxCommandEvent & event);
    web::json::array currentList = web::json::value::array().as_array();
};


#endif //QINGZHENYUN_LITE_SYNC_PANEL_H
