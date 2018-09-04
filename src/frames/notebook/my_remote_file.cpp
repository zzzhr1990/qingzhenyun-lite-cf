/////////////////////////////////////////////////////////////////////////////
// Name:        my_remote_file.cpp
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     02/09/2018 17:46:18
// RCS-ID:      
// Copyright:   for free
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
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

#include "my_remote_file.h"
#include "../../model/remote_file_model.h"

////@begin XPM images
#include "../../resources/refresh.xpm"
#include "../../resources/up_level.xpm"
#include "../../resources/search.xpm"
#include "../../resources/new_directory.xpm"
#include "../../resources/delete_trash.xpm"
#include "../../resources/copy.xpm"
#include "../../resources/left_btn.xpm"
#include "../../resources/right_btn.xpm"
#include "../../util/common_util.h"
////@end XPM images


/*
 * MyRemoteFilePanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( MyRemoteFilePanel, wxPanel )


/*
 * MyRemoteFilePanel event table definition
 */

BEGIN_EVENT_TABLE( MyRemoteFilePanel, wxPanel )

////@begin NyRemoteFilePanel event table entries
////@end NyRemoteFilePanel event table entries

END_EVENT_TABLE()


/*
 * MyRemoteFilePanel constructors
 */

MyRemoteFilePanel::MyRemoteFilePanel()
{
    Init();
}

MyRemoteFilePanel::MyRemoteFilePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{
    Init();
    Create(parent, id, pos, size, style);
}


/*
 * MyRemoteFilePanel creator
 */

bool MyRemoteFilePanel::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{
////@begin NyRemoteFilePanel creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxPanel::Create(parent, id, pos, size, style);
    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end NyRemoteFilePanel creation
    return true;
}


/*
 * MyRemoteFilePanel destructor
 */

MyRemoteFilePanel::~MyRemoteFilePanel()
{
////@begin NyRemoteFilePanel destruction
////@end NyRemoteFilePanel destruction
}


/*
 * Member initialisation
 */

void MyRemoteFilePanel::Init()
{
////@begin NyRemoteFilePanel member initialisation
////@end NyRemoteFilePanel member initialisation
}


/*
 * Control creation for MyRemoteFilePanel
 */

