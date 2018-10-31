//
// Created by zzzhr on 2018/10/29.
//

#ifndef QINGZHENYUN_LITE_API_REMOTE_FILE_MODEL_H
#define QINGZHENYUN_LITE_API_REMOTE_FILE_MODEL_H
#include <functional>
#include "../entity/response_entity.h"
#include "base/base_api_model.h"
namespace qingzhen::api {
    class api_remote_file_model  : public base_api_model<api_remote_file_model> {
    public:
        //static api_remote_file_model& instance();
        pplx::task<response_entity> refresh_path(const pplx::cancellation_token_source &cancellation_token_source,
                                                 const utility::string_t &path = _XPLATSTR(""), const int &page = -1,
                                                 const int &page_size = -1, const int &type = -1);
        pplx::task<response_entity> refresh_path_list_ex(const pplx::cancellation_token_source &cancellation_token_source,
                                                 const utility::string_t &path = _XPLATSTR(""), const int &start = -1,
                                                 const int &size = -1, const int &type = -1);
        pplx::task<response_entity> goto_path(const pplx::cancellation_token_source &cancellation_token_source,
                                                 const utility::string_t &path = _XPLATSTR(""), const int &page = -1,
                                                 const int &page_size = -1, const int &type = -1);
        pplx::task<response_entity> goto_uuid(const pplx::cancellation_token_source &cancellation_token_source,
                                              const utility::string_t &uuid = _XPLATSTR(""), const int &page = -1,
                                              const int &page_size = -1, const int &type = -1);

        // void set_path(const utility::string_t &path);

        void
        update_current_location(const utility::string_t &path, const utility::string_t &file_id, const int &page,
                                               const int &page_size, const int &total_page, const utility::string_t &parent,
                                               const web::json::array &list);
        bool on_response_entity_received(response_entity & entity);
        web::json::array get_current_list() ;
        int get_current_page();
        int get_total_page();
        utility::string_t get_current_path();
        utility::string_t get_parent();
        pplx::task<response_entity> create_new_directory(const pplx::cancellation_token_source &cancellation_token_source,const utility::string_t & directory_name, const utility::string_t & parent_uuid = U(""));
    private:
        utility::string_t current_path = _XPLATSTR("/");
        utility::string_t current_file_id = _XPLATSTR("");
        int current_page = 1;
        int current_page_size = 40;
        int total_page = 1;
        utility::string_t current_parent = _XPLATSTR("");
        web::json::array current_list = web::json::value::array().as_array();
        int current_order = -1;
    };
}


#endif //QINGZHENYUN_LITE_API_REMOTE_FILE_MODEL_H
