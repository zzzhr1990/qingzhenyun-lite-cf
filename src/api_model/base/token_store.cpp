//
// Created by zzzhr on 2018/10/25.
//

#include "token_store.h"
#include "../../local_model/config_model.h"
#include "../../common/common_util.hpp"

qingzhen::api::token_store &qingzhen::api::token_store::instance() {
    static token_store c;
    return c;
}

void qingzhen::api::token_store::update_token(utility::string_t &token) {
    this->token = token;
    auto current = qingzhen::util::get_current_linux_timestamp();
    if(first_time){
        this->save_token();
        last_update_time = current;
        return;
    }

    if(current - last_update_time > 120){
        this->save_token();
        last_update_time = current;
    }
}

void qingzhen::api::token_store::remove_token() {
    this->token = utility::string_t();
    this->save_token();
    this->first_time = true;
}

void qingzhen::api::token_store::save_token() {
    config_model::instance().update_token(this->token);
}

utility::string_t qingzhen::api::token_store::get_token() {
    return this->token;
}

pplx::task<utility::string_t> qingzhen::api::token_store::async_read_token() {
    return config_model::instance().async_read_token();
}


