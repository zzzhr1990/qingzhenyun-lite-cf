//
// Created by zzzhr on 2018/10/31.
//

#include "api_offline_task_model.h"

web::json::array qingzhen::api::api_offline_task_model::get_current_list() {
    return this->current_list;
}

int qingzhen::api::api_offline_task_model::get_current_page() {
    return this->current_page;
}

int qingzhen::api::api_offline_task_model::get_total_page() {
    return this->total_page;
}

void qingzhen::api::api_offline_task_model::update_current_location(const int &page, const int &page_size,
                                                                    const int &total_page,
                                                                    const web::json::array &list) {
    this->current_page = page;
    this->current_page_size = page_size;
    this->total_page = total_page;
    this->current_list = list;
}

pplx::task<response_entity>
qingzhen::api::api_offline_task_model::refresh_page(const pplx::cancellation_token_source &cancellation_token_source,
                                                    const int &page, const int &page_size) {
    web::json::value request;
    request[_XPLATSTR("page")] = web::json::value::number(page > 0 ? page : current_page);
    request[_XPLATSTR("pageSize")] = web::json::value::number(page_size > 0 ? page_size : current_page_size);
    return this->post_json(_XPLATSTR("/v1/offline/page"),request, cancellation_token_source);
}

bool qingzhen::api::api_offline_task_model::on_response_entity_page_data_received(response_entity &entity) {
    if(!entity.success){
        return false;
    }


    if(entity.result.is_null()){
        return false;
    }
    auto &result = entity.result;

    //calc current list

    if(!result.has_field(_XPLATSTR("page"))){
        return false;
    }
    auto current_page = result.at(_XPLATSTR("page")).as_integer();
    auto current_page_size = result.at(_XPLATSTR("pageSize")).as_integer();
    auto total_page = result.at(_XPLATSTR("totalPage")).as_integer();
    if(!result.has_field(_XPLATSTR("list"))){
        return false;
    }
    auto list = result.at(_XPLATSTR("list")).as_array();
    this->update_current_location( current_page, current_page_size, total_page, list);
    return true;

}

pplx::task<response_entity>
qingzhen::api::api_offline_task_model::parse_url(const pplx::cancellation_token_source &cancellation_token_source,
                                                 const utility::string_t &url) {
    web::json::value request;
    request[_XPLATSTR("url")] = web::json::value::string(url);
    return this->post_json(_XPLATSTR("/v1/offline/parseUrl"),request, cancellation_token_source);
}

pplx::task<response_entity>
qingzhen::api::api_offline_task_model::parse_torrent(const pplx::cancellation_token_source &cancellation_token_source,
                                                 const utility::string_t &path) {
    web::json::value request;
    request[_XPLATSTR("path")] = web::json::value::string(path);
    return this->post_json(_XPLATSTR("/v1/offline/parseTorrent"),request, cancellation_token_source);
}

pplx::task<response_entity>
qingzhen::api::api_offline_task_model::start_task(const pplx::cancellation_token_source &cancellation_token_source,
                                                  const utility::string_t &task_hash,
                                                  const utility::string_t &save_path,
                                                  const utility::string_t &copy_file) {
    web::json::value request;
    request[_XPLATSTR("taskHash")] = web::json::value::string(task_hash);
    request[_XPLATSTR("savePath")] = web::json::value::string(save_path);
    request[_XPLATSTR("copyFile")] = web::json::value::string(copy_file);
    return this->post_json(_XPLATSTR("/v1/offline/start"),request, cancellation_token_source);
}
