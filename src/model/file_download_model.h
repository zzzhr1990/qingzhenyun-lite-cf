//
// Created by zzzhr on 2018/9/10.
//

#ifndef QINGZHENYUN_LITE_FILE_DOWNLOAD_MODEL_H
#define QINGZHENYUN_LITE_FILE_DOWNLOAD_MODEL_H

#include "cpprest/http_client.h"

class FileDownloadModel {
public:
    static FileDownloadModel& Instance();
    void StartDownloadFile(const web::json::value & value);
    void DownloadTestFile(const utility::string_t& url);

private:
    void DownloadSingleFile(const web::json::value & value);
};


#endif //QINGZHENYUN_LITE_FILE_DOWNLOAD_MODEL_H
