//
// Created by zzzhr on 2018/11/7.
//

#ifndef QINGZHENYUN_LITE_DOWNLOAD_STATUS_H
#define QINGZHENYUN_LITE_DOWNLOAD_STATUS_H

#include <cpprest/details/basic_types.h>
#include <vector>
#include <memory>
namespace qingzhen::sync_task{
    enum error_reason {
        none = 0,
        io_error = 1,
        network_error = 2,
        mkfile_error = 3,
        upload_block_error = 4,
        upload_file_error = 5,
        hash_not_match = 6,
        api_error = 7,
        unknown_error = 9999,
        task_canceled = 1000
    };
    struct file_task_info {
    public:
        utility::size64_t file_size;
        utility::size64_t progress_size;
        bool cancelled;
        bool upload;
        bool success;
        utility::string_t local_path;
        utility::string_t remote_path;
        unsigned int progress;
        utility::string_t file_hash;
        error_reason error_reason;
        void set_progress(utility::size64_t progress_size){
            this->progress_size = progress_size;
            if(file_size > 0){
                this->progress = static_cast<unsigned int>(progress_size * 100 / file_size);
            }
        }
    };
    struct sync_task_info {
        utility::size64_t file_size;
        utility::size64_t progress_size;
        bool cancelled;
        bool upload;
        bool success;
        utility::string_t local_path;
        utility::string_t remote_path;
        unsigned int progress;
        error_reason error_reason;
        std::vector<std::shared_ptr<file_task_info>> task_detail = std::vector<std::shared_ptr<file_task_info>>();
    };
}

#endif //QINGZHENYUN_LITE_DOWNLOAD_STATUS_H
