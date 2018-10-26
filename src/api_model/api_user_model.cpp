//
// Created by zzzhr on 2018/10/25.
//

#include "api_user_model.h"

using namespace qingzhen::api;

api_user_model &api_user_model::instance() {
    static api_user_model c;
    return c;
}

void api_user_model::logout(std::function<void(response_entity)> &callback) {
    this->then_json(this->logout(),callback);
}


pplx::task<response_entity> api_user_model::logout() {
    web::json::value val = web::json::value::object();
    //val[_XPLATSTR("x")] = web::json::value::string(_XPLATSTR("2"));
    return this->post_json(_XPLATSTR("/v1/user/logout"),val);
}
