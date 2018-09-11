//
// Created by zzzhr on 2018/9/11.
//

#ifndef QINGZHENYUN_LITE_DOWNLOAD_TASK_H
#define QINGZHENYUN_LITE_DOWNLOAD_TASK_H

#include "tbb/concurrent_vector.h"
#include "single_url_task.h"
struct DownloadTask{
    tbb::concurrent_vector<SingleUrlTask> task;
    utility::size64_t fileSize;
    utility::size64_t processedSize;
    utility::string_t localPath;
    web::http::message_direction::direction direction;
    utility::string_t filename;
    utility::string_t remotePath;
};
#endif //QINGZHENYUN_LITE_DOWNLOAD_TASK_H
