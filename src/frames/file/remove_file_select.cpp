#include <utility>

/////////////////////////////////////////////////////////////////////////////
// Name:        RemoteFileSelect.cpp
// Purpose:
// Author:
// Modified by:
// Created:     Tue 30 Oct 02:43:54 2018
// RCS-ID:
// Copyright:
// Licence:
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".

////@begin includes
#include "wx/imaglist.h"
////@end includes

#include "remove_file_select.h"
#include "../../api_model/api_remote_file_model.h"
#include "add_directory_dialog.h"
#include "../../api_model/api_user_model.h"
////@begin XPM images
////@end XPM images


/*
 * RemoteFileSelect type definition
 */

IMPLEMENT_DYNAMIC_CLASS( RemoteFileSelect, wxDialog )


/*
 * RemoteFileSelect event table definition
 */

BEGIN_EVENT_TABLE( RemoteFileSelect, wxDialog )

////@begin remotefileselect event table entries
    // EVT_CLOSE( RemoteFileSelect::OnCloseWindow )
////@end remotefileselect event table entries

END_EVENT_TABLE()


/*
 * RemoteFileSelect constructors
 */


RemoteFileSelect::RemoteFileSelect()
{
    Init();
}

RemoteFileSelect::RemoteFileSelect( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
    //Append root
    this->AddRootDirectory();
}



/*
 * RemoteFileSelect creator
 */

bool RemoteFileSelect::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin remotefileselect creation
    SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY|wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end remotefileselect creation
    return true;
}


/*
 * RemoteFileSelect destructor
 */

RemoteFileSelect::~RemoteFileSelect()
{
////@begin remotefileselect destruction

////@end remotefileselect destruction
}


/*
 * Member initialisation
 */

void RemoteFileSelect::Init()
{
////@begin remotefileselect member initialisation
////@end remotefileselect member initialisation
}


/*
 * Control creation for RemoteFileSelect
 */

