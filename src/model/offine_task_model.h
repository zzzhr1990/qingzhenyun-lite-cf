#ifndef FUCK_REMOTE_DOWNLOAD_TASK_MODEL_H
#define FUCK_REMOTE_DOWNLOAD_TASK_MODEL_H
#include "wx/wxprec.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include "cpprest/http_client.h"
class OfflineDownloadTaskModel  {
public:
	static OfflineDownloadTaskModel& Instance();

	int GetCurrentPage() {
		return current_page;
	}
	void SetCurrentPage(const int &page = 1) {
		if (page > 0) {
			current_page = page;
		}
	}
	int GetTotalPage() {
		return total_page;
	}
	int GetCurrentPageSize() {
		return current_page_size;
	}

	void GetPage(wxWindow* handler, const int &page = -1, const int &pageSize = -1);
	void StartUrl(wxWindow * handler, const utility::string_t& url);
	void StartTask(wxWindow * handler, const utility::string_t& taskHash, const utility::string_t & savePath,const utility::string_t& copyFile);
	void DeleteTasks(wxWindow * handler, const web::json::value & tasks);
	void UpdateCurrent(const int &page, const int &pageSize, const int &totalPage, const web::json::array& list);
	web::json::array GetCurrentList() {
		return this->currentList;
	}

private:
	int current_page = 1;
	int current_page_size = 50;
	int total_page = 1;
	web::json::array currentList = web::json::value::array().as_array();
};



#endif //FUCK_REMOTE_DOWNLOAD_TASK_MODEL_H