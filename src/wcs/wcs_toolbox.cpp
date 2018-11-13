//
// Created by zzzhr on 2018/11/7.
//

#include "wcs_toolbox.h"
#include <openssl/sha.h>
#include <thread>
#include "random"
#include "../api_model/api_user_model.h"

using namespace qingzhen::wcs;
utility::size64_t qingzhen::wcs::wcs_toolbox::read_buffer_from_stream(std::istream &input_stream, const std::streamsize &max_buffer_size,
                                                                      char *buffer) {
    input_stream.read(buffer, max_buffer_size);
    auto count = input_stream.gcount();
    return static_cast<utility::size64_t>(count);
}

/*
utility::size64_t
wcs_toolbox::read_block_and_post_stream(std::istream &input_stream, const utility::size64_t &block_size,
                                        size_t &buffer_size, char *buffer) {
    utility::size64_t block_read = 0;
    while (block_read < block_size) {
        auto buffer_read_size = read_buffer_from_stream(input_stream, buffer_size,buffer);
        if (buffer_read_size <= 0) {
            //block read finished
            break;
            // Hash
        }
        block_read += buffer_read_size;
    }
    return block_read;
}
 */


utility::size64_t qingzhen::wcs::wcs_toolbox::read_block_and_hash_from_stream(std::istream &input_stream,
                                                                              const utility::size64_t &block_size,
                                                                              size_t &buffer_size,
                                                                              unsigned char *temp_digest, char *buffer) {

    SHA_CTX shaCtx;
    SHA1_Init(&shaCtx);
    utility::size64_t block_read = 0;
    while (block_read < block_size) {
        auto buffer_read_size = read_buffer_from_stream(input_stream, buffer_size,buffer);
        if (buffer_read_size <= 0) {
            //block read finished
            break;
            // Hash
        }
        SHA1_Update(&shaCtx, buffer, static_cast<size_t>(buffer_read_size));
        block_read += buffer_read_size;
    }

    SHA1_Final(temp_digest, &shaCtx);
    return block_read;
}

std::pair<utility::string_t, utility::size64_t> wcs_toolbox::hash_file_stream(std::istream &iss, pplx::cancellation_token token, const utility::size64_t &block_size, size_t &buffer_size) {
    utility::size64_t file_read = 0;
    std::vector<unsigned char> rec = std::vector<unsigned char>();
    unsigned char temp_digest[SHA_DIGEST_LENGTH];
    char* buffer = new char[buffer_size];
    while (true){
        utility::size64_t currentRead = read_block_and_hash_from_stream(iss, block_size, buffer_size,temp_digest, buffer);
        if(currentRead <= 0 || token.is_canceled()){
            break;
        }
        for(auto &c : temp_digest){
            rec.push_back(c);
        }
        file_read += currentRead;
    }
    delete[] buffer;
    if(token.is_canceled()){
        return std::pair<utility::string_t, utility::size64_t>(utility::string_t(), file_read);
    }
    const unsigned char BYTE_LOW_4 = 0x16;
    const unsigned char BYTE_OVER_4 = 0x96;
    size_t digestSize = rec.size();
    unsigned char final_digest[SHA_DIGEST_LENGTH + 1];
    if(digestSize == SHA_DIGEST_LENGTH){
        final_digest[0] = BYTE_LOW_4;
        for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {//SHA1 20
            final_digest[i + 1] = rec[i];
        }
        //Single file
    }else{
        //final_digest[0] = BYTE_OVER_4;
        //unsigned char temp_digest[SHA_DIGEST_LENGTH];

        SHA_CTX sha_ctx;
        SHA1_Init(&sha_ctx);
        SHA1_Update(&sha_ctx, rec.data(), digestSize);
        SHA1_Final(temp_digest, &sha_ctx);
        final_digest[0] = BYTE_OVER_4;
        for (auto i = 0; i < SHA_DIGEST_LENGTH; ++i) {//0x96
            final_digest[i + 1] = temp_digest[i];
        }
    }

    std::vector<unsigned char> v(std::begin(final_digest), std::end(final_digest));
    auto base64 = utility::conversions::to_base64(v);
    //char * ch = base64.data();

    for (auto &i : base64) {
        if (i == _XPLATSTR('+')) {
            i = _XPLATSTR('-');
        }

        if (i == _XPLATSTR('/')) {
            i = _XPLATSTR('_');
        }
    }
    if(token.is_canceled()){
        return std::pair<utility::string_t, utility::size64_t>(utility::string_t(), 0);
    }
    //return
    return std::pair<utility::string_t, utility::size64_t>(base64, file_read);
}

pplx::task<std::pair<utility::string_t, utility::size64_t>> wcs_toolbox::hash_file(const pplx::cancellation_token &cancellation_token,
                                                     const utility::string_t &file_path,
                                                     qingzhen::sync_task::file_task_info *file_task_info,
                                                     utility::size64_t block_size, size_t buffer_size) {
    return pplx::create_task([cancellation_token,file_path,block_size, buffer_size,file_task_info]() {
        std::filebuf in;
        if (!in.open(file_path, std::ios::in | std::ios::binary)) {
            std::cout << "fail to open file" << std::endl;

            return std::pair<utility::string_t, utility::size64_t>(utility::string_t(), 0);
        }
        std::istream iss(&in);
        auto read_size = buffer_size;
        auto b_size = block_size;
        auto result = hash_file_stream(iss, cancellation_token, b_size, read_size);
        in.close();
        return result;
        },cancellation_token);
}

