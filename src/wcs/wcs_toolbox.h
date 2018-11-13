//
// Created by zzzhr on 2018/11/7.
//

#ifndef QINGZHENYUN_LITE_WCS_TOOLBOX_H
#define QINGZHENYUN_LITE_WCS_TOOLBOX_H

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "../entity/file_task_info.hpp"

namespace qingzhen::wcs{
    class wcs_toolbox {
    public:
        static utility::size64_t read_buffer_from_stream(std::istream &input_stream, const std::streamsize &max_buffer_size, char* buffer);
        static std::pair<utility::string_t, utility::size64_t> hash_file_stream(std::istream &iss,pplx::cancellation_token token, const utility::size64_t &block_size, size_t &buffer_size);
        static pplx::task<std::pair<utility::string_t, utility::size64_t>> hash_file(const pplx::cancellation_token &cancellation_token, const utility::string_t &file_path,qingzhen::sync_task::file_task_info* file_task_info = nullptr ,utility::size64_t block_size = 1024 * 1024 * 4, size_t buffer_size = 1024 * 1024);
        static std::pair<utility::string_t, utility::size64_t> hash_file_sync(const pplx::cancellation_token &cancellation_token, const utility::string_t &file_path ,utility::size64_t block_size = 1024 * 1024 * 4, size_t buffer_size = 1024 * 1024);
        static utility::size64_t read_block_and_hash_from_stream(std::istream &input_stream, const utility::size64_t &block_size, size_t &buffer_size,unsigned char *temp_digest,char *buffer);
        //static utility::size64_t read_block_and_post_stream(std::istream &input_stream, const utility::size64_t &block_size, size_t &buffer_size,char *buffer);
        static bool post_simple_file(const pplx::cancellation_token &cancellation_token, qingzhen::sync_task::file_task_info &info, std::istream &input_stream, const utility::string_t & upload_token, const utility::string_t &upload_url);
        static web::http::client::http_client create_wcs_client(const utility::string_t &url);
        static web::http::http_request create_wcs_request(const web::http::method& mtd = web::http::methods::POST);
        static utility::string_t do_post_file(const pplx::cancellation_token &cancellation_token, qingzhen::sync_task::file_task_info& task_info, std::istream &input_stream, const utility::string_t & upload_token, const utility::string_t &upload_url);
        static std::vector<unsigned char> read_vector_from_stream(std::istream &iss, const size_t &max_buffer_size);
        static utility::string_t post_block(const pplx::cancellation_token &cancellation_token,qingzhen::sync_task::file_task_info& task_info, web::http::client::http_client &client, const utility::string_t &upload_token,
                                   const std::vector<unsigned char> &buffer, const long &block_index,const utility::size64_t &block_start_offset,
                                   const utility::string_t &batch);
        static utility::string_t make_file(const pplx::cancellation_token &cancellation_token, qingzhen::sync_task::file_task_info& task_info, web::http::client::http_client &client,
                                          const utility::string_t &upload_token,
                                          const utility::string_t &batch,
                                          const utility::string_t &blocks, const utility::size64_t &size);
    };
}



#endif //QINGZHENYUN_LITE_WCS_TOOLBOX_H
