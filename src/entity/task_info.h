//
// Created by zzzhr on 2018/9/11.
//

#ifndef QINGZHENYUN_LITE_SINGLE_URL_DOWNLOAD_TASK_H
#define QINGZHENYUN_LITE_SINGLE_URL_DOWNLOAD_TASK_H

#include <cpprest/http_client.h>

#ifdef U
#undef U

#include <tbb/concurrent_vector.h>

#define U(x) _XPLATSTR(x)
#endif

namespace wcs {
    enum file_download_status {
        pretending = 0,
        proccessing = 1,
        finished = 2,
        failed = -1,
        info = 3,
        retry = 4,
        hashing = 5
    };

    enum sync_download_error {
        none = 0,
        unknown = -1,
        token_api_error = 2,
        hash_not_match = 5,
        calc_hash_fail = 6,
        url_api_error = 3,
        upload_part_error = 7,
        local_error = 4,
        file_exception = 8
    };

    struct SingleUrlTask {
        utility::size64_t fileSize;
        utility::size64_t processedSize;
        utility::string_t localPath;
        web::http::message_direction::direction direction;
        utility::string_t filename;
        utility::string_t remotePath;
        utility::string_t hash;
        int status;
        int error;
        int retryCount;
    };

    struct DownloadTask {
        tbb::concurrent_vector<SingleUrlTask *> task;
        utility::size64_t fileSize;
        utility::size64_t processedSize;
        utility::string_t localPath;
        utility::string_t localDirectory;
        web::http::message_direction::direction direction;
        utility::string_t filename;
        utility::string_t remotePath;
        int error;
        int fileCount;
        int type;
        int status;
        int progress;
    };
}


#endif //QINGZHENYUN_LITE_SINGLE_URL_DOWNLOAD_TASK_H
