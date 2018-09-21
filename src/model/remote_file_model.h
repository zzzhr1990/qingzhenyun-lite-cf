//
// Created by zzzhr on 2018/9/4.
//

#ifndef QINGZHENYUN_LITE_REMOTE_FILE_MODEL_H
#define QINGZHENYUN_LITE_REMOTE_FILE_MODEL_H

#include <pplx/pplxtasks.h>
#include "../util/common_api.h"
#include "cpprest/http_client.h"
#include "wx/wxprec.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include "../common/common_event_ids.h"

class RemoteFileModel {
public:
    static RemoteFileModel& Instance();
    void GetPage(wxWindow* handler, const utility::string_t &path = U(""), const int &page = -1, const int &pageSize = -1, const int &type = -1);
    void GetPageById(wxWindow* handler, const utility::string_t &uuid, const int &page = -1, const int &pageSize = -1, const int &type = -1);
	void CreateNewDirectory(wxWindow * handler, const utility::string_t & directoryName, const utility::string_t & parent = U(""));
	void DeleteFile(wxWindow * handler, const utility::string_t & filePath);
	void DeleteFiles(wxWindow * handler, const web::json::value & filePaths);
	void GetPreviewInfo(wxWindow * handler, const utility::string_t & path);
	void GetFileInfo(wxWindow * handler, const utility::string_t & path);
    /*
    static void SendThreadMessage(wxWindow * handler, ResponseEntity v){
    }
     */
	void SetCurrentPage(const int &page = 1) {
		if (page > 0) {
			current_page = page;
		}
	}
	void SetCurrentPath(const utility::string_t &path) {
		current_path = path;
	}
    int GetCurrentPage(){
        return current_page;
    }
    int GetTotalPage(){
        return total_page;
    }
    int GetCurrentPageSize(){
        return current_page_size;
    }

    utility::string_t GetParent(){
        return current_parent;
    }

    void UpdateCurrentLocation(const utility::string_t &path, const utility::string_t &fileId, const int &page,
                               const int &pageSize, const int &totalPage, const utility::string_t &parent, const web::json::array& list);
    utility::string_t GetCurrentPath();

	web::json::array GetCurrentList() {
		return this->currentList;
	}

private:
    utility::string_t current_path = U("/");
    utility::string_t current_file_id = U("");
    int current_page = 1;
    int current_page_size = 40;
    int total_page = 1;
    utility::string_t current_parent = U("");
	web::json::array currentList = web::json::value::array().as_array();
	int currentOrder = -1;
};


#endif //QINGZHENYUN_LITE_REMOTE_FILE_MODEL_H
