//
// Created by zzzhr on 2018/10/25.
//

#include "api_user_model.h"
#include "../common/common_util.hpp"
#include "./base/token_store.h"
using namespace qingzhen::api;

api_user_model &api_user_model::instance() {
    static api_user_model c;
    return c;
}

void api_user_model::logout(std::function<void(response_entity)> &callback, const pplx::cancellation_token_source &cancellation_token_source) {
    this->then_json(this->logout(cancellation_token_source),callback);
}


pplx::task<response_entity> api_user_model::logout(const pplx::cancellation_token_source &cancellation_token_source) {

    token_store::instance().remove_token();
    web::json::value val = web::json::value::object();
    //val[_XPLATSTR("x")] = web::json::value::string(_XPLATSTR("2"));
    return this->post_json(_XPLATSTR("/v1/user/logout"),val, cancellation_token_source);
}

pplx::task<response_entity>
api_user_model::login(utility::string_t &country_code, utility::string_t &value, utility::string_t &password, const pplx::cancellation_token_source &cancellation_token_source) {
    web::json::value val = web::json::value::object();
    val[_XPLATSTR("countryCode")] = web::json::value::string(country_code);
    val[_XPLATSTR("value")] = web::json::value::string(value);
    // password should be encode
	auto md5_str = qingzhen::util::utf8_to_md5(password);
	val[_XPLATSTR("password")] = web::json::value::string(md5_str);
    return this->post_json(_XPLATSTR("/v1/user/login"),val, cancellation_token_source);
}

pplx::task<response_entity>
api_user_model::check_user_info(const pplx::cancellation_token_source &cancellation_token_source) {
	web::json::value val = web::json::value::object(false);
	val[_XPLATSTR("time")] = web::json::value::number(qingzhen::util::get_current_linux_timestamp());	// password should be encode
	return this->post_json(_XPLATSTR("/v1/user/info"), val, cancellation_token_source);
}

pplx::task<response_entity>
api_user_model::send_login_message(utility::string_t &country_code, utility::string_t &phone, const pplx::cancellation_token_source &cancellation_token_source) {
    web::json::value val = web::json::value::object();
    val[_XPLATSTR("countryCode")] = web::json::value::string(country_code);
    val[_XPLATSTR("phone")] = web::json::value::string(phone);
    // password should be encode
    return this->post_json(_XPLATSTR("/v1/user/sendLoginMessage"),val, cancellation_token_source);
}

void api_user_model::login(utility::string_t &country_code, utility::string_t &value, utility::string_t &password,
                           std::function<void(response_entity)> &callback, const pplx::cancellation_token_source &cancellation_token_source) {
    this->then_json(this->login(country_code, value, password, cancellation_token_source), callback);
}

pplx::task<response_entity>
api_user_model::login_by_message(utility::string_t &phone_info, utility::string_t &code, const pplx::cancellation_token_source &cancellation_token_source) {
    web::json::value val = web::json::value::object();
    val[_XPLATSTR("phoneInfo")] = web::json::value::string(phone_info);
    val[_XPLATSTR("code")] = web::json::value::string(code);
    // password should be encode
    return this->post_json(_XPLATSTR("/v1/user/loginByMessage"),val, cancellation_token_source);
}

web::json::value api_user_model::get_user_info() {
    return this->user_info;
}

web::json::value api_user_model::set_user_info(web::json::value info) {
    if(info.is_null() || !info.has_field(_XPLATSTR("uuid"))){
        this->user_login = false;
        return info;
    }
    this->user_login = true;
    this->user_info = info;
    return info;
}

bool api_user_model::is_user_login() {
    return this->user_login;
}

pplx::task<utility::string_t> api_user_model::async_read_token() {
    return token_store::instance().async_read_token();
}