void RemoteFileSelect::CreateControls()
{
////@begin remotefileselect content construction
    RemoteFileSelect* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer1, 0, wxGROW|wxALL, 5);

    wxStaticText* itemStaticText2 = new wxStaticText( itemDialog1, wxID_STATIC, _("Current"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add(itemStaticText2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    pathInput = new wxTextCtrl( itemDialog1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
    pathInput->SetEditable(false);
    itemBoxSizer1->Add(pathInput, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxButton* createNewDirectoryBtn = new wxButton( itemDialog1, wxID_ANY, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add(createNewDirectoryBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    mainTreeCtrl = new wxTreeCtrl( itemDialog1, wxID_ANY, wxDefaultPosition, wxSize(100, 100), wxTR_DEFAULT_STYLE | wxSUNKEN_BORDER );
    itemBoxSizer2->Add(mainTreeCtrl, 1, wxGROW|wxALL, 5);

    wxStaticLine* itemStaticLine6 = new wxStaticLine( itemDialog1, wxID_STATIC, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
    itemBoxSizer2->Add(itemStaticLine6, 0, wxGROW|wxALL, 5);

    //this->CreateStdDialogButtonSizer(wxID_OK | wxID_CANCEL);



    wxStdDialogButtonSizer* itemStdDialogButtonSizer7 = new wxStdDialogButtonSizer;

    itemBoxSizer2->Add(itemStdDialogButtonSizer7, 0, wxGROW|wxALL, 5);
    wxButton* itemButton8 = new wxButton( itemDialog1, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer7->AddButton(itemButton8);

    wxButton* itemButton9 = new wxButton( itemDialog1, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
    itemStdDialogButtonSizer7->AddButton(itemButton9);

    itemStdDialogButtonSizer7->Realize();

    // add evt..
    this->Bind(wxEVT_TREE_ITEM_EXPANDING, &RemoteFileSelect::OnTreeExpanding, this);

    this->Bind(wxEVT_TREE_SEL_CHANGED, &RemoteFileSelect::OnTreeSelectChanged, this);

	this->Bind(wxEVT_TREE_ITEM_ACTIVATED, &RemoteFileSelect::OnTreeSelectActivated, this);

    createNewDirectoryBtn->Bind(wxEVT_BUTTON, &RemoteFileSelect::OnCreateDirectoryBtnClicked, this);
////@end remotefileselect content construction
}


/*
 * Should we show tooltips?
 */

bool RemoteFileSelect::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap RemoteFileSelect::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin remotefileselect bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end remotefileselect bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon RemoteFileSelect::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin remotefileselect icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end remotefileselect icon retrieval
}

void RemoteFileSelect::EndModal(int retCode) {
    wxDialog::EndModal(retCode);
    get_path_cancellation.cancel();
}

void RemoteFileSelect::AddRootDirectory() {
    auto * rootData = new simple_directory_info(_XPLATSTR("/"));
    auto root_id = this->mainTreeCtrl->AddRoot(_("Root Directory"),-1,-1,rootData);
    auto * data = new simple_directory_info(_XPLATSTR("../"));
    this->mainTreeCtrl->AppendItem(root_id,_("Fetching Data"),-1,-1,data);
    //this->mainTreeCtrl->GetItemData(root_id)->GetId();
    pathInput->SetValue(rootData->get_path());
}

void RemoteFileSelect::OnTreeExpanding(wxTreeEvent &evt) {
    //evt.Veto();
    auto data = this->mainTreeCtrl->GetItemData(evt.GetItem());
    if(data != nullptr){
        // exp...
        auto directory_data = (simple_directory_info*) data;
        if(!directory_data->get_inited()){
            evt.Veto();
            this->get_path_cancellation.cancel();
            this->get_path_cancellation = pplx::cancellation_token_source();
            auto task = qingzhen::api::api_remote_file_model::instance()
                    .refresh_path_list_ex(this->get_path_cancellation,directory_data->get_path(), -1, -1, 1);
            task.then([this,directory_data](response_entity entity){
                if(!entity.is_cancelled() && entity.success){
                    // create new data
                    auto &result = entity.result;
                    if(result.has_field(_XPLATSTR("info"))){
                        this->CallAfter([this,result, directory_data](){ this -> OnDirectoryDataReceived(result, directory_data->GetId());});
                    }
                }
            });
        }
    }
}

void RemoteFileSelect::OnDirectoryDataReceived(web::json::value result,wxTreeItemId selection) {
    //auto selection = this->mainTreeCtrl->GetSelection();
    if(selection != nullptr){
        auto item_data = this->mainTreeCtrl->GetItemData(selection);
        if(item_data != nullptr){
            auto directory_info = (simple_directory_info*)item_data;
            //
            auto info = result[_XPLATSTR("info")];
            auto path = info[_XPLATSTR("path")].as_string();
            auto name = info[_XPLATSTR("path")].as_string();
            if(directory_info->get_path() == path){
                directory_info->set_inited(true);
                this->mainTreeCtrl->DeleteChildren(selection);
                auto current_list = result[_XPLATSTR("list")].as_array();
                if(current_list.size() > 0){
                    for(auto &val : current_list){
                        utility::string_t sub_name = val[_XPLATSTR("name")].as_string();
                        utility::string_t sub_path = val[_XPLATSTR("path")].as_string();
                        wxString display_name = sub_name;
                        auto * data = new simple_directory_info(sub_path,sub_name);
                        data->set_inited(false);
                        auto sub = this->mainTreeCtrl->AppendItem(selection, display_name,-1,-1,data);
                        auto * data_sub = new simple_directory_info(_XPLATSTR("../"));
                        this->mainTreeCtrl->AppendItem(sub,_("Fetching Data"),-1,-1,data_sub);
                    }
                    this->mainTreeCtrl->Expand(selection);
                }

            }
        }
    }
}

void RemoteFileSelect::OnTreeSelectChanged(wxTreeEvent &evt) {
    auto data = this->mainTreeCtrl->GetItemData(evt.GetItem());
    if(data != nullptr) {
        // exp...
        auto directory_data = (simple_directory_info *) data;
        pathInput->SetValue(directory_data->get_path());
    }
}

//OnTreeSelectActivated
void RemoteFileSelect::OnTreeSelectActivated(wxTreeEvent &evt) {
	auto id = evt.GetItem();
	if (this->mainTreeCtrl->IsExpanded(id)) {
		this->mainTreeCtrl->Collapse(id);
	}
	else {
		this->mainTreeCtrl->Expand(evt.GetItem());
	}
}

void RemoteFileSelect::OnCreateDirectoryBtnClicked(wxCommandEvent &event) {
    auto select = this->mainTreeCtrl->GetSelection();
    if(select == nullptr){
        return;
    }
    auto data = this->mainTreeCtrl->GetItemData( select);
    if(data != nullptr) {
        // exp...
        auto directory_data = (simple_directory_info *) data;
        auto * add_dialog = new AddDirectoryDialog(this);
        add_dialog->ShowModal();
        utility::string_t input = add_dialog->GetUserInput();
        //
        if(!input.empty()){
            this->get_path_cancellation.cancel();
            this->get_path_cancellation = pplx::cancellation_token_source();
            auto task = qingzhen::api::api_remote_file_model::instance().create_new_directory(get_path_cancellation,input ,directory_data->get_path());
            task.then([select,this,directory_data](response_entity entity){
               if(entity.success){
                   this->CallAfter([select,this,directory_data](){
                       directory_data->set_inited(false);
                       this->mainTreeCtrl->Collapse(select);
                       auto * data_sub = new simple_directory_info(_XPLATSTR("../"));
                       this->mainTreeCtrl->AppendItem(select,_("Fetching Data"),-1,-1,data_sub);
                       //this->mainTreeCtrl->DeleteChildren(select);
                       this->mainTreeCtrl->Expand(select);
                   });
               }
            });
        }
    }
}

wxString RemoteFileSelect::GetUserInput() {
    return pathInput->GetValue();
}
