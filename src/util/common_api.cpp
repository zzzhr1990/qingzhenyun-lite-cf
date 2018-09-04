//
// Created by zzzhr on 2018/9/4.
//

#include "common_api.h"
#include "../model/user_model.h"

CommonApi &CommonApi::Instance() {
    static CommonApi c;
    return c;
}

pplx::task<ResponseEntity> CommonApi::PostData(const utility::string_t &uri, const web::json::value &data) {
    using namespace web::http;
    http_request request(methods::POST);
    uri_builder login_uri(uri);
    request.set_request_uri(login_uri.to_string());
    auto & headers = request.headers();
    headers.add(header_names::accept, U("application/json"));
    headers.add(header_names::content_type, U("application/json"));
    auto &token = UserModel::Instance().GetToken();
    if (!token.empty()) {
        headers.add(U("Token"),token);
    }
    request.set_body(data);
    const pplx::task<ResponseEntity> resp = raw_client.request(request).then([](pplx::task<http_response> response_task){
        // if there is any task, cancel it.
        try
        {
            auto json_response = response_task.get();
            auto json = json_response.extract_json();
            auto v = json.get();
            if (v.has_field(U("token"))) {
                utility::string_t new_token = v.at(U("token")).as_string();
                UserModel::Instance().UpdateToken(new_token);
            }
            auto success = v[U("success")].as_bool();
            ResponseEntity response;
            response.success = success;
            if (v.has_field(U("message"))) {
                response.message = v.at(U("message")).as_string();
            }
            if (v.has_field(U("code"))) {
                response.code = v.at(U("code")).as_string();
            }
            if (v.has_field(U("result"))) {
                response.result = v.at(U("result"));
            }
            if (v.has_field(U("status"))) {
                response.status = v.at(U("status")).as_integer();
            }
            return pplx::create_task([response]() {
                return response;
            });
        }
        catch (const std::exception& e)
        {
            ResponseEntity response;
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

