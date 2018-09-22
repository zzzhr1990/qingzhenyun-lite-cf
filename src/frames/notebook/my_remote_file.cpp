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
#include <wx/filename.h>

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
#include "../../model/sync_model.h"
#include "../../util/common_util.h"

////@begin XPM images
#include "../../resources/refresh.xpm"
#include "../../resources/up_level.xpm"
#include "../../resources/search.xpm"
#include "../../resources/new_directory.xpm"
#include "../../resources/delete_trash.xpm"
#include "../../resources/copy.xpm"
#include "../../resources/left_btn.xpm"
#include "../../resources/right_btn.xpm"
#include "../userfile/filedetail.h"

#include "wx/dnd.h"         // drag and drop for the playlist

////@end XPM images


/*
 * MyRemoteFilePanel type definition
 */

IMPLEMENT_DYNAMIC_CLASS(MyRemoteFilePanel, wxPanel)


/*
 * MyRemoteFilePanel event table definition
 */

BEGIN_EVENT_TABLE(MyRemoteFilePanel, wxPanel)

////@begin NyRemoteFilePanel event table entries
////@end NyRemoteFilePanel event table entries

END_EVENT_TABLE()
//

// ----------------------------------------------------------------------------
// wxPlayListDropTarget
//
//  Drop target for playlist (i.e. allows users to drag a file from explorer into
//  the playlist to add that file)
// ----------------------------------------------------------------------------
#if wxUSE_DRAG_AND_DROP

class wxPlayListDropTarget : public wxFileDropTarget {
public:
    wxPlayListDropTarget(MyRemoteFilePanel &panel) : m_book(panel) {}

    ~wxPlayListDropTarget() {}

    virtual bool OnDropFiles(wxCoord WXUNUSED(x), wxCoord WXUNUSED(y),
                             const wxArrayString &files) {
        m_book.DoOpenFiles(files);

        return true;
    }

    //wxListCtrl& m_list;
    MyRemoteFilePanel &m_book;
};

#endif

/*
 * MyRemoteFilePanel constructors
 */

MyRemoteFilePanel::MyRemoteFilePanel() {
    Init();
}

MyRemoteFilePanel::MyRemoteFilePanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size,
                                     long style) {
    Init();
    Create(parent, id, pos, size, style);
}


/*
 * MyRemoteFilePanel creator
 */