void MyRemoteFilePanel::CreateControls()
{    
////@begin NyRemoteFilePanel content construction
    MyRemoteFilePanel* itemPanel1 = this;

    this->SetName(wxT("MyRemoteFiles"));
    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxGROW, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemPanel1, wxID_STATIC, _("Current Path"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl5 = new wxTextCtrl( itemPanel1, ID_TEXTCTRL, _("/"), wxDefaultPosition, wxDefaultSize, 0 );
    itemTextCtrl5->Enable(false);
    itemBoxSizer3->Add(itemTextCtrl5, 1, wxGROW|wxALL, 5);

    wxBitmapButton* itemBitmapButton6 = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON, itemPanel1->GetBitmapResource(wxT("refresh.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBitmapButton6->SetHelpText(_("Refresh"));
    if (MyRemoteFilePanel::ShowToolTips())
        itemBitmapButton6->SetToolTip(_("Refresh"));
    itemBoxSizer3->Add(itemBitmapButton6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton2 = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON5, itemPanel1->GetBitmapResource(wxT("up_level.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBitmapButton2->SetHelpText(_("Refresh"));
    if (MyRemoteFilePanel::ShowToolTips())
        itemBitmapButton2->SetToolTip(_("Refresh"));
    itemBoxSizer3->Add(itemBitmapButton2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton7 = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON1, itemPanel1->GetBitmapResource(wxT("search.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBitmapButton7->SetHelpText(_("Search"));
    if (MyRemoteFilePanel::ShowToolTips())
        itemBitmapButton7->SetToolTip(_("Search"));
    itemBoxSizer3->Add(itemBitmapButton7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton1 = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON23, itemPanel1->GetBitmapResource(wxT("new_directory.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBitmapButton1->SetHelpText(_("New directory"));
    if (MyRemoteFilePanel::ShowToolTips())
        itemBitmapButton1->SetToolTip(_("New directory"));
    itemBoxSizer3->Add(itemBitmapButton1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    mainListCtrl = new wxListCtrl( itemPanel1, ID_LISTCTRL, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT );
    itemBoxSizer2->Add(mainListCtrl, 1, wxGROW|wxALL, 5);
    mainListCtrl->AppendColumn(_("Type"),wxLIST_FORMAT_CENTER);
	mainListCtrl->AppendColumn(_("Filename"),wxLIST_FORMAT_CENTER,120);
    mainListCtrl->AppendColumn(_("FileSize"),wxLIST_FORMAT_CENTER);
    mainListCtrl->AppendColumn(_("FileType"),wxLIST_FORMAT_CENTER);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer4, 0, wxGROW, 5);

    wxCheckBox* itemCheckBox1 = new wxCheckBox( itemPanel1, ID_CHECKBOX, _("Select All"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox1->SetValue(false);
    itemBoxSizer4->Add(itemCheckBox1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText2 = new wxStaticText( itemPanel1, wxID_STATIC, _("Selected:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemStaticText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton5 = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON2, itemPanel1->GetBitmapResource(wxT("delete_trash.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBitmapButton5->SetHelpText(_("Delete"));
    if (MyRemoteFilePanel::ShowToolTips())
        itemBitmapButton5->SetToolTip(_("Delete Select Files"));
    itemBoxSizer4->Add(itemBitmapButton5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton8 = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON3, itemPanel1->GetBitmapResource(wxT("copy.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBoxSizer4->Add(itemBitmapButton8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer6 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer4->Add(itemBoxSizer6, 1, wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( itemPanel1, wxID_STATIC, _("0 / 1024 MB"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer6->Add(itemStaticText7, 0, wxALIGN_CENTER_HORIZONTAL, 5);

    wxBitmapButton* prevPageBtn = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON6, itemPanel1->GetBitmapResource(wxT("left_btn.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBoxSizer4->Add(prevPageBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxTextCtrl* itemTextCtrl13 = new wxTextCtrl( itemPanel1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer4->Add(itemTextCtrl13, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* nextPageBtn = new wxBitmapButton( itemPanel1, ID_BITMAPBUTTON7, itemPanel1->GetBitmapResource(wxT("right_btn.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBoxSizer4->Add(nextPageBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    this->Bind(wxEVT_THREAD,&MyRemoteFilePanel::OnThreadEvent,this);
    mainListCtrl->Bind(wxEVT_SIZE,&MyRemoteFilePanel::OnSizeChanged,this);
////@end NyRemoteFilePanel content construction
}


/*
 * Should we show tooltips?
 */

bool MyRemoteFilePanel::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap MyRemoteFilePanel::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin NyRemoteFilePanel bitmap retrieval
    wxUnusedVar(name);
    if (name == wxT("refresh.xpm"))
    {
        wxBitmap bitmap(refresh_xpm);
        return bitmap;
    }
    else if (name == wxT("up_level.xpm"))
    {
        wxBitmap bitmap(up_level_xpm);
        return bitmap;
    }
    else if (name == wxT("search.xpm"))
    {
        wxBitmap bitmap(search_xpm);
        return bitmap;
    }
    else if (name == wxT("new_directory.xpm"))
    {
        wxBitmap bitmap(new_directory_xpm);
        return bitmap;
    }
    else if (name == wxT("delete_trash.xpm"))
    {
        wxBitmap bitmap(delete_trash_xpm);
        return bitmap;
    }
    else if (name == wxT("copy.xpm"))
    {
        wxBitmap bitmap(copy_xpm);
        return bitmap;
    }
    else if (name == wxT("left_btn.xpm"))
    {
        wxBitmap bitmap(left_btn_xpm);
        return bitmap;
    }
    else if (name == wxT("right_btn.xpm"))
    {
        wxBitmap bitmap(right_btn_xpm);
        return bitmap;
    }
    return wxNullBitmap;
////@end NyRemoteFilePanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon MyRemoteFilePanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin NyRemoteFilePanel icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end NyRemoteFilePanel icon retrieval
}

void MyRemoteFilePanel::RefreshData() {
    auto & fileModel = RemoteFileModel::Instance();
    fileModel.GetPage(this);
}

void MyRemoteFilePanel::OnThreadEvent(wxThreadEvent &event) {
    // D
    switch (event.GetInt()){
        case USER_REMOTE_FILE_PAGE_DATA:
        {
            auto payload = event.GetPayload<ResponseEntity>();
            RefreshListData(payload);
            break;
        }
        default:
            event.Skip();
    }
}

void MyRemoteFilePanel::RefreshListData(const ResponseEntity& payload) {
    if(payload.code == U("FILE_NOT_FOUND")){
        wxMessageBox( _("Destination invalid.\nThere parent directory not found.\nAuto goto root dir."), _("Cannot go to directory"), wxICON_INFORMATION);
        RemoteFileModel::Instance().GetPage(this,U("/"),1);
        return;
    }
    web::json::array list =  payload.result.at(U("list")).as_array();
    // model->AppendItem( data ,1);
    auto model = &RemoteFileModel::Instance();
    auto dirInfo = payload.result.at(U("info"));
    auto currentPath = dirInfo.at(U("path")).as_string();
    auto currentId = dirInfo.at(U("uuid")).as_string();
    auto parent = dirInfo.at(U("parent")).as_string();
    auto currentPage = payload.result.at(U("page")).as_integer();
    auto currentPageSize = payload.result.at(U("pageSize")).as_integer();
    auto totalPage = payload.result.at(U("totalPage")).as_integer();
    model->UpdateCurrentLocation(currentPath, currentId, currentPage, currentPageSize, totalPage, parent);
    /*
     * "Type" --- "Filename" --- "FileSize" --- "FileType"
     */
    long cur = 0;
    //long index = 0;
    mainListCtrl->Hide();
    for(const auto& i : list){
        // create item
        wxListItem itemCol;
        itemCol.SetId(cur);
        // col 1 type
        itemCol.SetColumn(0);
        if(i.at(U("type")).as_integer() == 1){
            itemCol.SetText(_T("+"));
        }else{
            itemCol.SetText(_T("-"));
        }
        mainListCtrl->InsertItem(itemCol);
        // col1 filename

        mainListCtrl->SetItem(cur, 1, i.at(U("name")).as_string());
        // col 2 file size
        mainListCtrl->SetItem(cur, 2, ConvertSizeToDisplay(i.at(U("size")).as_number().to_int64()));
        // col3 mime
        mainListCtrl->SetItem(cur, 3, i.at(U("mime")).as_string());

        //mainListCtrl->GetColumnWidth()
        /*
        // col3 size
        wxListItem itemCol2;
        itemCol2.SetId(cur);
        itemCol2.SetColumn(2);
        itemCol2.SetText(_T("0B"));
        mainListCtrl->InsertItem(itemCol2);
        //mainListCtrl->InsertItem(itemCol);
        //itemCol.SetColumn(3);
        wxListItem itemCol3;
        itemCol3.SetId(cur);
        itemCol3.SetColumn(3);
        itemCol3.SetText(i.at(U("mime")).as_string());
        mainListCtrl->InsertItem(itemCol3);
         */
        cur++;
    }
    mainListCtrl->Show();
}

void MyRemoteFilePanel::OnSizeChanged(wxSizeEvent &event) {
    event.Skip();
    int panelWidth = event.GetSize().GetWidth();
    /*
     * "Type" --- "Filename" --- "FileSize" --- "FileType"
     */
    auto typeWidth = mainListCtrl->GetColumnWidth(0);
    //auto fileNameWidth = mainListCtrl->GetColumnWidth(1);
    auto fileSizeWidth = mainListCtrl->GetColumnWidth(2);
    auto fileTypeWidth = mainListCtrl->GetColumnWidth(3);
    auto s2 = 7 * 2;
    // wxBorder broder = userRemoteFilePage->GetBorder();
    // broder.
    auto diff = panelWidth - typeWidth - fileSizeWidth - fileTypeWidth - s2;
    if(diff > 0){
        //nameCol->SetWidth(diff);
        mainListCtrl->SetColumnWidth(1,diff);
    }
    // std::cout << mainListCtrl->GetCharWidth() << " x ";
    // std::cout << panelWidth << std::endl;
}
