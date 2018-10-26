//
// Created by zzzhr on 2018/10/25.
//

#ifndef QINGZHENYUN_LITE_BASE_API_MODEL_H
#define QINGZHENYUN_LITE_BASE_API_MODEL_H

#include <pplx/pplxtasks.h>
#include "../../entity/response_entity.h"

namespace qingzhen::api {
    class client_static {
    public:
        static web::http::client::http_client get_client() {
            static client_static c;
            return c.raw_client;
        }
    private:
        web::http::client::http_client raw_client = web::http::client::http_client(_XPLATSTR("https://api.6pan.cn"));
    };
    class base_api_model {
    public:
        pplx::task<response_entity> post_json(const utility::string_t& uri, const web::json::value & data);
        void post_json(const utility::string_t& uri, const web::json::value & data,std::function<void(response_entity)> callback);
        void then_json(pplx::task<response_entity> task, std::function<void(response_entity)> callback);
    private:
        // web::http::client::http_client raw_client;
    };

}

#endif //QINGZHENYUN_LITE_BASE_API_MODEL_H
