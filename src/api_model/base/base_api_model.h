//
// Created by zzzhr on 2018/10/25.
//

#ifndef QINGZHENYUN_LITE_BASE_API_MODEL_H
#define QINGZHENYUN_LITE_BASE_API_MODEL_H

#include <pplx/pplxtasks.h>
#include "../../entity/response_entity.h"
#include <iostream>
#include "./token_store.h"

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
            this->raw_client = web::http::client::http_client(_XPLATSTR("https://api.6pan.cn"), this->config);
        }
		web::http::client::http_client_config config;
		web::http::client::http_client raw_client = web::http::client::http_client(_XPLATSTR("https://www.cctv.com"),config);
    };



    template<class T>  class base_api_model {
    public:
        static T &instance();
        pplx::task<response_entity> post_json(const utility::string_t& uri, const web::json::value & data, const pplx::cancellation_token_source &cancellation_token_source);
        pplx::task<response_entity> post_json(const utility::string_t& uri, const web::json::value & data, const pplx::cancellation_token &cancellation_token);
        void then_json(pplx::task<response_entity> task, std::function<void(response_entity)> callback);
    private:
        // web::http::client::http_client raw_client;
    };

    template<class T>
    T &base_api_model<T>::instance() {
        static T c;
        return c;
    }



    template<class T>
    void base_api_model<T>::then_json(pplx::task<response_entity> task, std::function<void(response_entity)> callback) {
        task.then([callback](response_entity entity) -> void {
            callback(entity);
        });
    }

    template<class T>
    pplx::task<response_entity> base_api_model<T>::post_json(const utility::string_t &uri, const web::json::value &data,
                                                             const pplx::cancellation_token &cancellation_token) {
        web::http::http_request request(web::http::methods::POST);
        web::uri_builder login_uri(uri);
        request.set_request_uri(login_uri.to_string());
        auto &headers = request.headers();
        headers.add(web::http::header_names::accept, _XPLATSTR("application/json"));
        headers.add(web::http::header_names::content_type, _XPLATSTR("application/json"));
        const auto &token = token_store::instance().get_token();
        if (!token.empty()) {
            headers.add(_XPLATSTR("Token"), token);
        }
        request.set_body(data);
        //auto cancellation_token = cancellation_token_source.get_token();
        response_entity response_data;
        try {
            client_static::get_client().request(request, cancellation_token).then([&response_data](web::http::http_response response) {
                //return pplx::task_from_result(false);
                response_data.status = response.status_code();
                return response.extract_json(true).then([&response_data](web::json::value v){
                    if (v.has_field(_XPLATSTR("token"))) {
                        utility::string_t new_token = v.at(_XPLATSTR("token")).as_string();
                        token_store::instance().update_token(new_token);
                    }
                    auto success = v[_XPLATSTR("success")].as_bool();
                    response_data.success = success;
                    if (v.has_field(_XPLATSTR("message"))) {
                        response_data.message = v.at(_XPLATSTR("message")).as_string();
                    }
                    if (v.has_field(_XPLATSTR("code"))) {
                        response_data.code = v.at(_XPLATSTR("code")).as_string();
                    }
                    if (v.has_field(_XPLATSTR("result"))) {
                        response_data.result = v.at(_XPLATSTR("result"));
                    }
                    if (v.has_field(_XPLATSTR("status"))) {
                        response_data.status = v.at(_XPLATSTR("status")).as_integer();
                    }
                    //return pplx::task_from_result(response_re);
                });
            }).wait();
        } catch (const pplx::task_canceled &e) {
            if(response_data.status != 0){
                response_data.status = -99999;
            }
            response_data.message = utility::conversions::to_string_t(e.what());
        } catch (web::http::http_exception & http_ex) {
            if (http_ex.error_code() == std::errc::operation_canceled) {

                if(response_data.status != 0){
                    response_data.status = -99999;
                }
                response_data.message = utility::conversions::to_string_t(http_ex.what());
            }
            else {

                response_data.success = false;
                if(response_data.status != 0){
                    response_data.status = -1;
                }
                response_data.result = web::json::value();
                response_data.message = utility::conversions::to_string_t(http_ex.what());
            }
        } catch (const std::exception &e) {

            if(response_data.status != 0){
                response_data.status = -1;
            }
            response_data.result = web::json::value();
            response_data.message = utility::conversions::to_string_t(e.what());
        }
        return pplx::task_from_result(response_data,cancellation_token);
    }

    template<class T>
    pplx::task<response_entity> base_api_model<T>::post_json(const utility::string_t &uri, const web::json::value &data,
                                                             const pplx::cancellation_token_source &cancellation_token_source) {
        return post_json(uri,data,cancellation_token_source.get_token());
    }
}

#endif //QINGZHENYUN_LITE_BASE_API_MODEL_H
