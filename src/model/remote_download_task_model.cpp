
#include "remote_download_task_model.h"
#include "cpprest/http_client.h"
#include "../util/common_api.h"
#include "../common/common_event_ids.h"

RemoteDownloadTaskModel& RemoteDownloadTaskModel::Instance() {
	static RemoteDownloadTaskModel c;
	return c;

}

void RemoteDownloadTaskModel::GetPage(wxWindow* handler, const int &page, const int &pageSize) {
	web::json::value request;
	//request[U("path")] = web::json::value::string(path.empty() ? current_path : path);
	request[U("page")] = web::json::value::number(page > 0 ? page : current_page);
	request[U("pageSize")] = web::json::value::number(pageSize > 0 ? pageSize : current_page_size);
	/*
	if(type > -1){
		request[U("type")] = web::json::value::number(type);
	}
	 */

	CommonApi::Instance().PostData(U("/v1/offline/page"), request).then([handler](ResponseEntity v) {
		SendCommonThreadEvent(handler, USER_REMOTE_TASK_PAGE_DATA, v, true);
	});

}

void RemoteDownloadTaskModel::StartUrl(wxWindow* handler, const utility::string_t& url) {
	web::json::value request;
	request[U("url")] = web::json::value::string(url);
	CommonApi::Instance().PostData(U("/v1/offline/parseUrl"), request).then([handler](ResponseEntity v) {
		SendCommonThreadEvent(handler, USER_REMOTE_TASK_URL_PARSED, v, true);
	});

}

void RemoteDownloadTaskModel::StartTask(wxWindow* handler,const utility::string_t& taskHash, const utility::string_t& savePath,const utility::string_t& copyFile) {
	web::json::value request;
	request[U("taskHash")] = web::json::value::string(taskHash);
	request[U("savePath")] = web::json::value::string(savePath);
	request[U("copyFile")] = web::json::value::string(copyFile);
	CommonApi::Instance().PostData(U("/v1/offline/start"), request).then([handler](ResponseEntity v) {
		SendCommonThreadEvent(handler, USER_REMOTE_TASK_URL_START, v, true);
	});

}

void RemoteDownloadTaskModel::UpdateCurrent(const int &page,
	const int &pageSize, const int &totalPage, const web::json::array& list) {
	this->current_page = page;
	this->current_page_size = pageSize;
	this->total_page = totalPage;
	this->currentList = list;
}