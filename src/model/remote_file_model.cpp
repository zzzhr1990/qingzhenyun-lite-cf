//
// Created by zzzhr on 2018/9/4.
//

#include "remote_file_model.h"

RemoteFileModel &RemoteFileModel::Instance() {
    static RemoteFileModel c;
    return c;
}

void RemoteFileModel::GetPage(wxWindow *handler, const utility::string_t &path, const int &page, const int &pageSize,
                              const int &type) {
    web::json::value request;
    request[U("path")] = web::json::value::string(path.empty() ? current_path : path);
    request[U("page")] = web::json::value::number(page > 0 ? page : current_page);
    request[U("pageSize")] = web::json::value::number(pageSize > 0 ? pageSize : current_page_size);
    request[U("order")] = web::json::value::number(currentOrder);
    if (type > -1) {
        request[U("type")] = web::json::value::number(type);
    }

    common_api::Instance().PostData(U("/v1/files/page"), request).then([handler](response_entity v) {
        SendCommonThreadEvent(handler, USER_REMOTE_FILE_PAGE_DATA, v, true);
    });

}

void
RemoteFileModel::GetPageById(wxWindow *handler, const utility::string_t &uuid, const int &page, const int &pageSize,
                             const int &type) {
    web::json::value request;
    request[U("uuid")] = web::json::value::string(uuid);
    request[U("page")] = web::json::value::number(page > 0 ? page : current_page);
    request[U("pageSize")] = web::json::value::number(pageSize > 0 ? pageSize : current_page_size);
    request[U("order")] = web::json::value::number(currentOrder);
    if (type > -1) {
        request[U("type")] = web::json::value::number(type);
    }

    common_api::Instance().PostData(U("/v1/files/page"), request).then([handler](response_entity v) {
        SendCommonThreadEvent(handler, USER_REMOTE_FILE_PAGE_DATA, v, true);
    });

}

void RemoteFileModel::CreateNewDirectory(wxWindow *handler, const utility::string_t &directoryName,
                                         const utility::string_t &parent) {
    web::json::value request;
    request[U("parent")] = web::json::value::string(parent.empty() ? this->current_file_id : parent);
    request[U("name")] = web::json::value::string(directoryName);

    common_api::Instance().PostData(U("/v1/files/createDirectory"), request).then([handler](response_entity v) {
        //SendCommonThreadEvent(handler, USER_REMOTE_FILE_PAGE_DATA, v, true);
        SendCommonThreadEvent(handler, USER_REMOTE_DIRECTORY_CREATE, v, true);
    });

}

void RemoteFileModel::GetPreviewInfo(wxWindow *handler, const utility::string_t &path) {
    web::json::value request;
    request[U("path")] = web::json::value::string(path);
    //request[U("name")] = web::json::value::string(directoryName);

    common_api::Instance().PostData(U("/v1/preview/media"), request).then([handler](response_entity v) {
        SendCommonThreadEvent(handler, USER_PREVIEW_INFO, v, true);
    });

}

utility::string_t RemoteFileModel::GetCurrentPath() {
    return current_path;
}

void
RemoteFileModel::UpdateCurrentLocation(const utility::string_t &path, const utility::string_t &fileId, const int &page,
                                       const int &pageSize, const int &totalPage, const utility::string_t &parent,
                                       const web::json::array &list) {
    this->current_path = path;
    this->current_file_id = fileId;
    this->current_page = page;
    this->current_page_size = pageSize;
    this->total_page = totalPage;
    this->current_parent = parent;
    this->currentList = list;
}

void RemoteFileModel::GetFileInfo(wxWindow *handler, const utility::string_t &path) {
    web::json::value request;
    request[U("path")] = web::json::value::string(path);
    //request[U("name")] = web::json::value::string(directoryName);

    common_api::Instance().PostData(U("/v1/files/get"), request).then([handler](response_entity v) {
        SendCommonThreadEvent(handler, USER_REMOTE_FILE_INFO, v, true);
    });

}

void RemoteFileModel::DeleteFile(wxWindow *handler, const utility::string_t &filePath) {

    web::json::value request;
    request[U("path")] = web::json::value::string(filePath);
    common_api::Instance().PostData(U("/v1/files/remove"), request).then([handler](response_entity v) {
        //SendCommonThreadEvent(handler, USER_REMOTE_FILE_PAGE_DATA, v, true);
        SendCommonThreadEvent(handler, USER_REMOTE_FILE_DELETE, v, true);
    });
}

void RemoteFileModel::DeleteFiles(wxWindow *handler, const web::json::value &filePaths) {

    web::json::value request;
    //auto pathArray = web::json::value::object().array();
    request[U("path")] = filePaths;
    common_api::Instance().PostData(U("/v1/files/remove"), request).then([handler](response_entity v) {
        //SendCommonThreadEvent(handler, USER_REMOTE_FILE_PAGE_DATA, v, true);
        SendCommonThreadEvent(handler, USER_REMOTE_FILE_DELETE, v, true);
    });
}
