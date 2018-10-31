//
// Created by zzzhr on 2018/10/29.
//

#include "api_remote_file_model.h"
using namespace qingzhen::api;
/*
api_remote_file_model &api_remote_file_model::instance() {
    static api_remote_file_model c;
    return c;
}
 */

pplx::task<response_entity>
api_remote_file_model::refresh_path(const pplx::cancellation_token_source &cancellation_token_source,
                                    const utility::string_t &path, const int &page, const int &page_size,
                                    const int &type) {
    web::json::value request;
    request[_XPLATSTR("path")] = web::json::value::string(path.empty() ? current_path : path);
    request[_XPLATSTR("page")] = web::json::value::number(page > 0 ? page : current_page);
    request[_XPLATSTR("pageSize")] = web::json::value::number(page_size > 0 ? page_size : current_page_size);
    request[_XPLATSTR("order")] = web::json::value::number(current_order);
    if (type > -1) {
        request[_XPLATSTR("type")] = web::json::value::number(type);
    }
    return this->post_json(_XPLATSTR("/v1/files/page"),request, cancellation_token_source);
}

pplx::task<response_entity>
api_remote_file_model::refresh_path_list_ex(const pplx::cancellation_token_source &cancellation_token_source,
                                    const utility::string_t &path, const int &start, const int &size,
                                    const int &type) {
    web::json::value request;
    request[_XPLATSTR("path")] = web::json::value::string(path.empty() ? current_path : path);
    request[_XPLATSTR("start")] = web::json::value::number(start > -1 ? start : -1);
    request[_XPLATSTR("size")] = web::json::value::number(size > 0 ? size : current_page_size);
    request[_XPLATSTR("order")] = web::json::value::number(current_order);
    if (type > -1) {
        request[_XPLATSTR("type")] = web::json::value::number(type);
    }
    return this->post_json(_XPLATSTR("/v1/files/list2"),request, cancellation_token_source);
}

/*
void api_remote_file_model::set_path(const utility::string_t &path) {
    this->current_path = path;
}
 */

void api_remote_file_model::update_current_location(const utility::string_t &path, const utility::string_t &file_id,
                                                    const int &page, const int &page_size, const int &total_page,
                                                    const utility::string_t &parent, const web::json::array &list) {
    this->current_path = path;
    this->current_file_id = file_id;
    this->current_page = page;
    this->current_page_size = page_size;
    this->total_page = total_page;
    this->current_parent = parent;
    this->current_list = list;
}

bool api_remote_file_model::on_response_entity_received(response_entity &entity) {
    if(!entity.success){
        return false;
    }


    if(entity.result.is_null()){
        return false;
    }
    auto &result = entity.result;
    if(!result.has_field(_XPLATSTR("info"))){
        return false;
    }
    //calc current list

    auto dir_info = result.at(_XPLATSTR("info"));
    auto current_path = dir_info.at(_XPLATSTR("path")).as_string();
    auto current_id = dir_info.at(_XPLATSTR("uuid")).as_string();
    auto parent = dir_info.at(_XPLATSTR("parent")).as_string();
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
    // we create list
    web::json::array array = web::json::value::array().as_array();
    if(current_path.empty() || current_path == _XPLATSTR("/")){
        array = list;
    } else {
        auto path_idx = current_path.find_last_of(_XPLATSTR('/'));
        auto parent_path = path_idx > 0 ? current_path.substr(0,path_idx) : _XPLATSTR("/");
        // create root file
        web::json::value root = web::json::value();
        root[_XPLATSTR("uuid")] = web::json::value::string(parent);
        root[_XPLATSTR("storeId")] = web::json::value::string(_XPLATSTR(""));
        root[_XPLATSTR("userId")] = web::json::value::number(-1);
        root[_XPLATSTR("path")] = web::json::value::string(parent_path);
        root[_XPLATSTR("name")] = web::json::value::string(_XPLATSTR(".."));
        root[_XPLATSTR("ext")] = web::json::value::string(_XPLATSTR(""));
        root[_XPLATSTR("size")] = web::json::value::number(0);
        root[_XPLATSTR("parent")] = web::json::value::string(_XPLATSTR(""));
        root[_XPLATSTR("type")] = web::json::value::number(1);
        root[_XPLATSTR("atime")] = web::json::value::number(1);
        root[_XPLATSTR("ctime")] = web::json::value::number(1);
        root[_XPLATSTR("mtime")] = web::json::value::number(1);
        root[_XPLATSTR("version")] = web::json::value::number(0);
        root[_XPLATSTR("locking")] = web::json::value::boolean(false);
        root[_XPLATSTR("opt")] = web::json::value::number(0);
        root[_XPLATSTR("mime")] = web::json::value::string(_XPLATSTR("application/x-directory"));
        root[_XPLATSTR("preview")] = web::json::value::number(-1);
        root[_XPLATSTR("flag")] = web::json::value::number(0);
        root[_XPLATSTR("hasPreview")] = web::json::value::boolean(false);
        array[0] = root;
        web::json::array::size_type idx = 1;
        for(auto &obj : list){
            array[idx] = obj;
            idx++;
        }
    }
    this->update_current_location(current_path, current_id, current_page, current_page_size, total_page, parent, array);
    return true;
}

web::json::array api_remote_file_model::get_current_list() {
    return this->current_list;
}

int api_remote_file_model::get_current_page() {
    return current_page;
}

int api_remote_file_model::get_total_page() {
    return total_page;
}

utility::string_t api_remote_file_model::get_current_path() {
    return this->current_path;
}

utility::string_t api_remote_file_model::get_parent() {
    return this->current_parent;
}

pplx::task<response_entity>
api_remote_file_model::goto_uuid(const pplx::cancellation_token_source &cancellation_token_source,
                                 const utility::string_t &uuid, const int &page, const int &page_size,
                                 const int &type) {
    web::json::value request;
    request[_XPLATSTR("uuid")] = web::json::value::string(uuid.empty() ? current_path : _XPLATSTR(""));
    request[_XPLATSTR("page")] = web::json::value::number(page > 0 ? page : current_page);
    request[_XPLATSTR("pageSize")] = web::json::value::number(page_size > 0 ? page_size : current_page_size);
    request[_XPLATSTR("order")] = web::json::value::number(current_order);
    if (type > -1) {
        request[_XPLATSTR("type")] = web::json::value::number(type);
    }
    return this->post_json(_XPLATSTR("/v1/files/page"),request, cancellation_token_source);
}

pplx::task<response_entity>
api_remote_file_model::goto_path(const pplx::cancellation_token_source &cancellation_token_source,
                                 const utility::string_t &path, const int &page, const int &page_size,
                                 const int &type) {
    return this->refresh_path(cancellation_token_source,path,page,page_size,type);
}

pplx::task<response_entity>
api_remote_file_model::create_new_directory(const pplx::cancellation_token_source &cancellation_token_source,
                                               const utility::string_t &directory_name,
                                               const utility::string_t &parent_uuid) {
    web::json::value request;
    request[_XPLATSTR("parent")] = web::json::value::string(parent_uuid.empty() ? this->current_file_id : parent_uuid);
    request[_XPLATSTR("name")] = web::json::value::string(directory_name);

    return this->post_json(_XPLATSTR("/v1/files/createDirectory"),request, cancellation_token_source);

}

