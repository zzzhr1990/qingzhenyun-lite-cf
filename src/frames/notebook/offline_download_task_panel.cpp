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
#include "../../model/offine_task_model.h"
#include "../../model/remote_file_model.h"
//#include "../../model/remote_download_task_model.h"
#include "../../common/common_event_ids.h"
#include "../../util/common_util.h"

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
	this->Bind(wxEVT_THREAD, &OfflineDownloadTaskPanel::OnThreadEvent, this);
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
		auto fileData = list.at(static_cast<web::json::array::size_type>(itemIndex));
		if (fileData.is_null()) {
			return;
		}
		// found
		if (event.GetId() == ID_COPY_URL_TO_CLIP) {
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
		else if (event.GetId() == ID_VIEW_TASK_DETAIL) {
			ShowTaskDetail(fileData);
		}
	}
	
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
	//event.Get
	auto & fileModel = OfflineDownloadTaskModel::Instance();
	currentPageInput->SetValue(wxString::Format(_T("%d"), fileModel.GetCurrentPage()));
	currentPageInput->SetEditable(true);
	currentPageInput->Bind(wxEVT_KILL_FOCUS, &OfflineDownloadTaskPanel::OnPageInputKillFocus, this);
}

void OfflineDownloadTaskPanel::RefreshBtnClicked(const wxCommandEvent &event) {
	auto & fileModel = OfflineDownloadTaskModel::Instance();
	fileModel.GetPage(this);

}

void OfflineDownloadTaskPanel::OnPageInputKillFocus(const wxFocusEvent &event) {

	currentPageInput->Unbind(wxEVT_KILL_FOCUS, &OfflineDownloadTaskPanel::OnPageInputKillFocus, this);
	currentPageInput->SetEditable(false);
	auto & fileModel = OfflineDownloadTaskModel::Instance();
	wxString input = currentPageInput->GetValue();
	int c = wxAtoi(input);
	if (c > 0 && c != fileModel.GetCurrentPage() && c <= fileModel.GetTotalPage() && c != fileModel.GetCurrentPage()) {
		fileModel.GetPage(this, c);
	}
	else {
		ResetCurrentPathDisplay();
	}

}

void OfflineDownloadTaskPanel::OnThreadEvent( wxThreadEvent &event) {
	// D
	switch (event.GetInt()) {
	case USER_REMOTE_TASK_PAGE_DATA:
	{
		auto payload = event.GetPayload<ResponseEntity>();
		RefreshListData(payload);
		break;
	}
	case USER_REMOTE_TASK_CREATE:
	{
		auto & remoteModel = OfflineDownloadTaskModel::Instance();
		remoteModel.GetPage(this);
		break;
	}
	case USER_REMOTE_TASK_URL_PARSED:
	{
		auto payload = event.GetPayload<ResponseEntity>();
		//RefreshListData(payloads);
		const auto & res = payload.result;
		if (res.has_field(U("taskHash"))) {
			// start
			auto & remoteModel = OfflineDownloadTaskModel::Instance();
			remoteModel.StartTask(this, res.at(U("taskHash")).as_string(), currentDownloadPath, _("*"));
		}
		break;
	}
	case USER_REMOTE_TASK_URL_START: {
		addOfflineTask->ClearUrlInputStr();
		OfflineDownloadTaskModel::Instance().GetPage(this, 1);
		break;
	}
		
	default:
		event.Skip();
	}
}

