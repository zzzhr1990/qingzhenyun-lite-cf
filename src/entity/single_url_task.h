//
// Created by zzzhr on 2018/9/11.
//

#ifndef QINGZHENYUN_LITE_SINGLE_URL_DOWNLOAD_TASK_H
#define QINGZHENYUN_LITE_SINGLE_URL_DOWNLOAD_TASK_H
#include <cpprest/http_client.h>
struct SingleUrlTask{
    utility::size64_t fileSize;
    utility::size64_t processedSize;
    utility::string_t localPath;
    web::http::message_direction::direction direction;
    utility::string_t filename;
    utility::string_t remotePath;
    int status;
};

#endif //QINGZHENYUN_LITE_SINGLE_URL_DOWNLOAD_TASK_H
