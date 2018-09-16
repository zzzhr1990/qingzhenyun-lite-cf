//
// Created by zzzhr on 2018/9/14.
//

#include "sync_panel.h"

#include "../../resources/refresh.xpm"
#include "../../model/file_download_model.h"
#include "../../common/common_event_ids.h"
#include "../../util/common_util.h"
#include <wx/platinfo.h>

IMPLEMENT_DYNAMIC_CLASS( SyncPanel, wxPanel )


/*
 * OfflineDownloadTaskPanel event table definition
 */

BEGIN_EVENT_TABLE( SyncPanel, wxPanel )

////@begin SyncPanel event table entries
////@end SyncPanel event table entries

END_EVENT_TABLE()

SyncPanel::SyncPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style) {
    Init();
    Create(parent, id, pos, size, style);
}

SyncPanel::~SyncPanel() {
    menu->Destroy(ID_VIEW_D_TASK_DETAIL);
    menu->Destroy(ID_VIEW_D_OPEN_IN_EXPLORER);
    delete menu;
}

void SyncPanel::Init() {
////@begin SyncPanel member initialisation
////@end SyncPanel member initialisation
}

bool SyncPanel::Create(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style) {
    ////@begin OfflineDownloadTaskPanel creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxPanel::Create(parent, id, pos, size, style);
    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end OfflineDownloadTaskPanel creation
    return true;
}

