/////////////////////////////////////////////////////////////////////////////
// Name:        offline_download_task_panel.cpp
// Purpose:     
// Author:      zzzhr
// Modified by: 
// Created:     02/09/2018 17:48:31
// RCS-ID:      
// Copyright:   for free
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".


#include "offline_download_task_panel.h"

////@begin XPM images
#include "../../resources/new_task.xpm"
#include "../../resources/delete_trash.xpm"
#include "../../resources/refresh.xpm"
#include "../../resources/left_btn.xpm"
#include "../../resources/right_btn.xpm"
#include "../../api_model/api_offline_task_model.h"
#include "../../common/common_event_ids.h"
#include "../../util/common_util.h"
#include "../../util/listctrlutil.h"
#include "../offline/add_task_result_dialog.h"

////@end XPM images


/*
 * OfflineDownloadTaskPanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS( OfflineDownloadTaskPanel, wxPanel )


/*
 * OfflineDownloadTaskPanel event table definition
 */

BEGIN_EVENT_TABLE( OfflineDownloadTaskPanel, wxPanel )

////@begin OfflineDownloadTaskPanel event table entries
////@end OfflineDownloadTaskPanel event table entries

END_EVENT_TABLE()


/*
 * OfflineDownloadTaskPanel constructors
 */

OfflineDownloadTaskPanel::OfflineDownloadTaskPanel()
{
    Init();
}

