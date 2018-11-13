//
// Created by zzzhr on 2018/11/8.
//

#include "api_file_store_model.h"
#include "../wcs/wcs_toolbox.h"
#include "../common/common_fs.h"

pplx::task<response_entity> qingzhen::api::api_file_store_model::get_token_or_file_info(
        const pplx::cancellation_token_source &cancellation_token_source, const utility::string_t &file_hash,
        const utility::string_t &remote_path) {
    web::json::value request;
    request[_XPLATSTR("hash")] = web::json::value::string(file_hash);
    request[_XPLATSTR("path")] = web::json::value::string(remote_path);
    return this->post_json(_XPLATSTR("/v1/store/token"),request, cancellation_token_source);
}

pplx::task<response_entity> qingzhen::api::api_file_store_model::get_token_or_file_info(
        const pplx::cancellation_token_source &cancellation_token_source, const utility::string_t &file_hash,
        const utility::string_t &remote_path_dir, const utility::string_t &filename) {
    web::json::value request;
    request[_XPLATSTR("hash")] = web::json::value::string(file_hash);
    request[_XPLATSTR("path")] = web::json::value::string(remote_path_dir);
    if(!filename.empty()){
        request[_XPLATSTR("name")] = web::json::value::string(filename);
        request[_XPLATSTR("originalFilename")] = web::json::value::string(filename);

    }
    return this->post_json(_XPLATSTR("/v1/store/token"),request, cancellation_token_source);
}

pplx::task<qingzhen::sync_task::file_task_info>
qingzhen::api::api_file_store_model::post_simple_file(const pplx::cancellation_token_source &cancellation_token_source,
                                                      const utility::string_t &file_path,
                                                      const utility::string_t &remote_path) {
    auto token = cancellation_token_source.get_token();
    auto task =  pplx::create_task([token,file_path,remote_path,this]() {
        qingzhen::sync_task::file_task_info result = qingzhen::sync_task::file_task_info();
        auto hash_result = qingzhen::wcs::wcs_toolbox::hash_file_sync(token,file_path);
        if(token.is_canceled()){
            result.success = false;
            result.error_reason = qingzhen::sync_task::error_reason::task_canceled;
            return result;
        }
        auto file_hash = hash_result.first;
        if(file_hash.empty()){
            result.success = false;
            result.error_reason = qingzhen::sync_task::error_reason::io_error;
            return result;
        }

        result.file_size = hash_result.second;
        result.file_hash = file_hash;

        // Get Token
        utility::string_t upload_token = utility::string_t();
        utility::string_t upload_url = utility::string_t();
        try {
            auto data = get_token_or_file_info(token,file_hash,remote_path).get();
            if(token.is_canceled()){
                result.success = false;
                result.error_reason = qingzhen::sync_task::error_reason::task_canceled;
                return result;
            }

            if(!data.success){
                result.success = false;
                result.error_reason = qingzhen::sync_task::error_reason::network_error;
                return result;
            }
            if(data.result.has_field(_XPLATSTR("storeId"))){
                result.success = true;
                result.file_hash = data.result.at(_XPLATSTR("storeId")).as_string();
                if(data.result.has_field(_XPLATSTR("path"))) {
                    result.remote_path = data.result.at(_XPLATSTR("path")).as_string();
                }
                return result;
            }else{
                if(!data.result.has_field(_XPLATSTR("token"))){
                    result.success = false;
                    result.error_reason = qingzhen::sync_task::error_reason::api_error;
                    return result;
                }else{
                    upload_token = data.result.at(_XPLATSTR("token")).as_string();
                }

                if(!data.result.has_field(_XPLATSTR("uploadUrl"))){
                    result.success = false;
                    result.error_reason = qingzhen::sync_task::error_reason::api_error;
                    return result;
                }else{
                    upload_url = data.result.at(_XPLATSTR("uploadUrl")).as_string();
                }
            }

        }catch (std::exception &e){
            if(token.is_canceled()){
                result.success = false;
                result.error_reason = qingzhen::sync_task::error_reason::task_canceled;
                return result;
            }
            result.success = false;
            result.error_reason = qingzhen::sync_task::error_reason::unknown_error;
            return result;
        }

        if(upload_url.empty() || upload_token.empty()){
            result.success = false;
            result.error_reason = qingzhen::sync_task::error_reason::task_canceled;
            return result;
        }

        std::filebuf in;
        if (!in.open(file_path, std::ios::in | std::ios::binary)) {
            std::cout << "fail to open file" << std::endl;
            result.success = false;
            result.error_reason = qingzhen::sync_task::error_reason::io_error;
            return result;
        }

        /*
        try {
            auto path = common_fs::path(file_path);
            auto file_size = common_fs::file_size(path);
            result.file_size = file_size;
        }catch (std::exception &x){
            std::cout << "Get file size error" << std::endl;
        }
         */


        std::istream iss(&in);

        //result.success = qingzhen::wcs::wcs_toolbox::post_simple_file(token,result,)

        //auto read_size = buffer_size;
        //auto b_size = block_size;
        //auto result = hash_file_stream(iss, token, b_size, read_size);

        // do try catch, prevent I386_EXC
        auto success = qingzhen::wcs::wcs_toolbox::post_simple_file(token,result,iss,upload_token,upload_url);
        // and ensure close the file
        //
        if(!success){
            result.success = false;
            //result.error_reason = qingzhen::sync_task::error_reason::task_canceled;
            //return result;
            if(result.error_reason == qingzhen::sync_task::error_reason::none){
                result.error_reason = qingzhen::sync_task::error_reason::unknown_error;
            }
        }else{
            result.success = true;
        }
        in.close();
        return result;
    },token);
    return task;
}

pplx::task<response_entity>
qingzhen::api::api_file_store_model::get_token_or_file_info(const pplx::cancellation_token &cancellation_token,
                                                            const utility::string_t &file_hash,
                                                            const utility::string_t &remote_path_dir,
                                                            const utility::string_t &filename) {
    web::json::value request;
    request[_XPLATSTR("hash")] = web::json::value::string(file_hash);
    request[_XPLATSTR("path")] = web::json::value::string(remote_path_dir);
    if(!filename.empty()){
        request[_XPLATSTR("name")] = web::json::value::string(filename);
        request[_XPLATSTR("originalFilename")] = web::json::value::string(filename);

    }
    return this->post_json(_XPLATSTR("/v1/store/token"),request, cancellation_token);
}