bool
wcs_toolbox::post_simple_file(const pplx::cancellation_token &cancellation_token,qingzhen::sync_task::file_task_info &info, std::istream &input_stream,
                              const utility::string_t & upload_token, const utility::string_t &upload_url) {

    size_t BLOCK_SIZE = 1024 * 1024 * 4; //MUST BE 4MB

    utility::string_t file_hash;
    try {
        file_hash = do_post_file(cancellation_token,info ,input_stream,upload_token,upload_url);

    }catch (std::exception &ex){
        std::cout << "Post single " << ex.what() << std::endl;
        if(cancellation_token.is_canceled()){
            info.error_reason = qingzhen::sync_task::error_reason::task_canceled;
            return false;
        }
        else if(info.error_reason == qingzhen::sync_task::error_reason::none){
            info.error_reason = qingzhen::sync_task::error_reason::upload_file_error;
        }
        return false;
    }
    if(file_hash.empty()){
        if(cancellation_token.is_canceled()){
            info.error_reason = qingzhen::sync_task::error_reason::task_canceled;
            return false;
        }
        else if(info.error_reason == qingzhen::sync_task::error_reason::none){
            info.error_reason = qingzhen::sync_task::error_reason::upload_file_error;
        }
        return false;
    }
    if(file_hash != info.file_hash){
        if(info.file_hash.empty()){
            info.file_hash = file_hash;
        } else {
            //if()
            if(info.error_reason == qingzhen::sync_task::error_reason::none){
                info.error_reason = qingzhen::sync_task::error_reason::hash_not_match;
            }
            //std::cout << "HASH_NOT_MATCH!!!!" << file_hash << ": :" << info.file_hash << std::endl;
            return false;
        }
    }

    //std::generate_n()
    return true;
}

web::http::client::http_client wcs_toolbox::create_wcs_client(const utility::string_t &url) {
    web::http::client::http_client_config config;
    config.set_timeout(std::chrono::seconds(30));
    config.set_chunksize(1024 * 4);
    web::http::client::http_client client(url, config);
    return client;
}

web::http::http_request wcs_toolbox::create_wcs_request(const web::http::method &mtd) {
    web::http::http_request request(mtd);
    auto & headers = request.headers();
    headers.add(web::http::header_names::accept, _XPLATSTR("application/json"));
    return request;
}

utility::string_t wcs_toolbox::do_post_file(const pplx::cancellation_token &cancellation_token,
                               qingzhen::sync_task::file_task_info &task_info, std::istream &input_stream,
                               const utility::string_t &upload_token, const utility::string_t &upload_url) {
    const size_t BLOCK_SIZE = 1024 * 1024 * 4;
    utility::size64_t read_bytes = 0;
    auto client = create_wcs_client(upload_url);
    auto batch = qingzhen::api::api_user_model::instance().user_random_string();
    long index = 0;
    utility::string_t blocks;
    while (!cancellation_token.is_canceled()) {
        std::vector<unsigned char> buffer = read_vector_from_stream(input_stream,BLOCK_SIZE);
        auto bufferReadSize = buffer.size();
        if(bufferReadSize <= 0){
            break;
        }
        utility::string_t blockCtx = post_block(cancellation_token,task_info,client,upload_token, buffer, index,read_bytes ,batch);
        if(blockCtx.empty()){
            //throw std::exception();
            // NEED TER,
            return utility::string_t();
        }
        read_bytes += bufferReadSize;
        if(index > 0){
            blocks += (_XPLATSTR(",") + blockCtx);
        }else{
            blocks += blockCtx;
        }
        index++;
    }

    if(cancellation_token.is_canceled()){
        // TERI
        return utility::string_t();
    }
    //Do MKFILE
    if(blocks.empty()){
        blocks = post_block(cancellation_token, task_info, client,upload_token, std::vector<unsigned char>(0), index,read_bytes, batch);
    }
    if(read_bytes != task_info.file_size){
        task_info.file_size = read_bytes;
        std::cout << "- FILE SIZE NOT MATCH" << std::endl;
    }
    return make_file(cancellation_token,task_info,client,upload_token,batch,blocks,read_bytes);
    //


}

std::vector<unsigned char> wcs_toolbox::read_vector_from_stream(std::istream &iss, const size_t &max_buffer_size) {
    std::vector<unsigned char> buffer = std::vector<unsigned char>(max_buffer_size);
    iss.read((char*)buffer.data(), max_buffer_size);
    auto rs = static_cast<size_t>(iss.gcount());
    if (rs != max_buffer_size) {
        buffer.resize(rs);
    }
    return buffer;
}