bool MyRemoteFilePanel::Create(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style) {
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

MyRemoteFilePanel::~MyRemoteFilePanel() {
////@begin NyRemoteFilePanel destruction
    menu->Destroy(ID_DOWNLOAD_FILE);
    menu->Destroy(ID_DELETE_FILE);
	menu->Destroy(ID_VIEW_FILE_DETAIL);
    delete menu;
////@end NyRemoteFilePanel destruction
}


/*
 * Member initialisation
 */

void MyRemoteFilePanel::Init() {
////@begin NyRemoteFilePanel member initialisation
////@end NyRemoteFilePanel member initialisation
}


/*
 * Control creation for MyRemoteFilePanel
 */

void MyRemoteFilePanel::CreateControls() {
////@begin NyRemoteFilePanel content construction
    MyRemoteFilePanel *itemPanel1 = this;

    this->SetName(wxT("MyRemoteFiles"));
    wxBoxSizer *itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemPanel1->SetSizer(itemBoxSizer2);

    wxBoxSizer *itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxGROW, 5);

    wxStaticText *itemStaticText4 = new wxStaticText(itemPanel1, wxID_STATIC, _("Current Path"), wxDefaultPosition,
                                                     wxDefaultSize, 0);
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    pathInput = new wxTextCtrl(itemPanel1, ID_TEXTCTRL, _("/"), wxDefaultPosition, wxDefaultSize, 0);
    pathInput->Enable(false);
    itemBoxSizer3->Add(pathInput, 1, wxGROW | wxALL, 5);

    wxBitmapButton *refreshBtn = new wxBitmapButton(itemPanel1, ID_BITMAPBUTTON,
                                                    itemPanel1->GetBitmapResource(wxT("refresh.xpm")),
                                                    wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
    refreshBtn->SetHelpText(_("Refresh"));
    if (MyRemoteFilePanel::ShowToolTips())
        refreshBtn->SetToolTip(_("Refresh"));
    itemBoxSizer3->Add(refreshBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    parentBtn = new wxBitmapButton(itemPanel1, ID_BITMAPBUTTON5, itemPanel1->GetBitmapResource(wxT("up_level.xpm")),
                                   wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
    parentBtn->SetHelpText(_("Up level"));
    if (MyRemoteFilePanel::ShowToolTips())
        parentBtn->SetToolTip(_("Up level"));
    itemBoxSizer3->Add(parentBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxBitmapButton *itemBitmapButton7 = new wxBitmapButton(itemPanel1, ID_BITMAPBUTTON1,
                                                           itemPanel1->GetBitmapResource(wxT("search.xpm")),
                                                           wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
    itemBitmapButton7->SetHelpText(_("Search"));
    if (MyRemoteFilePanel::ShowToolTips())
        itemBitmapButton7->SetToolTip(_("Search"));
    itemBoxSizer3->Add(itemBitmapButton7, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxBitmapButton *newDirectoryBtn = new wxBitmapButton(itemPanel1, ID_BITMAPBUTTON23,
                                                         itemPanel1->GetBitmapResource(wxT("new_directory.xpm")),
                                                         wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
    newDirectoryBtn->SetHelpText(_("New directory"));
    if (MyRemoteFilePanel::ShowToolTips())
        newDirectoryBtn->SetToolTip(_("New directory"));
    itemBoxSizer3->Add(newDirectoryBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    mainListCtrl = new wxListCtrl(itemPanel1, ID_LISTCTRL, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT);
    itemBoxSizer2->Add(mainListCtrl, 1, wxGROW | wxALL, 5);
    mainListCtrl->AppendColumn(_("Type"), wxLIST_FORMAT_LEFT, 50);
    mainListCtrl->AppendColumn(_("Filename"), wxLIST_FORMAT_LEFT);
    mainListCtrl->AppendColumn(_("FileSize"), wxLIST_FORMAT_CENTER);
    mainListCtrl->AppendColumn(_("FileType"), wxLIST_FORMAT_CENTER);
    mainListCtrl->AppendColumn(_("CreateTime"), wxLIST_FORMAT_CENTER, 160);

#if wxUSE_DRAG_AND_DROP
    mainListCtrl->SetDropTarget(new wxPlayListDropTarget(*itemPanel1));
#endif

    wxBoxSizer *itemBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer4, 0, wxGROW, 5);

    wxCheckBox *itemCheckBox1 = new wxCheckBox(itemPanel1, ID_CHECKBOX, _("Select All"), wxDefaultPosition,
                                               wxDefaultSize, 0);
    itemCheckBox1->SetValue(false);
    itemBoxSizer4->Add(itemCheckBox1, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxStaticText *itemStaticText2 = new wxStaticText(itemPanel1, wxID_STATIC, _("Selected:"), wxDefaultPosition,
                                                     wxDefaultSize, 0);
    itemBoxSizer4->Add(itemStaticText2, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxBitmapButton *itemBitmapButton5 = new wxBitmapButton(itemPanel1, ID_BITMAPBUTTON2,
                                                           itemPanel1->GetBitmapResource(wxT("delete_trash.xpm")),
                                                           wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
    itemBitmapButton5->SetHelpText(_("Delete"));
    if (MyRemoteFilePanel::ShowToolTips())
        itemBitmapButton5->SetToolTip(_("Delete Select Files"));
    itemBoxSizer4->Add(itemBitmapButton5, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxBitmapButton *itemBitmapButton8 = new wxBitmapButton(itemPanel1, ID_BITMAPBUTTON3,
                                                           itemPanel1->GetBitmapResource(wxT("copy.xpm")),
                                                           wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
    itemBoxSizer4->Add(itemBitmapButton8, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    wxBoxSizer *itemBoxSizer6 = new wxBoxSizer(wxVERTICAL);
    itemBoxSizer4->Add(itemBoxSizer6, 1, wxALIGN_CENTER_VERTICAL, 5);

    capacityText = new wxStaticText(itemPanel1, wxID_STATIC, _("8888 / 8888 MB"), wxDefaultPosition, wxDefaultSize, 0);
    itemBoxSizer6->Add(capacityText, 0, wxALIGN_CENTER_HORIZONTAL, 5);

    prevPageBtn = new wxBitmapButton(itemPanel1, ID_BITMAPBUTTON6, itemPanel1->GetBitmapResource(wxT("left_btn.xpm")),
                                     wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
    itemBoxSizer4->Add(prevPageBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    currentPageInput = new wxTextCtrl(itemPanel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                                      wxTE_CENTRE);
    currentPageInput->SetEditable(false);
    currentPageInput->Bind(wxEVT_LEFT_DCLICK, &MyRemoteFilePanel::OnPageInputDClick, this);
    itemBoxSizer4->Add(currentPageInput, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    nextPageBtn = new wxBitmapButton(itemPanel1, ID_BITMAPBUTTON7, itemPanel1->GetBitmapResource(wxT("right_btn.xpm")),
                                     wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW);
    itemBoxSizer4->Add(nextPageBtn, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

    this->Bind(wxEVT_THREAD, &MyRemoteFilePanel::OnThreadEvent, this);
    mainListCtrl->Bind(wxEVT_SIZE, &MyRemoteFilePanel::OnSizeChanged, this);
    mainListCtrl->Bind(wxEVT_LIST_COL_BEGIN_DRAG, &MyRemoteFilePanel::OnStartDrag, this);
    mainListCtrl->Bind(wxEVT_LIST_COL_END_DRAG, &MyRemoteFilePanel::OnEndDrag, this);
    prevPageBtn->Bind(wxEVT_BUTTON, &MyRemoteFilePanel::PrevBtnClicked, this);
    nextPageBtn->Bind(wxEVT_BUTTON, &MyRemoteFilePanel::NextBtnClicked, this);
    parentBtn->Bind(wxEVT_BUTTON, &MyRemoteFilePanel::ParentBtnClicked, this);
    refreshBtn->Bind(wxEVT_BUTTON, &MyRemoteFilePanel::RefreshBtnClicked, this);
    mainListCtrl->Bind(wxEVT_LIST_ITEM_ACTIVATED, &MyRemoteFilePanel::OnUserRemoteFileActivated, this);
    mainListCtrl->Bind(wxEVT_LEFT_DCLICK, &MyRemoteFilePanel::OnUserRemoteFileDClick, this);
    newDirectoryBtn->Bind(wxEVT_BUTTON, &MyRemoteFilePanel::NewDirectoryBtnClicked, this);
    //prevPageBtn->
    menu = new wxMenu();
	menu->Append(ID_VIEW_FILE_DETAIL, _("File Detail"));
    menu->Append(ID_DOWNLOAD_FILE, _("Download file"));
    menu->Append(ID_DELETE_FILE, _("Delete file"));
	
    menu->Bind(wxEVT_MENU, &MyRemoteFilePanel::OnCtrlListMenuClicked, this);
    mainListCtrl->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &MyRemoteFilePanel::OnItemRightClick, this);
////@end NyRemoteFilePanel content construction
}


/*
 * Should we show tooltips?
 */

bool MyRemoteFilePanel::ShowToolTips() {
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap MyRemoteFilePanel::GetBitmapResource(const wxString &name) {
    // Bitmap retrieval
////@begin NyRemoteFilePanel bitmap retrieval
    wxUnusedVar(name);
    if (name == wxT("refresh.xpm")) {
        wxBitmap bitmap(refresh_xpm);
        return bitmap;
    } else if (name == wxT("up_level.xpm")) {
        wxBitmap bitmap(up_level_xpm);
        return bitmap;
    } else if (name == wxT("search.xpm")) {
        wxBitmap bitmap(search_xpm);
        return bitmap;
    } else if (name == wxT("new_directory.xpm")) {
        wxBitmap bitmap(new_directory_xpm);
        return bitmap;
    } else if (name == wxT("delete_trash.xpm")) {
        wxBitmap bitmap(delete_trash_xpm);
        return bitmap;
    } else if (name == wxT("copy.xpm")) {
        wxBitmap bitmap(copy_xpm);
        return bitmap;
    } else if (name == wxT("left_btn.xpm")) {
        wxBitmap bitmap(left_btn_xpm);
        return bitmap;
    } else if (name == wxT("right_btn.xpm")) {
        wxBitmap bitmap(right_btn_xpm);
        return bitmap;
    }
    return wxNullBitmap;
////@end NyRemoteFilePanel bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon MyRemoteFilePanel::GetIconResource(const wxString &name) {
    // Icon retrieval
////@begin NyRemoteFilePanel icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end NyRemoteFilePanel icon retrieval
}

void MyRemoteFilePanel::RefreshData(const bool& force) {
	if (!force && waitPage) {
		return;
	}
    auto &fileModel = RemoteFileModel::Instance();
	waitPage = true;
    fileModel.GetPage(this);
}

void MyRemoteFilePanel::OnThreadEvent(wxThreadEvent &event) {
    // D
    switch (event.GetInt()) {
        case USER_REMOTE_FILE_PAGE_DATA: {
            auto payload = event.GetPayload<ResponseEntity>();
            //if(!payload.success)
            RefreshListData(payload);
            break;
        }
        case USER_REMOTE_DIRECTORY_CREATE: {
            auto &fileModel = RemoteFileModel::Instance();
            fileModel.GetPage(this);
            break;
        }
        case USER_REMOTE_FILE_DELETE: {
            auto &fileModel = RemoteFileModel::Instance();
            fileModel.GetPage(this);
            break;
        }
        default:
            event.Skip();
    }
}

void MyRemoteFilePanel::OnUserRemoteFileDClick(wxMouseEvent &event) {
    if (mainListCtrl->GetSelectedItemCount() > 0) {
        event.Skip();
    } else {
        auto &fileModel = RemoteFileModel::Instance();
        fileModel.GetPageById(this, fileModel.GetParent(), 1);
    }

}

void MyRemoteFilePanel::OnItemRightClick(const wxListEvent &event) {
    mainListCtrl->PopupMenu(menu);
}

void MyRemoteFilePanel::OnCtrlListMenuClicked(const wxCommandEvent &event) {
	//// Get Select
	long itemIndex = -1;
	std::vector<long> selectedItems;
	auto &fileModel = RemoteFileModel::Instance();
	auto list = fileModel.GetCurrentList();
	long count = list.size();
	while ((itemIndex = mainListCtrl->GetNextItem(itemIndex,
		wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND) {
		// Got the selected item index
		//wxLogDebug(listControl->GetItemText(itemIndex));
		// got
		//auto list = fileModel.GetCurrentList();
		
		if (itemIndex >= count) {
			break;
		}
		auto& fileData = list.at(static_cast<web::json::array::size_type>(itemIndex));
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
	//
	if (event.GetId() == ID_DOWNLOAD_FILE) {
		wxString dirHome;
		wxGetHomeDir(&dirHome);
		//long style = wxDD_DEFAULT_STYLE,
		//auto = list.at(fileData)
		wxDirDialog dialog(this, _("Select Directory"), dirHome, wxDD_DEFAULT_STYLE, wxDefaultPosition,
			wxDefaultSize, _T("Select Directory"));

		if (dialog.ShowModal() == wxID_OK) {
			for (auto idx : selectedItems) {
				auto fileData = list.at(idx);
				SyncModel::Instance().StartDownloadFile(fileData, dialog.GetPath(), fileModel.GetCurrentPath());
			}
			
		}
	}
	else if (event.GetId() == ID_DELETE_FILE) {

		if (selectedItems.size() < 2) {
			if (selectedItems.size() > 0 && list.size() > 0) {
				auto fileData = list.at(selectedItems[0]);
				wxMessageDialog dialog(this, wxString::Format(_T("Delete file %s"), fileData.at(U("name")).as_string()), _("Confirm Delete File"), wxOK | wxCANCEL | wxCENTRE);

				if (dialog.ShowModal() == wxID_OK) {
					RemoteFileModel::Instance().DeleteFile(this, fileData.at(U("path")).as_string());
					//SyncModel::Instance().StartDownloadFile(fileData, fileData.at(U("name")).as_string(), fileModel.GetCurrentPath());
				}
			}

			//ShowTaskDetail(fileData);
		}
		else {
			wxMessageDialog dialog(this, wxString::Format(_T("Delete file %ld files?"), selectedItems.size()), _("Confirm Delete Files"), wxOK | wxCANCEL | wxCENTRE);

			if (dialog.ShowModal() == wxID_OK) {
				auto json = web::json::value::array();
				long i = 0;
				for (auto idx : selectedItems) {
					auto fileData = list.at(idx);
					json[i] = fileData.at(U("path"));
					i++;
				}
				RemoteFileModel::Instance().DeleteFiles(this, json);
				//SyncModel::Instance().StartDownloadFile(fileData, fileData.at(U("name")).as_string(), fileModel.GetCurrentPath());
			}
		}
	}
	else if (event.GetId() == ID_VIEW_FILE_DETAIL) {
		if (!selectedItems.empty() && list.size() > 0) {
			auto fInfo = list.at(static_cast<web::json::array::size_type>(selectedItems[0]));
			if (!fInfo.is_null()) {
				auto fileDetailDialog = FileDetail(this, fInfo);
				fileDetailDialog.ShowModal();
			}
		}
	}
}


void MyRemoteFilePanel::OnUserRemoteFileActivated(wxListEvent &event) {
    long index = event.GetIndex();
    auto &fileModel = RemoteFileModel::Instance();
    auto list = fileModel.GetCurrentList();
    long count = list.size();
    if (index >= count) {
        fileModel.GetPageById(this, fileModel.GetParent(), 1);
        return;
    }
    auto fileData = list.at(static_cast<web::json::array::size_type>(index));
    if (fileData.is_null()) {
        fileModel.GetPageById(this, fileModel.GetParent(), 1);
        return;
    }
    utility::string_t currentPath = fileData.at(U("path")).as_string();
    int type = fileData.at(U("type")).as_integer();
    if (type == 1) {
        fileModel.GetPage(this, currentPath, 1);
    } else if (type == -1) {

        wxMessageBox(wxT("This file is in invalid.\nThere's something wrong with our server."), _T("ErrorFile"),
                     wxICON_ERROR);
        //ShowModal())msg->Show();
    } else {
        if (fileData.has_field(U("preview"))) {
            int preview = fileData.at(U("preview")).as_integer();
            if (preview == 1000) {
                if (videoPreviewFrame == nullptr) {
                    auto system = wxPlatformInfo::Get().GetOperatingSystemId();
                    if (system & wxOS_MAC) {
                        auto text = wxGetCwd() + wxFileName::GetPathSeparator() + wxT("plugins");
                        if (!wxDirExists(text)) {
                            text = "/Applications/VLC.app/Contents/MacOS/plugins";
                        }
                        if (!wxDirExists(text)) {
                            wxMessageBox(_("Could not found LibVLC plugins"), _("VLC init fail"));
                            // this->Close();
                            return;
                        }
                        //
#ifndef __WINDOWS__
                        setenv("VLC_PLUGIN_PATH", text.c_str(), 1);
#endif // !__WINDOWS__
                        // Can't do it under windows, Under windows, we have to search plugins manually.
                    }
                    videoPreviewFrame = new VideoPreviewFrame(currentPath, this);
                } else {
                    videoPreviewFrame->SetPath(currentPath);
                }
                videoPreviewFrame->GetVideoStream();
                videoPreviewFrame->ShowModal();
                //std::cout << "exit" << std::endl;
                videoPreviewFrame->Clean();
                //std::cout << "exit3" << std::endl;
            }
        }
    }
    /*

if (item == nullptr) {
    fileModel.GetPageById(this, fileModel.GetParent());
    return;
}
auto row = fileModel.GetRow(item);
wxDataViewListStoreLine *line = fileModel.m_data[row];

auto path = line->m_values.at(5).GetString();
auto type = line->m_values.at(6).GetInteger();
if (type == 1) {
    fileModel.GetPage(this, path, 1);
}
else if (type == -1) {
    wxMessageBox(wxT("This file is in invalid.\nThere's something wrong with our server."), _T("ErrorFile"), wxICON_INFORMATION);
    //ShowModal())msg->Show();
}
//
//std::cout << data->at(0).GetString() << std::endl;
*/
}

void MyRemoteFilePanel::RefreshBtnClicked(wxCommandEvent &event) {
    auto &fileModel = RemoteFileModel::Instance();
    fileModel.GetPage(this);

}

void MyRemoteFilePanel::NewDirectoryBtnClicked(wxCommandEvent &event) {
    if (this->addDirectoryDialog == nullptr) {
        addDirectoryDialog = new AddDirectoryDialog(this, wxID_ANY);
        addDirectoryDialog->Iconize(false);
        addDirectoryDialog->SetLabel(_("New Directory"));
    }

    // loginFrame->SetTips(text);
    // login_frame->Show(true);
    // loginFrame->Raise();  // doesn't seem to work
    // loginFrame->SetFocus();  // does nothing
    auto const &result = addDirectoryDialog->ShowModal(); // this by itself doesn't work
    if (result == wxID_OK) {
        // check validate
        const auto &userInput = addDirectoryDialog->getUserInput();
        //TryLogin(userInput, Utf8MD5(userPassword));
        auto &fileModel = RemoteFileModel::Instance();
        fileModel.CreateNewDirectory(this, userInput);
    }
}

void MyRemoteFilePanel::ParentBtnClicked(wxCommandEvent &event) {
    auto &fileModel = RemoteFileModel::Instance();
    auto parent = fileModel.GetParent();
    if (!parent.empty()) {
        fileModel.GetPageById(this, parent, 1);
    }

}

void MyRemoteFilePanel::PrevBtnClicked(wxCommandEvent &event) {
    auto &fileModel = RemoteFileModel::Instance();
    auto page = fileModel.GetCurrentPage();
    if (page > 1) {
        fileModel.GetPage(this, fileModel.GetCurrentPath(), page - 1);
    }
}

void MyRemoteFilePanel::NextBtnClicked(wxCommandEvent &event) {
    auto &fileModel = RemoteFileModel::Instance();
    auto page = fileModel.GetCurrentPage();
    if (page < fileModel.GetTotalPage()) {
        fileModel.GetPage(this, fileModel.GetCurrentPath(), page + 1);
    }
}

void MyRemoteFilePanel::ResetCurrentPathDisplay() {
    auto &fileModel = RemoteFileModel::Instance();
    auto const &currentPage = fileModel.GetCurrentPage();
    auto const &totalPage = fileModel.GetTotalPage();
    currentPageInput->SetValue(wxString::Format(_T("%d / %d"), currentPage, totalPage));
    currentPageInput->SetEditable(false);
    prevPageBtn->Enable(currentPage > 1);
    nextPageBtn->Enable(currentPage < totalPage);
    pathInput->SetValue(fileModel.GetCurrentPath());
    parentBtn->Enable(!fileModel.GetParent().empty());
}

void MyRemoteFilePanel::OnPageInputDClick(wxMouseEvent &event) {
    //event.Get
    auto &fileModel = RemoteFileModel::Instance();
    currentPageInput->SetValue(wxString::Format(_T("%d"), fileModel.GetCurrentPage()));
    currentPageInput->SetEditable(true);
    currentPageInput->Bind(wxEVT_KILL_FOCUS, &MyRemoteFilePanel::OnPageInputKillFocus, this);
}

void MyRemoteFilePanel::OnPageInputKillFocus(wxFocusEvent &event) {

    currentPageInput->Unbind(wxEVT_KILL_FOCUS, &MyRemoteFilePanel::OnPageInputKillFocus, this);
    currentPageInput->SetEditable(false);
    auto &fileModel = RemoteFileModel::Instance();
    wxString input = currentPageInput->GetValue();
    int c = wxAtoi(input);
    if (c > 0 && c != fileModel.GetCurrentPage() && c <= fileModel.GetTotalPage() && c != fileModel.GetCurrentPage()) {
        fileModel.GetPage(this, fileModel.GetCurrentPath(), c);
    } else {
        ResetCurrentPathDisplay();
    }

}

void MyRemoteFilePanel::RefreshListData(const ResponseEntity &payload) {
	waitPage = false;
    if (payload.code == U("FILE_NOT_FOUND")) {
        wxMessageBox(_("Destination invalid.\nThere parent directory not found.\nAuto goto root dir."),
                     _("Cannot go to directory"), wxICON_INFORMATION);
        RemoteFileModel::Instance().GetPage(this, U("/"), 1);
        return;
    }
    if(!payload.success){
        return;
    }
    // check if a file
    if (payload.result.has_field(U("info"))) {
        const web::json::value &info = payload.result.at(U("info"));
        if (info.has_field(U("type"))) {
            const int &type = info.at(U("type")).as_integer();
            if (type == 0) {
                //wxMessageBox("Ahhh");
                if (info.has_field(U("parent"))) {
                    const auto &parent = info.at(U("parent")).as_string();
                    if (parent.empty()) {
                        RemoteFileModel::Instance().GetPage(this, U("/"), 1);
                        return;
                    } else {
                        RemoteFileModel::Instance().GetPageById(this, parent, 1);
                        return;
                    }
                }
                RemoteFileModel::Instance().GetPage(this, U("/"), 1);
                return;
            }
        }
    }
    //
    web::json::array list = payload.result.at(U("list")).as_array();
	
    // model->AppendItem( data ,1);
    auto model = &RemoteFileModel::Instance();
	auto refresh = model->GetCurrentList().size() != list.size();
    auto dirInfo = payload.result.at(U("info"));
    auto currentPath = dirInfo.at(U("path")).as_string();
    auto currentId = dirInfo.at(U("uuid")).as_string();
    auto parent = dirInfo.at(U("parent")).as_string();
    auto currentPage = payload.result.at(U("page")).as_integer();
    auto currentPageSize = payload.result.at(U("pageSize")).as_integer();
    auto totalPage = payload.result.at(U("totalPage")).as_integer();
    model->UpdateCurrentLocation(currentPath, currentId, currentPage, currentPageSize, totalPage, parent, list);
    /*
     * "Type" --- "Filename" --- "FileSize" --- "FileType"
     */
    long cur = 0;
    //long index = 0;
	if (refresh) {
		mainListCtrl->Hide();
		mainListCtrl->DeleteAllItems();
	}
   
    for (const auto &i : list) {
        // create item
        wxListItem itemCol;
        itemCol.SetId(cur);
        // col 1 type
        itemCol.SetColumn(0);
        auto cx = i.at(U("type")).as_integer();
        auto lock = i.at(U("locking")).as_bool();
        if (cx == 1) {
            if(lock){
                itemCol.SetText(_T(" [+][L]"));
            }else{
                itemCol.SetText(_T(" [+]"));
            }

        } else if (cx == -1) {
            itemCol.SetText(_T(" [E]"));
            itemCol.SetTextColour(*wxRED);
        } else {
            if(lock) {
                itemCol.SetText(_T(" [-][L]"));
            }else{
                itemCol.SetText(_T(" [-]"));
            }
        }
		if (refresh) {
			mainListCtrl->InsertItem(itemCol);
		}
		else {
			mainListCtrl->SetItem(cur, 0, itemCol.GetText());
		}
        // col1 filename

        mainListCtrl->SetItem(cur, 1, i.at(U("name")).as_string());
        // col 2 file size
        mainListCtrl->SetItem(cur, 2, ConvertSizeToDisplay(i.at(U("size")).as_number().to_int64()));
        // col3 mime
        mainListCtrl->SetItem(cur, 3, i.at(U("ext")).as_string());
        // col4 date
        std::time_t t = i.at(U("ctime")).as_number().to_int64() / 1000;
        mainListCtrl->SetItem(cur, 4, ConvertTimeToDisplay(t, "%Y/%m/%d %H:%M"));

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
	if (refresh) {
		mainListCtrl->Show();
		mainListCtrl->SetFocus();
	}
   
	ResetCurrentPathDisplay();

}

void MyRemoteFilePanel::OnSizeChanged(wxSizeEvent &event) {
    event.Skip();
    if (drag) {
        return;
    }
    //mainListCtrl->Hide();
    int panelWidth = mainListCtrl->GetSize().GetWidth();
    /*
     * "Type" --- "Filename" --- "FileSize" --- "FileType"
     */

    auto typeWidth = mainListCtrl->GetColumnWidth(0);
    //auto fileNameWidth = mainListCtrl->GetColumnWidth(1);
    auto fileSizeWidth = mainListCtrl->GetColumnWidth(2);
    auto fileTypeWidth = mainListCtrl->GetColumnWidth(3);
    auto fileTimeWidth = mainListCtrl->GetColumnWidth(4);
    auto s2 = 9 * 2;
    // wxBorder broder = userRemoteFilePage->GetBorder();
    // broder.
    auto diff = panelWidth - typeWidth - fileSizeWidth - fileTypeWidth - fileTimeWidth - s2;
    if (diff > 0) {
        //nameCol->SetWidth(diff);
        mainListCtrl->SetColumnWidth(1, diff);
    }
    // mainListCtrl->Show();
    // std::cout << mainListCtrl->GetCharWidth() << " x ";
    // std::cout << panelWidth << std::endl;
}

void MyRemoteFilePanel::OnStartDrag(wxListEvent &event) {
    event.Skip();
    drag = true;
}

void MyRemoteFilePanel::OnEndDrag(wxListEvent &event) {
    event.Skip();
    drag = false;

}

void MyRemoteFilePanel::UpdateSpaceCapacity(const long long &spaceUsed, const long long &spaceCapacity) {
    this->spaceUsed = spaceUsed;
    this->spaceCapacity = spaceCapacity;
    capacityText->SetLabel(
            wxString::Format(_("%s / %s"), ConvertSizeToDisplay(spaceUsed), ConvertSizeToDisplay(spaceCapacity)));
}

void MyRemoteFilePanel::DoOpenFiles(const wxArrayString &fileNames) {
    /*
    for (size_t i = 0; i < fileNames.GetCount(); ++i)
    {
        // m_list.AddToPlayList(files[i]);
        //std::cout << "Drag file:" << fileNames[i] << std::endl;
        auto path = RemoteFileModel::Instance().GetCurrentPath();
    }
     */
    SyncModel::Instance().StartUploadFile(fileNames, RemoteFileModel::Instance().GetCurrentPath());
}
