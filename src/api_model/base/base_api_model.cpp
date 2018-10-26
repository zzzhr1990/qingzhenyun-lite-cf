//
// Created by zzzhr on 2018/10/25.
//

#include "base_api_model.h"
#include "token_store.h"
using namespace web::http;


pplx::task<response_entity>
qingzhen::api::base_api_model::post_json(const utility::string_t &uri, const web::json::value &data) {
    http_request request(methods::POST);
    web::uri_builder login_uri(uri);
    request.set_request_uri(login_uri.to_string());
    auto &headers = request.headers();
    headers.add(header_names::accept, _XPLATSTR("application/json"));
    headers.add(header_names::content_type, _XPLATSTR("application/json"));
    const auto &token = token_store::instance().get_token();
    if (!token.empty()) {
        headers.add(_XPLATSTR("Token"), token);
    }
    request.set_body(data);
    //raw_client.c
    const pplx::task<response_entity> resp = client_static::get_client().request(request).then(
            [](pplx::task<http_response> response_task) {
                try {
                    auto json_response = response_task.get();
                    auto json = json_response.extract_json(true);
                    auto v = json.get();
                    if (v.has_field(_XPLATSTR("token"))) {
                        utility::string_t new_token = v.at(_XPLATSTR("token")).as_string();
                        token_store::instance().update_token(new_token);
                    }
                    auto success = v[_XPLATSTR("success")].as_bool();
                    response_entity response;
                    response.success = success;
                    if (v.has_field(_XPLATSTR("message"))) {
                        response.message = v.at(_XPLATSTR("message")).as_string();
                    }
                    if (v.has_field(_XPLATSTR("code"))) {
                        response.code = v.at(_XPLATSTR("code")).as_string();
                    }
                    if (v.has_field(_XPLATSTR("result"))) {
                        response.result = v.at(_XPLATSTR("result"));
                    }
                    if (v.has_field(_XPLATSTR("status"))) {
                        response.status = v.at(_XPLATSTR("status")).as_integer();
                    }
                    return pplx::create_task([response]() {
                        return response;
                    });
                }
                catch (const std::exception &e) {
                    response_entity response;
                    response.success = false;
                    response.status = -1;
                    response.result = web::json::value();
                    response.message = utility::conversions::to_string_t(e.what());
                    return pplx::create_task([response]() {
                        return response;
                    });
                }

            }, pplx::task_continuation_context::use_default());

    return resp;
}

void qingzhen::api::base_api_model::post_json(const utility::string_t &uri, const web::json::value &data,
                                              std::function<void(response_entity)> callback) {
    //response_entity response;
    //response.success = false;
    //response.status = -1;
    //response.result = web::json::value();
    /*
    this->post_json(uri,data).then([](response_entity &entity) -> void {
        //callback(entity);
    });
     */

    this->post_json(uri,data).then([callback](response_entity entity) -> void {
        callback(entity);
    });
}

void qingzhen::api::base_api_model::then_json(const pplx::task<response_entity> task,
                                              std::function<void(response_entity)> callback) {
    task.then([callback](response_entity entity) -> void {
        callback(entity);
    });
}

/*
void qingzhen::api::base_api_model::then_json(const pplx::task<response_entity> & task,
                                              std::function<void(response_entity)> callback) {
    //response_entity response;
    //response.success = false;
    //response.status = -1;
    //response.result = web::json::value();
    task.then([callback](response_entity &entity) -> void {
        callback(entity);
    });
}
 */