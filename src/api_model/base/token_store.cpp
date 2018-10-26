//
// Created by zzzhr on 2018/10/25.
//

#include "token_store.h"

qingzhen::api::token_store &qingzhen::api::token_store::instance() {
    static token_store c;
    return c;
}

void qingzhen::api::token_store::update_token(utility::string_t &token) {
    this->token = token;
}

void qingzhen::api::token_store::remove_token() {
    this->token = utility::string_t();
    this->save_token();
}

void qingzhen::api::token_store::save_token() {

}

utility::string_t qingzhen::api::token_store::get_token() {
    return this->token;
}