OfflineDownloadTaskPanel::OfflineDownloadTaskPanel(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{
    Init();
    Create(parent, id, pos, size, style);
}


/*
 * OfflineDownloadTaskPanel creator
 */

bool OfflineDownloadTaskPanel::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
{
////@begin OfflineDownloadTaskPanel creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    wxPanel::Create(parent, id, pos, size, style);
    CreateControls();
    if (GetSizer())
        GetSizer()->Fit(this);
////@end OfflineDownloadTaskPanel creation
    return true;
}


/*
 * OfflineDownloadTaskPanel destructor
 */

OfflineDownloadTaskPanel::~OfflineDownloadTaskPanel()
{
////@begin OfflineDownloadTaskPanel destruction
	menu->Destroy(ID_COPY_URL_TO_CLIP);
	menu->Destroy(ID_VIEW_TASK_DETAIL);
	menu->Destroy(ID_DELETE_SELECT_TASKS);
	// menu->Detach();
	delete menu;
////@end OfflineDownloadTaskPanel destruction
}


/*
 * Member initialisation
 */

void OfflineDownloadTaskPanel::Init()
{
////@begin OfflineDownloadTaskPanel member initialisation
////@end OfflineDownloadTaskPanel member initialisation
}


/*
 * Control creation for OfflineDownloadTaskPanel
 */

void OfflineDownloadTaskPanel::CreateControls()
{    
////@begin OfflineDownloadTaskPanel content construction
    OfflineDownloadTaskPanel* itemPanel2 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxVERTICAL);
    itemPanel2->SetSizer(itemBoxSizer1);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer1->Add(itemBoxSizer5, 0, wxGROW, 5);

    itemBoxSizer5->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxSearchCtrl* itemSearchCtrl2 = new wxSearchCtrl( itemPanel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemSearchCtrl2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

	wxBitmapButton* refreshBtn = new wxBitmapButton(itemPanel2, wxID_ANY, itemPanel2->GetBitmapResource(wxT("refresh.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
	refreshBtn->SetHelpText(_("Refresh"));
	if (OfflineDownloadTaskPanel::ShowToolTips())
		refreshBtn->SetToolTip(_("Refresh"));
	itemBoxSizer5->Add(refreshBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxBitmapButton* newTaskBtn = new wxBitmapButton( itemPanel2, wxID_ANY, itemPanel2->GetBitmapResource(wxT("new_task.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBoxSizer5->Add(newTaskBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    mainListCtrl = new wxListCtrl( itemPanel2, wxID_ANY, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT );
    itemBoxSizer1->Add(mainListCtrl, 1, wxGROW|wxALL, 5);
	//mainListCtrl->AppendColumn(_("Type"), wxLIST_FORMAT_LEFT, 40);
	mainListCtrl->AppendColumn(_("TaskName"), wxLIST_FORMAT_LEFT);
	mainListCtrl->AppendColumn(_("TaskSize"), wxLIST_FORMAT_CENTER);
	mainListCtrl->AppendColumn(_("Progress"), wxLIST_FORMAT_CENTER);
	mainListCtrl->AppendColumn(_("Status"), wxLIST_FORMAT_CENTER);
	mainListCtrl->AppendColumn(_("CreateTime"), wxLIST_FORMAT_CENTER, 160);
    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer1->Add(itemBoxSizer8, 0, wxGROW, 5);

    wxCheckBox* itemCheckBox9 = new wxCheckBox( itemPanel2, wxID_ANY, _("Select All"), wxDefaultPosition, wxDefaultSize, 0 );
    itemCheckBox9->SetValue(false);
    itemBoxSizer8->Add(itemCheckBox9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText10 = new wxStaticText( itemPanel2, wxID_STATIC, _("Selected:"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(itemStaticText10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBitmapButton* itemBitmapButton11 = new wxBitmapButton( itemPanel2, wxID_ANY, itemPanel2->GetBitmapResource(wxT("delete_trash.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBitmapButton11->SetHelpText(_("Delete"));
    if (OfflineDownloadTaskPanel::ShowToolTips())
        itemBitmapButton11->SetToolTip(_("Delete Select Files"));
    itemBoxSizer8->Add(itemBitmapButton11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer12 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer8->Add(itemBoxSizer12, 1, wxALIGN_CENTER_VERTICAL, 5);

    wxStaticText* itemStaticText13 = new wxStaticText( itemPanel2, wxID_STATIC, _("0 / 1024 Task this month"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer12->Add(itemStaticText13, 0, wxALIGN_CENTER_HORIZONTAL, 5);

    prevPageBtn = new wxBitmapButton( itemPanel2, wxID_ANY, itemPanel2->GetBitmapResource(wxT("left_btn.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBoxSizer8->Add(prevPageBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    currentPageInput = new wxTextCtrl( itemPanel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
    itemBoxSizer8->Add(currentPageInput, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	currentPageInput->SetEditable(false);

    nextPageBtn = new wxBitmapButton( itemPanel2, wxID_ANY, itemPanel2->GetBitmapResource(wxT("right_btn.xpm")), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW );
    itemBoxSizer8->Add(nextPageBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
	currentPageInput->Bind(wxEVT_LEFT_DCLICK, &OfflineDownloadTaskPanel::OnPageInputDClick, this);
	mainListCtrl->Bind(wxEVT_SIZE, &OfflineDownloadTaskPanel::OnSizeChanged, this);
	mainListCtrl->Bind(wxEVT_LIST_COL_BEGIN_DRAG, &OfflineDownloadTaskPanel::OnStartDrag, this);
	mainListCtrl->Bind(wxEVT_LIST_COL_END_DRAG, &OfflineDownloadTaskPanel::OnEndDrag, this);
	mainListCtrl->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &OfflineDownloadTaskPanel::OnItemRightClick, this);
	prevPageBtn->Bind(wxEVT_BUTTON, &OfflineDownloadTaskPanel::PrevBtnClicked, this);
	nextPageBtn->Bind(wxEVT_BUTTON, &OfflineDownloadTaskPanel::NextBtnClicked, this);
	mainListCtrl->Bind(wxEVT_LIST_ITEM_ACTIVATED, &OfflineDownloadTaskPanel::OnUserRemoteTaskActivated, this);
	newTaskBtn->Bind(wxEVT_BUTTON, &OfflineDownloadTaskPanel::NewTaskBtnClicked, this);
	refreshBtn->Bind(wxEVT_BUTTON, &OfflineDownloadTaskPanel::RefreshBtnClicked, this);
	menu = new wxMenu();
	menu->Append(ID_VIEW_TASK_DETAIL, _("View task detail"));
	menu->Append(ID_COPY_URL_TO_CLIP, _("Copy task url to clipboard"));
	menu->Append(ID_DELETE_SELECT_TASKS, _("Delete selected task"));
	menu->Bind(wxEVT_MENU, &OfflineDownloadTaskPanel::OnCtrlListMenuClicked, this);
////@end OfflineDownloadTaskPanel content construction
}


/*
 * Should we show tooltips?
 */

bool OfflineDownloadTaskPanel::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */
// wxListEvent
void OfflineDownloadTaskPanel::OnCtrlListMenuClicked(const wxCommandEvent &event) {
	//TODO: FIX this
	/*
	auto & fileModel = OfflineDownloadTaskModel::Instance();
	auto list = fileModel.GetCurrentList();
	long count = list.size();
	auto selectedItem = GetCurrentSelectItems(mainListCtrl);
	if (selectedItem.empty()) {
		return;
	}
	if (event.GetId() == ID_COPY_URL_TO_CLIP) {
		auto selectedIndex = selectedItem[0];
		if (selectedIndex >= count) {
			return;
		}
		auto fileData = list.at(static_cast<web::json::array::size_type>(selectedIndex));
		if (fileData.has_field(U("detail"))) {
			try
			{
				web::json::value data = web::json::value::parse(fileData.at(U("detail")).as_string());
				if (data.has_field(U("url"))) {
					CopyTextToClipboard(data.at(U("url")).as_string());
					return;
				}
			}
			catch (const std::exception&)
			{
				return;
			}
		}
	}
	else if (event.GetId() == ID_VIEW_TASK_DETAIL) {
		auto selectedIndex = selectedItem[0];
		if (selectedIndex >= count) {
			return;
		}
		auto fileData = list.at(static_cast<web::json::array::size_type>(selectedIndex));
		ShowTaskDetail(fileData);
		return;
	}
	else if (event.GetId() == ID_DELETE_SELECT_TASKS) {
		auto json = web::json::value::array();
		long i = 0;
		for (auto &selectedIndex : selectedItem) {
			if (selectedIndex < count) {
				auto fileData = list.at(static_cast<web::json::array::size_type>(selectedIndex));
				if (fileData.has_field(U("taskId"))) {
					//auto taskId =.as_string();
					json[i] = fileData.at(U("taskId"));
					i++;
				}
			}
		}
		if (i > 0) {
			fileModel.DeleteTasks(this, json);
		}
		return;
	}
	 */
	/*
	if (event.GetId() == ID_COPY_URL_TO_CLIP) {
		long itemIndex = -1;

		while ((itemIndex = mainListCtrl->GetNextItem(itemIndex,
			wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND) {
			// Got the selected item index
			//wxLogDebug(listControl->GetItemText(itemIndex));
			// got
			auto & fileModel = OfflineDownloadTaskModel::Instance();
			auto list = fileModel.GetCurrentList();
			long count = list.size();
			if (itemIndex >= count) {
				return;
			}
			auto fileData = list.at(itemIndex);
			if (fileData.is_null()) {
				return;
			}

			if (fileData.has_field(U("detail"))) {
				try
				{
					web::json::value data = web::json::value::parse(fileData.at(U("detail")).as_string());
					if (data.has_field(U("url"))) {
						CopyTextToClipboard(data.at(U("url")).as_string());
						break;
					}
				}
				catch (const std::exception&)
				{
					continue;
				}
			}
		}
	}
	*/
	
}

void OfflineDownloadTaskPanel::ShowTaskDetail(const web::json::value& v) {
	if (taskDetail == nullptr) {
		taskDetail = new TaskDetail(this);
	}
	taskDetail->setView(v);
	taskDetail->ShowModal();
}

void OfflineDownloadTaskPanel::OnItemRightClick(const wxListEvent &event) {
	mainListCtrl->PopupMenu(menu);
}
void OfflineDownloadTaskPanel::OnSizeChanged( wxSizeEvent &event) {
	event.Skip();
	if (drag) {
		return;
	}
	//mainListCtrl->Hide();
	int panelWidth = mainListCtrl->GetSize().GetWidth();
	auto sizeWidth = mainListCtrl->GetColumnWidth(1);
	//auto fileNameWidth = mainListCtrl->GetColumnWidth(1);
	auto progressWidth = mainListCtrl->GetColumnWidth(2);
	auto statusWidth = mainListCtrl->GetColumnWidth(3);
	auto fileTimeWidth = mainListCtrl->GetColumnWidth(4);
	auto s2 = 9 * 2;
	// wxBorder broder = userRemoteFilePage->GetBorder();
	// broder.
	auto diff = panelWidth - sizeWidth - progressWidth - statusWidth - fileTimeWidth - s2;
	if (diff > 0) {
		//nameCol->SetWidth(diff);
		mainListCtrl->SetColumnWidth(0, diff);
	}
	// mainListCtrl->Show();
	// std::cout << mainListCtrl->GetCharWidth() << " x ";
	// std::cout << panelWidth << std::endl;
}

void OfflineDownloadTaskPanel::OnUserRemoteTaskActivated(const wxListEvent &event)
{
    //TODO:FIX
    /*
	long index = event.GetIndex();
	auto & fileModel = OfflineDownloadTaskModel::Instance();
	auto list = fileModel.GetCurrentList();
	long count = list.size();
	if (index >= count) {
		return;
	}
	auto fileData = list.at(static_cast<web::json::array::size_type>(index));
	if (fileData.is_null()) {
		return;
	}
	if (fileData.has_field(U("filePath"))) {
		utility::string_t currentPath = fileData.at(U("filePath")).as_string();
		// USER_GOTO_DIRECTORY
		if (!currentPath.empty()) {
			wxThreadEvent xEvent(wxEVT_THREAD, this->GetId());
			// event.SetString(COMMON_THREAD_EVENT_STRING);
			xEvent.SetInt(USER_GOTO_DIRECTORY);
			xEvent.SetString(currentPath);
			wxQueueEvent(this, xEvent.Clone());
		}
		
	}
	*/
	
}

wxBitmap OfflineDownloadTaskPanel::GetBitmapResource(const wxString& name )
{
    // Bitmap retrieval
////@begin OfflineDownloadTaskPanel bitmap retrieval
    wxUnusedVar(name);
    if (name == wxT("new_task.xpm"))
    {
        wxBitmap bitmap(new_task_xpm);
        return bitmap;
    }
    else if (name == wxT("delete_trash.xpm"))
    {
        wxBitmap bitmap(delete_trash_xpm);
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
    }else if (name == wxT("refresh.xpm"))
	{
		wxBitmap bitmap(refresh_xpm);
		return bitmap;
	}
    return wxNullBitmap;
////@end OfflineDownloadTaskPanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon OfflineDownloadTaskPanel::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin OfflineDownloadTaskPanel icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end OfflineDownloadTaskPanel icon retrieval
}

void OfflineDownloadTaskPanel::OnPageInputDClick(const wxMouseEvent &event) {

    auto & task_model = qingzhen::api::api_offline_task_model::instance();
	currentPageInput->SetValue(wxString::Format(_T("%d"), task_model.get_current_page()));
	currentPageInput->SetEditable(true);
	currentPageInput->Bind(wxEVT_KILL_FOCUS, &OfflineDownloadTaskPanel::OnPageInputKillFocus, this);
}

void OfflineDownloadTaskPanel::RefreshBtnClicked(const wxCommandEvent &event) {
    this->RefreshPage();
}

void OfflineDownloadTaskPanel::OnPageInputKillFocus(const wxFocusEvent &event) {

	currentPageInput->Unbind(wxEVT_KILL_FOCUS, &OfflineDownloadTaskPanel::OnPageInputKillFocus, this);
	currentPageInput->SetEditable(false);
    auto & task_model = qingzhen::api::api_offline_task_model::instance();
	wxString input = currentPageInput->GetValue();
	int c = wxAtoi(input);
	if (c > 0 && c != task_model.get_current_page() && c <= task_model.get_total_page()) {
		this->RefreshPage(c);
	}
	else {
		ResetCurrentPathDisplay();
	}


}





void OfflineDownloadTaskPanel::PrevBtnClicked(const wxCommandEvent &event) {

    auto & task_model = qingzhen::api::api_offline_task_model::instance();
	auto page = task_model.get_current_page();
	if (page > 1) {
		this->RefreshPage(page - 1);
	}
}

void OfflineDownloadTaskPanel::NextBtnClicked(const wxCommandEvent &event) {
    auto & task_model = qingzhen::api::api_offline_task_model::instance();
    auto page = task_model.get_current_page();
	if (page < task_model.get_total_page()) {
        this->RefreshPage(page + 1);
	}
}

void OfflineDownloadTaskPanel::NewTaskBtnClicked(const wxCommandEvent &event) {

	AddOfflineTask * addOfflineTaskDialog = new AddOfflineTask(this);
	if(addOfflineTaskDialog->ShowModal() == wxID_OK) {
	    if(addOfflineTaskDialog->IsTorrentPageSelected()){

	    }else{

	    }
        currentDownloadPath = addOfflineTaskDialog->GetDownloadDir();
        auto url = addOfflineTaskDialog->GetDownloadUrl().Trim();
        if(url.empty()){
            wxMessageBox(_("Please input urls"), _("Empty input"),wxICON_INFORMATION | wxOK, this);
            return;
        }
        action_cancellation.cancel();
        action_cancellation = pplx::cancellation_token_source();
        qingzhen::api::api_offline_task_model::instance().parse_url(action_cancellation, url).then([this](response_entity entity){
            if(!entity.is_cancelled()){
                this->CallAfter([this, entity](){
                    this->OnUrlParsed(entity);
                });
            }
        });
    }
}

void OfflineDownloadTaskPanel::ResetCurrentPathDisplay() {
	auto & task_model = qingzhen::api::api_offline_task_model::instance();
	auto const &currentPage = task_model.get_current_page();
	auto const &totalPage = task_model.get_total_page();
	currentPageInput->SetValue(wxString::Format(_T("%d / %d"), currentPage, totalPage));
	currentPageInput->SetEditable(false);
	prevPageBtn->Enable(currentPage > 1);
	nextPageBtn->Enable(currentPage < totalPage);

}

void OfflineDownloadTaskPanel::OnStartDrag(wxListEvent & event)
{
	event.Skip();
	drag = true;
}

void OfflineDownloadTaskPanel::OnEndDrag(wxListEvent & event)
{
	event.Skip();
	drag = false;

}



void OfflineDownloadTaskPanel::StartDownloadUrl(const wxString& str) {
	//OfflineDownloadTaskModel::Instance().GetPage(this);
	/*
	OfflineDownloadTaskModel::Instance().GetPage(this);
	 */
}

void OfflineDownloadTaskPanel::RefreshData(const bool &force) {
    if (!force && waitPage) {
        return;
    }
    this->RefreshPage();
}

void OfflineDownloadTaskPanel::RefreshPage(const int &page, const int &page_size) {
    waitPage = true;
    this->offline_page_cancellation.cancel();
    this->offline_page_cancellation = pplx::cancellation_token_source();
    // go and request...
    qingzhen::api::api_offline_task_model::instance().refresh_page(this->offline_page_cancellation,page,page_size).then([this](response_entity entity){
        if(!entity.is_cancelled()){
            this->CallAfter([this,entity](){
                this->OnCurrentPageDataReceived(entity);
            });
        }
        this->waitPage = false;
    });
}

void OfflineDownloadTaskPanel::Terminate() {
    offline_page_cancellation.cancel();
    action_cancellation.cancel();
}

void OfflineDownloadTaskPanel::OnCurrentPageDataReceived(response_entity entity) {
    if(qingzhen::api::api_offline_task_model::instance().on_response_entity_page_data_received(entity)){
        this->RefreshDataGridDisplay();
    }
}

void OfflineDownloadTaskPanel::RefreshDataGridDisplay() {
    mainListCtrl->Freeze();
    auto model = qingzhen::api::api_offline_task_model::instance();

    auto task_list = model.get_current_list();
    long list_size = static_cast<long>(task_list.size());
    auto refresh = list_size != last_list_size;
    last_list_size = list_size;

    long cur = 0;
    if (refresh) {
        mainListCtrl->Hide();
        mainListCtrl->DeleteAllItems();
    }
    for (const auto& i : task_list) {
        // create item
        wxListItem itemCol;
        itemCol.SetId(cur);
        // col 1 type
        itemCol.SetColumn(0);

        itemCol.SetText(i.at(U("name")).as_string());
        if (refresh) {
            mainListCtrl->InsertItem(itemCol);
        }
        else {
            mainListCtrl->SetItem(cur, 0, itemCol.GetText());
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
            mainListCtrl->SetItem(cur, 3, wxString::Format(_T("Error %d"), i.at(U("errorCode")).as_integer()));
        }
        else {
            if (status == 90) {
                mainListCtrl->SetItem(cur, 3, _T("Copying"));
            }
            else if (status == 100) {
                mainListCtrl->SetItem(cur, 3, _T("Finish"));
            }
            else {
                mainListCtrl->SetItem(cur, 3, _T("Downloading"));
            }
        }

        // col5 date
        std::time_t t = i.at(U("createTime")).as_number().to_int64() / 1000;
        mainListCtrl->SetItem(cur, 4, ConvertTimeToDisplay(t, "%Y/%m/%d %H:%M"));


        cur++;
    }
    if (refresh) {
        mainListCtrl->Show();
        mainListCtrl->SetFocus();
    }
    mainListCtrl->Thaw();
    ResetCurrentPathDisplay();
}

void OfflineDownloadTaskPanel::OnUrlParsed(response_entity entity) {
    if(!entity.success){
        wxMessageBox(wxString::Format(_("Add task failed %s"), entity.message), _("Add Task Failed"));
        return;
    }
    auto result = entity.result;
    if(result.is_null()){
        return;
    }
    if(result.has_field(_XPLATSTR("needPassword"))){
        if(result.at(_XPLATSTR("needPassword")).as_bool()){
            wxMessageBox(_("Url need password to download, please input password and try again"), _("Need password"));
            return;
        }
    }
    if(!result.has_field(_XPLATSTR("taskHash"))){
        return;
    }
    auto taskHash = result.at(_XPLATSTR("taskHash")).as_string();
    if(result.has_field(_XPLATSTR("files"))){
        //
        auto files = result.at(_XPLATSTR("files")).as_array();
        if(files.size() > 0){
            wxArrayString file_names;
            for(auto &data:files){
                wxString file_name = wxT("unknown file");
                if(data.has_field(_XPLATSTR("path"))){
                    file_name = data.at(_XPLATSTR("path")).as_string();
                } else if(data.has_field(_XPLATSTR("name"))){
                    file_name = data.at(_XPLATSTR("name")).as_string();
                }
                file_names.push_back(file_name);
            }
            auto * addTaskResult = new AddTaskResultDialog(this, file_names);
            if(wxID_OK == addTaskResult->ShowModal()){
                StartTask(taskHash, addTaskResult->GetItemsSelectString());
            }
            return;
        }
    }
    StartTask(taskHash, _XPLATSTR("[\"*\"]"));
}

void OfflineDownloadTaskPanel::StartTask(utility::string_t taskHash, utility::string_t copyFile) {
    action_cancellation.cancel();
    action_cancellation = pplx::cancellation_token_source();
    utility::string_t path = this->currentDownloadPath;
    auto task = qingzhen::api::api_offline_task_model::instance().start_task(action_cancellation, taskHash, path, copyFile);
    task.then([this](response_entity entity){
        if(!entity.is_cancelled()){
            this->CallAfter([this,entity](){
                if(entity.success){
                    this->RefreshPage(1);
                }else{
                    wxMessageBox(wxString::Format(_("Add task failed %s"), entity.message), _("Add Task Failed"));
                }
            });
        }
    });
}
