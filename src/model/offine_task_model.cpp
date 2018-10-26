
#include "offine_task_model.h"
#include "cpprest/http_client.h"
#include "../util/common_api.h"
#include "../common/common_event_ids.h"

OfflineDownloadTaskModel& OfflineDownloadTaskModel::Instance() {
	static OfflineDownloadTaskModel c;
	return c;

}

void OfflineDownloadTaskModel::GetPage(wxWindow* handler, const int &page, const int &pageSize) {
	web::json::value request;
	//request[U("path")] = web::json::value::string(path.empty() ? current_path : path);
	request[U("page")] = web::json::value::number(page > 0 ? page : current_page);
	request[U("pageSize")] = web::json::value::number(pageSize > 0 ? pageSize : current_page_size);
	/*
	if(type > -1){
		request[U("type")] = web::json::value::number(type);
	}
	 */

	common_api::Instance().PostData(U("/v1/offline/page"), request).then([handler](response_entity v) {
		SendCommonThreadEvent(handler, USER_REMOTE_TASK_PAGE_DATA, v, true);
	});

}

void OfflineDownloadTaskModel::StartUrl(wxWindow* handler, const utility::string_t& url) {
	web::json::value request;
	request[U("url")] = web::json::value::string(url);
	common_api::Instance().PostData(U("/v1/offline/parseUrl"), request).then([handler](response_entity v) {
		SendCommonThreadEvent(handler, USER_REMOTE_TASK_URL_PARSED, v, true);
	});

}

void OfflineDownloadTaskModel::StartTask(wxWindow* handler,const utility::string_t& taskHash, const utility::string_t& savePath,const utility::string_t& copyFile) {
	web::json::value request;
	request[U("taskHash")] = web::json::value::string(taskHash);
	request[U("savePath")] = web::json::value::string(savePath);
	request[U("copyFile")] = web::json::value::string(copyFile);
	common_api::Instance().PostData(U("/v1/offline/start"), request).then([handler](response_entity v) {
		SendCommonThreadEvent(handler, USER_REMOTE_TASK_URL_START, v, true);
	});

}

void OfflineDownloadTaskModel::DeleteTasks(wxWindow *handler, const web::json::value &filePaths) {

	web::json::value request;
	//auto pathArray = web::json::value::object().array();
	request[U("taskId")] = filePaths;
	common_api::Instance().PostData(U("/v1/offline/remove"), request).then([handler](response_entity v) {
		//SendCommonThreadEvent(handler, USER_REMOTE_FILE_PAGE_DATA, v, true);
		SendCommonThreadEvent(handler, USER_REMOTE_TASK_DELETE, v, true);
	});
}


void OfflineDownloadTaskModel::UpdateCurrent(const int &page,
	const int &pageSize, const int &totalPage, const web::json::array& list) {
	this->current_page = page;
	this->current_page_size = pageSize;
	this->total_page = totalPage;
	this->currentList = list;
}