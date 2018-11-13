//
// Created by zzzhr on 2018/10/31.
//

#ifndef QINGZHENYUN_LITE_API_OFFLINE_TASK_MODEL_H
#define QINGZHENYUN_LITE_API_OFFLINE_TASK_MODEL_H

#include <functional>
#include "../entity/response_entity.h"
#include "base/base_api_model.h"

namespace qingzhen::api {
	class api_offline_task_model : public base_api_model<api_offline_task_model> {
    public:
        pplx::task<response_entity> refresh_page(const pplx::cancellation_token_source &cancellation_token_source,
                                                 const int &page = -1,
                                                 const int &page_size = -1);
        web::json::array get_current_list() ;
        int get_current_page();
        int get_total_page();
        void
        update_current_location(const int &page,
                                const int &page_size, const int &total_page,
                                const web::json::array &list);
        bool on_response_entity_page_data_received(response_entity &entity);
        pplx::task<response_entity> start_task(const pplx::cancellation_token_source &cancellation_token_source,
                                               const utility::string_t &task_hash, const utility::string_t &save_path,
                                               const utility::string_t &copy_file);
        pplx::task<response_entity> parse_url(const pplx::cancellation_token_source &cancellation_token_source,const utility::string_t& url);
        pplx::task<response_entity> parse_torrent(const pplx::cancellation_token_source &cancellation_token_source,const utility::string_t& path);
    private:
        int current_page = 1;
        int current_page_size = 50;
        int total_page = 1;
        web::json::array current_list = web::json::value::array().as_array();
	};
}


#endif //QINGZHENYUN_LITE_API_OFFLINE_TASK_MODEL_H