void OfflineDownloadTaskPanel::RefreshListData(const ResponseEntity& payload) {
	auto model = &OfflineDownloadTaskModel::Instance();
	web::json::array list = payload.result.at(U("list")).as_array();
	auto currentPage = payload.result.at(U("page")).as_integer();
	auto currentPageSize = payload.result.at(U("pageSize")).as_integer();
	auto totalPage = payload.result.at(U("totalPage")).as_integer();
	//const utility::string_t &patent
	model->UpdateCurrent(currentPage, currentPageSize, totalPage,list);
	/*
	mainListCtrl->AppendColumn(_("TaskName"), wxLIST_FORMAT_LEFT);
	mainListCtrl->AppendColumn(_("TaskSize"), wxLIST_FORMAT_CENTER);
	mainListCtrl->AppendColumn(_("Progress"), wxLIST_FORMAT_CENTER);
	mainListCtrl->AppendColumn(_("Status"), wxLIST_FORMAT_CENTER);
	mainListCtrl->AppendColumn(_("CreateTime"), wxLIST_FORMAT_CENTER, 160);
	*/
	long cur = 0;
	mainListCtrl->Hide();
	mainListCtrl->DeleteAllItems();
	for (const auto& i : list) {
		// create item
		wxListItem itemCol;
		itemCol.SetId(cur);
		// col 1 type
		itemCol.SetColumn(0);
		
		itemCol.SetText(i.at(U("name")).as_string());
		mainListCtrl->InsertItem(itemCol);
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
	mainListCtrl->Show();
	ResetCurrentPathDisplay();
	mainListCtrl->SetFocus();
}

//void OfflineDownloadTaskPanel::RefreshListData(const ResponseEntity& payload) {
	/*
	web::json::array list = payload.result.at(U("list")).as_array();
	// model->AppendItem( data ,1);
	auto model = &RemoteFileModel::Instance();
	auto dirInfo = payload.result.at(U("info"));
	auto currentPath = dirInfo.at(U("path")).as_string();
	auto currentId = dirInfo.at(U("uuid")).as_string();
	auto parent = dirInfo.at(U("parent")).as_string();
	auto currentPage = payload.result.at(U("page")).as_integer();
	auto currentPageSize = payload.result.at(U("pageSize")).as_integer();
	auto totalPage = payload.result.at(U("totalPage")).as_integer();
	model->UpdateCurrentLocation(currentPath, currentId, currentPage, currentPageSize, totalPage, parent, list);
	
	// * "Type" --- "Filename" --- "FileSize" --- "FileType"
	
	long cur = 0;
	//long index = 0;
	mainListCtrl->Hide();
	mainListCtrl->DeleteAllItems();
	for (const auto& i : list) {
		// create item
		wxListItem itemCol;
		itemCol.SetId(cur);
		// col 1 type
		itemCol.SetColumn(0);
		auto cx = i.at(U("type")).as_integer();
		if (cx == 1) {
			itemCol.SetText(_T("[+]"));
		}
		else if (cx == -1) {
			itemCol.SetText(_T("[E]"));
			itemCol.SetTextColour(*wxRED);
		}
		else {
			itemCol.SetText(_T("[-]"));
		}
		mainListCtrl->InsertItem(itemCol);
		// col1 filename

		mainListCtrl->SetItem(cur, 1, i.at(U("name")).as_string());
		// col 2 file size
		mainListCtrl->SetItem(cur, 2, ConvertSizeToDisplay(i.at(U("size")).as_number().to_int64()));
		// col3 mime
		mainListCtrl->SetItem(cur, 3, i.at(U("ext")).as_string());
		// col4 date
		std::time_t t = i.at(U("ctime")).as_number().to_int64() / 1000;
		mainListCtrl->SetItem(cur, 4, ConvertTimeToDisplay(t, "%Y/%m/%d %H:%M"));


		cur++;
	}
	mainListCtrl->Show();
	ResetCurrentPathDisplay();
	mainListCtrl->SetFocus();
	*/

//}

void OfflineDownloadTaskPanel::PrevBtnClicked(const wxCommandEvent &event) {
	auto & fileModel = OfflineDownloadTaskModel::Instance();
	auto page = fileModel.GetCurrentPage();
	if (page > 1) {
		fileModel.GetPage(this, page - 1);
	}
}

void OfflineDownloadTaskPanel::NextBtnClicked(const wxCommandEvent &event) {
	auto & fileModel = OfflineDownloadTaskModel::Instance();
	auto page = fileModel.GetCurrentPage();
	if (page < fileModel.GetTotalPage()) {
		fileModel.GetPage(this, page + 1);
	}
}

void OfflineDownloadTaskPanel::NewTaskBtnClicked(const wxCommandEvent &event) {
	//show
	if (this->addOfflineTask == nullptr) {
		addOfflineTask = new AddOfflineTask(this, wxID_ANY);
		addOfflineTask->Iconize(false);
		//
		addOfflineTask->SetLabel(_("Add new task"));
	}
	addOfflineTask->SetDownloadPath(RemoteFileModel::Instance().GetCurrentPath());
	// login_frame->Show(true);
	// loginFrame->Raise();  // doesn't seem to work
	// loginFrame->SetFocus();  // does nothing
	auto const &result = addOfflineTask->ShowModal(); // this by itself doesn't work
	if (result == wxID_OK)
	{
		// check validate
		//const auto &userInput = loginFrame->getUserInput();
		//const auto &userPassword = loginFrame->getUserPassword();
		//TryLogin(userInput, Utf8MD5(userPassword));
		const auto &userInput = addOfflineTask->GetDownloadPath();
		const auto &userUrlInput = addOfflineTask->GetUrlInputStr();
		if (!userInput.empty() && !userUrlInput.empty()) {
			//Start..
			currentDownloadPath = userInput;
			OfflineDownloadTaskModel::Instance().StartUrl(this, userUrlInput);
		}
	}
}

void OfflineDownloadTaskPanel::ResetCurrentPathDisplay() {
	auto & fileModel = OfflineDownloadTaskModel::Instance();
	auto const &currentPage = fileModel.GetCurrentPage();
	auto const &totalPage = fileModel.GetTotalPage();
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

void OfflineDownloadTaskPanel::RefreshData() {
	OfflineDownloadTaskModel::Instance().GetPage(this);
}

void OfflineDownloadTaskPanel::StartDownloadUrl(const wxString& str) {
	//OfflineDownloadTaskModel::Instance().GetPage(this);
	OfflineDownloadTaskModel::Instance().GetPage(this);
}