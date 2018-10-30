//
// Created by zzzhr on 2018/10/25.
//

#ifndef QINGZHENYUN_LITE_BASE_API_MODEL_H
#define QINGZHENYUN_LITE_BASE_API_MODEL_H

#include <pplx/pplxtasks.h>
#include "../../entity/response_entity.h"
#include <iostream>
/*
class facebook_client {
public:
	static facebook_client& instance(); // Singleton


private:
	facebook_client() :
		raw_client(L"https://graph.facebook.com/"),
		signed_in(false) {}


	bool signed_in;
	web::http::client::http_client raw_client;
};
*/

namespace qingzhen::api {

	

    class client_static {
    public:
        static web::http::client::http_client get_client() {
            static client_static c;
            return c.raw_client;
        }

    private:
        client_static(){
            this->config = web::http::client::http_client_config();
            this->config.set_timeout(std::chrono::seconds(30));
            this->raw_client = web::http::client::http_client(_XPLATSTR("https://www.6pan.cn"), this->config);
        }
		web::http::client::http_client_config config;
		web::http::client::http_client raw_client = web::http::client::http_client(_XPLATSTR("https://www.cctv.com"),config);
    };
    class base_api_model {
    public:
        pplx::task<response_entity> post_json(const utility::string_t& uri, const web::json::value & data, const pplx::cancellation_token_source &cancellation_token_source);
        void post_json(const utility::string_t& uri, const web::json::value & data,std::function<void(response_entity)> callback, const pplx::cancellation_token_source &cancellation_token_source);
        void then_json(pplx::task<response_entity> task, std::function<void(response_entity)> callback);
    private:
        // web::http::client::http_client raw_client;
    };

}

#endif //QINGZHENYUN_LITE_BASE_API_MODEL_H
