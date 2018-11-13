//
// Created by zzzhr on 2018/11/8.
//

#ifndef QINGZHENYUN_LITE_API_FILE_STORE_MODEL_H
#define QINGZHENYUN_LITE_API_FILE_STORE_MODEL_H


#include <functional>
#include "../entity/response_entity.h"
#include "base/base_api_model.h"
#include "../entity/file_task_info.hpp"
#include "../common/common_fs.h"
#include <mutex>
#include <vector>
#include <memory>


namespace qingzhen::api{
    class api_file_store_model : public base_api_model<api_file_store_model> {
    public:
        pplx::task<response_entity> get_token_or_file_info(const pplx::cancellation_token_source &cancellation_token_source,
                                               const utility::string_t &file_hash,
                                               const utility::string_t &remote_path);
        pplx::task<response_entity> get_token_or_file_info(const pplx::cancellation_token_source &cancellation_token_source,
                                                           const utility::string_t &file_hash,
                                                           const utility::string_t &remote_path_dir, const utility::string_t &filename);
        pplx::task<response_entity> get_token_or_file_info(const pplx::cancellation_token &cancellation_token,
                                                           const utility::string_t &file_hash,
                                                           const utility::string_t &remote_path_dir, const utility::string_t &filename = utility::string_t());
        pplx::task<qingzhen::sync_task::file_task_info> post_simple_file(const pplx::cancellation_token_source &cancellation_token_source,
                                                                        const utility::string_t &file_path,
                                                                        const utility::string_t &remote_path);
        void add_upload_task(const std::vector<utility::string_t> & path,const utility::string_t &remote_directory);
    private:
        std::mutex task_mutex;
        void do_add_upload_task(const std::vector<utility::string_t> & path,const utility::string_t &remote_directory);
        void do_add_directory(const common_fs::path & path,const common_fs::path &base_path, const utility::string_t &remote_directory, std::shared_ptr<qingzhen::sync_task::sync_task_info> & info);
        std::vector<std::shared_ptr<qingzhen::sync_task::sync_task_info>> tasks /*GUARDED_BY(task_mutex)*/ = std::vector<std::shared_ptr<qingzhen::sync_task::sync_task_info>>();
    };
}



#endif //QINGZHENYUN_LITE_API_FILE_STORE_MODEL_H