utility::string_t
wcs_toolbox::post_block(const pplx::cancellation_token &cancellation_token, qingzhen::sync_task::file_task_info& task_info, web::http::client::http_client &client,
                        const utility::string_t &upload_token, const std::vector<unsigned char> &buffer,
                        const long &block_index, const utility::size64_t &block_start_offset, const utility::string_t &batch) {
    //return utility::string_t();
    auto read_size = buffer.size();
    auto post_url = utility::conversions::to_string_t("/mkblk/" + std::to_string(read_size) + '/' + std::to_string(block_index));
    int try_times = 10 * 3;
    while ( try_times > 0 && !cancellation_token.is_canceled()){
        try {
            auto request = create_wcs_request();
            web::uri_builder post_uri(post_url);
            request.set_request_uri(post_uri.to_string());
            request.headers().add(web::http::header_names::content_type, _XPLATSTR("application/octet-stream"));
            //UploadBatch
            request.headers().add(_XPLATSTR("UploadBatch"), batch);
            request.headers().add(_XPLATSTR("Authorization"), upload_token);
            request.set_body(buffer);
            request.set_progress_handler(
                    [&](web::http::message_direction::direction direction, utility::size64_t so_far)
                    {
                        if (direction == web::http::message_direction::upload && !cancellation_token.is_canceled()){
                            task_info.set_progress(so_far + block_start_offset);
                        }
                    });
            web::json::value create_blk_result = client.request(request,cancellation_token).get().extract_json(true).get();
            if (create_blk_result.has_field(_XPLATSTR("ctx"))) {
                return create_blk_result.at(_XPLATSTR("ctx")).as_string();
            }else{
                std::cout << create_blk_result.serialize().c_str() << std::endl;
            }
        }catch (std::exception &e){
            std::cout << "Make block fail: " << e.what() << std::endl;
            if(cancellation_token.is_canceled()){
                return utility::string_t();
            }
        }
        try_times -= 1;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    task_info.error_reason = qingzhen::sync_task::error_reason::upload_block_error;
    return utility::string_t();
}

utility::string_t wcs_toolbox::make_file(const pplx::cancellation_token &cancellation_token,
                                         qingzhen::sync_task::file_task_info &task_info,
                                         web::http::client::http_client &client, const utility::string_t &upload_token,
                                         const utility::string_t &batch, const utility::string_t &blocks,
                                         const utility::size64_t &size) {
    //return utility::string_t();
    auto post_url = utility::conversions::to_string_t("/mkfile/" + std::to_string(size));
    int try_times = 10 * 2;
    while ( try_times > 0 && !cancellation_token.is_canceled()){
        try {
            auto request = create_wcs_request();
            web::uri_builder post_uri(post_url);
            request.set_request_uri(post_uri.to_string());
            request.headers().add(web::http::header_names::content_type, _XPLATSTR("text/plain"));
            request.headers().add(_XPLATSTR("UploadBatch"), batch);
            request.headers().add(_XPLATSTR("Authorization"), upload_token);
            request.set_body(blocks);
            web::json::value create_file_result = client.request(request).get().extract_json(true).get();
            if (create_file_result.has_field(_XPLATSTR("hash"))) {
                if(create_file_result.has_field(_XPLATSTR("response"))){
                    auto res = create_file_result.at(_XPLATSTR("response")).as_string();
                    try {
                        auto r = web::json::value::parse(res);
                        if(r.has_field(_XPLATSTR("success"))){
                            if(r.at(_XPLATSTR("success")).as_bool()){
                                task_info.remote_path = r.at(_XPLATSTR("result")).at(_XPLATSTR("path")).as_string();
                            }
                        }
                    }
                    catch (std::exception &e){
                        std ::cout << "P json:" << e.what() << std::endl;
                    }
                }
                return create_file_result.at(_XPLATSTR("hash")).as_string();
            }else{
                std::cout << "Post failed" << create_file_result.serialize().c_str() << std::endl;
                //return utility::string_t();
            }
        }catch (std::exception &e){
            std::cout << e.what() << std::endl;
            if(cancellation_token.is_canceled()){
                return utility::string_t();
            }
        }
        try_times--;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    task_info.error_reason = qingzhen::sync_task::error_reason::mkfile_error;
    return utility::string_t();
}

std::pair<utility::string_t, utility::size64_t>
wcs_toolbox::hash_file_sync(const pplx::cancellation_token &cancellation_token, const utility::string_t &file_path,
                            utility::size64_t block_size,
                            size_t buffer_size) {
    std::filebuf in;
    if (!in.open(file_path, std::ios::in | std::ios::binary)) {
        std::cout << "fail to open file" << std::endl;

        return std::pair<utility::string_t, utility::size64_t>(utility::string_t(), 0);
    }
    std::istream iss(&in);
    auto read_size = buffer_size;
    auto b_size = block_size;
    auto result = hash_file_stream(iss, cancellation_token, b_size, read_size);
    in.close();
    return result;
}






/*

utility::string_t wcs_toolbox::hash_file(const pplx::cancellation_token_source& cancellation_token_source,const utility::string_t &file_path, utility::size64_t block_size,
                                         size_t buffer_size) {

}
 */