void SyncPanel::CreateControls() {
    ////@begin OfflineDownloadTaskPanel content construction
    SyncPanel* itemPanel2 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    itemPanel2->SetSizer(itemBoxSizer1);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer1->Add(itemBoxSizer5, 0, wxGROW, 5);

    itemBoxSizer5->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);


    wxBitmapButton* refreshBtn = new wxBitmapButton(itemPanel2, wxID_ANY, itemPanel2->GetBitmapResource(wxT("refresh.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
    refreshBtn->SetHelpText(_("Refresh"));
    if (SyncPanel::ShowToolTips())
        refreshBtn->SetToolTip(_("Refresh"));
    itemBoxSizer5->Add(refreshBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);


    mainListCtrl = new wxListCtrl( itemPanel2, wxID_ANY, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT );
    itemBoxSizer1->Add(mainListCtrl, 1, wxGROW|wxALL, 5);
    //mainListCtrl->AppendColumn(_("Type"), wxLIST_FORMAT_LEFT, 40);
    mainListCtrl->AppendColumn(_("TaskName"), wxLIST_FORMAT_LEFT);
    mainListCtrl->AppendColumn(_("TaskSize"), wxLIST_FORMAT_CENTER);
    mainListCtrl->AppendColumn(_("Progress"), wxLIST_FORMAT_CENTER);
    mainListCtrl->AppendColumn(_("Status"), wxLIST_FORMAT_CENTER);
    mainListCtrl->AppendColumn(_("Type"), wxLIST_FORMAT_CENTER, 80);
    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer1->Add(itemBoxSizer8, 0, wxGROW, 5);

    wxCheckBox* itemCheckBox9 = new wxCheckBox( itemPanel2, wxID_ANY, _("Select All"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox9->SetValue(false);
    itemBoxSizer8->Add(itemCheckBox9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText10 = new wxStaticText( itemPanel2, wxID_STATIC, _("Selected:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(itemStaticText10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    /*
    wxBitmapButton* itemBitmapButton11 = new wxBitmapButton( itemPanel2, wxID_ANY, itemPanel2->GetBitmapResource(wxT("delete_trash.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBitmapButton11->SetHelpText(_("Delete"));
    if (SyncPanel::ShowToolTips())
        itemBitmapButton11->SetToolTip(_("Delete Select Tasks"));
    itemBoxSizer8->Add(itemBitmapButton11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
    */

    wxBoxSizer* itemBoxSizer12 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer8->Add(itemBoxSizer12, 1, wxALIGN_CENTER_VERTICAL, 5);


    wxStaticText* itemStaticText13 = new wxStaticText( itemPanel2, wxID_STATIC, _("Upload:0kb/s Download:0kb/s"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemStaticText13, 0, wxALIGN_CENTER_HORIZONTAL, 5);


    this->Bind(wxEVT_THREAD, &SyncPanel::OnThreadEvent, this);
    refreshBtn->Bind(wxEVT_BUTTON,&SyncPanel::RefreshBtnClicked,this);
    mainListCtrl->Bind(wxEVT_SIZE, &SyncPanel::OnSizeChanged, this);
    mainListCtrl->Bind(wxEVT_LIST_COL_BEGIN_DRAG, &SyncPanel::OnStartDrag, this);
    mainListCtrl->Bind(wxEVT_LIST_COL_END_DRAG, &SyncPanel::OnEndDrag, this);
    mainListCtrl->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &SyncPanel::OnItemRightClick, this);
    mainListCtrl->Bind(wxEVT_LIST_ITEM_ACTIVATED, &SyncPanel::OnTaskActivated, this);
    menu = new wxMenu();
    menu->Append(ID_VIEW_D_TASK_DETAIL, _("View task detail"));
    menu->Append(ID_VIEW_D_OPEN_IN_EXPLORER, _("Open in Explorer"));
    menu->Bind(wxEVT_MENU, &SyncPanel::OnCtrlListMenuClicked, this);
    FileDownloadModel::Instance().AddRefreshListener(U("SYNC_PANEL"),this);
////@end OfflineDownloadTaskPanel content construction
}

wxBitmap SyncPanel::GetBitmapResource(const wxString &name) {
    // Bitmap retrieval
////@begin SyncPanel bitmap retrieval
    wxUnusedVar(name);
    if (name == wxT("refresh.xpm"))
    {
        wxBitmap bitmap(refresh_xpm);
        return bitmap;
    }
    return wxNullBitmap;
////@end SyncPanel bitmap retrieval
}

/*
 * Should we show tooltips?
 */

bool SyncPanel::ShowToolTips()
{
    return true;
}

wxIcon SyncPanel::GetIconResource(const wxString &name) {
    ////@begin SyncPanel icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end SyncPanel icon retrieval
}

void SyncPanel::OnSizeChanged(wxSizeEvent &event) {
    event.Skip();
    if (drag) {
        return;
    }
    int panelWidth = mainListCtrl->GetSize().GetWidth();

    auto sizeWidth = mainListCtrl->GetColumnWidth(1);
    auto progressWidth = mainListCtrl->GetColumnWidth(2);
    auto statusWidth = mainListCtrl->GetColumnWidth(3);
    auto fileTimeWidth = mainListCtrl->GetColumnWidth(4);
    auto s2 = 9 * 2;

    auto diff = panelWidth - sizeWidth - progressWidth - statusWidth - fileTimeWidth - s2;
    if (diff > 0) {
        mainListCtrl->SetColumnWidth(0, diff);
    }
}

void SyncPanel::OnStartDrag(wxListEvent &event) {
    event.Skip();
    drag = true;
}

void SyncPanel::OnEndDrag(wxListEvent &event) {
    event.Skip();
    drag = false;
}

void SyncPanel::OnThreadEvent(wxThreadEvent &event) {

    switch (event.GetInt()) {
        case USER_SYNC_LIST_REFRESH:
        {
            auto payload = event.GetPayload<ResponseEntity>();
            RefreshListData(payload);
            break;
        }
        default:
            event.Skip();
    }
}

void SyncPanel::OnItemRightClick(const wxListEvent &event) {
    mainListCtrl->PopupMenu(menu);
}

void SyncPanel::OnTaskActivated(const wxListEvent &event) {
    //
    //
    //

}

void SyncPanel::OnCtrlListMenuClicked(const wxCommandEvent &event) {
	// get selected
	long itemIndex = -1;
	std::vector<long> selectedItems;
	while ((itemIndex = mainListCtrl->GetNextItem(itemIndex,
		wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND) {
		// Got the selected item index
		//wxLogDebug(listControl->GetItemText(itemIndex));
		// got
		//auto list = fileModel.GetCurrentList();
		long count = currentList.size();
		if (itemIndex >= count) {
			break;
		}
		auto& fileData = currentList.at(static_cast<web::json::array::size_type>(itemIndex));
		if (fileData.is_null()) {
			break;
		}

		if (itemIndex > -1) {
			selectedItems.push_back(itemIndex);
		}
	}
	if (selectedItems.empty()) {
		return;
	}
	if (event.GetId() == ID_VIEW_D_OPEN_IN_EXPLORER) {
		auto &path = currentList.at(static_cast<web::json::array::size_type>(selectedItems.at(0))).at(U("localDirectory")).as_string();
		wxString arg = path;
		wxString command;
        auto system = wxPlatformInfo::Get().GetOperatingSystemId();
        if(system & wxOS_WINDOWS){
            command = wxT("explorer");
        }
        else if (system & wxOS_MAC) {
            command = wxT("open");
        } else{
            wxMessageBox(_("It seems you are using Unix/Linux system, we can't determine your file explorer, set it first."));
            return;
        }
		command += ' ';
		bool quote;
		if (arg.empty())
		{
			// we need to quote empty arguments, otherwise they'd just
			// disappear
			quote = true;
		}
		else // non-empty
		{
			// escape any quotes present in the string to avoid interfering
			// with the command line parsing in the child process
			arg.Replace("\"", "\\\"", true /* replace all */);

			// and quote any arguments containing the spaces to prevent them from
			// being broken down
			quote = arg.find_first_of(" \t") != wxString::npos;
		}

		if (quote) {
			command += '\"' + arg + '\"';
		}
		else {
			command += arg;
		}
		//Windows - explorer
		//mac - open
		//	linux - konqueror or whatever gnome uses(nautilus ? )
		
		wxExecute(command, wxEXEC_ASYNC, nullptr);
	}
}

void SyncPanel::RefreshData() {
    FileDownloadModel::Instance().ForceRefresh(this);
}

SyncPanel::SyncPanel() {
    Init();
}

void SyncPanel::RefreshListData(const ResponseEntity &payload, const bool & updateAll) {
    //std::cout << "Data Refresh.." << std::endl;
    //update all
    web::json::array list = payload.result.as_array();
    //if(currentList.size() != )
    // clear data...

    if(!updateAll){
        if(list.size() != currentList.size()){
            RefreshListData(payload, true);
        }
    }


    //
    long cur = 0;
    if(updateAll){
        mainListCtrl->Hide();
        mainListCtrl->DeleteAllItems();
    }

    for (const auto& i : list) {
        // create item
        if(updateAll){
            wxListItem itemCol;
            itemCol.SetId(cur);
            // col 1 type
            itemCol.SetColumn(0);

            itemCol.SetText(i.at(U("name")).as_string());
            mainListCtrl->InsertItem(itemCol);
        }else{
            mainListCtrl->SetItem(cur, 0, i.at(U("name")).as_string());
        }
        // col1 taskname

        // col 2 file size
        mainListCtrl->SetItem(cur, 1, ConvertSizeToDisplay(i.at(U("size")).as_number().to_int64()));
        // col3 progress

        int progress = i.at(U("progress")).as_integer();
        if (progress > 100) {
            progress = 100;
        }
        if (progress < 0) {
            progress = 0;
        }

        mainListCtrl->SetItem(cur, 2, wxString::Format(_T("%d%%"), progress));

        int status = i.at(U("status")).as_integer();

        if (status < 0) {
            mainListCtrl->SetItem(cur, 3, _T("Error"));
        }
        else {
            if (status == 0) {
                mainListCtrl->SetItem(cur, 3, _T("Pretending"));
            }
            else if (status == 1) {
                mainListCtrl->SetItem(cur, 3, _T("Downloading"));
            }
            else if (status == 2) {
                mainListCtrl->SetItem(cur, 3, _T("Finish"));
            }
            else {
                mainListCtrl->SetItem(cur, 3, _T("Unknown"));
            }
        }

        // col5 date
        auto t = i.at(U("direction")).as_integer();

        if(t == 1){
            mainListCtrl->SetItem(cur, 4, _T("Download"));
        }else{
            mainListCtrl->SetItem(cur, 4,  _T("Upload"));
        }

        cur++;
    }
    if(updateAll){
        mainListCtrl->Show();
        //ResetCurrentPathDisplay();
        mainListCtrl->SetFocus();
    }
    currentList = list;
}

void SyncPanel::RefreshBtnClicked(const wxCommandEvent &event) {
    wxUnusedVar(event);
    RefreshData();
}
