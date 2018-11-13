//
// Created by zzzhr on 2018/10/25.
//

#ifndef QINGZHENYUN_LITE_APIUSERMODEL_H
#define QINGZHENYUN_LITE_APIUSERMODEL_H
#include <functional>
#include "../entity/response_entity.h"
#include "base/base_api_model.h"

namespace qingzhen::api{
    class api_user_model : public base_api_model<api_user_model> {
    public:
        void logout(std::function<void(response_entity)> &callback, const pplx::cancellation_token_source &cancellation_token_source);
        pplx::task<response_entity> logout(const pplx::cancellation_token_source &cancellation_token_source);

        pplx::task<response_entity> login(utility::string_t& country_code,
                utility::string_t& value, utility::string_t& password, const pplx::cancellation_token_source &cancellation_token_source);

		pplx::task<response_entity> check_user_info(const pplx::cancellation_token_source &cancellation_token_source);

        pplx::task<response_entity> change_username_and_get(const pplx::cancellation_token_source &cancellation_token_source, const utility::string_t &name);

        pplx::task<response_entity>
        send_login_message(utility::string_t &country_code, utility::string_t &phone, const pplx::cancellation_token_source &cancellation_token_source);

        pplx::task<response_entity>
        send_register_message(utility::string_t &country_code, utility::string_t &phone, const pplx::cancellation_token_source &cancellation_token_source);

        pplx::task<response_entity> login_by_message(utility::string_t &phone_info, utility::string_t &code, const pplx::cancellation_token_source &cancellation_token_source);

        pplx::task<response_entity> register_by_message(utility::string_t &phone_info, utility::string_t &code,utility::string_t &password, const pplx::cancellation_token_source &cancellation_token_source);

        void login(utility::string_t& country_code,
                utility::string_t& value, utility::string_t& password,std::function<void(response_entity)> &callback, const pplx::cancellation_token_source &cancellation_token_source);
        web::json::value get_user_info();
        web::json::value set_user_info(web::json::value info);

        bool is_user_login();

        pplx::task<utility::string_t>  async_read_token();

        utility::string_t user_random_string();

    private:
        web::json::value user_info;
        bool user_login = false;
    };
}



#endif //QINGZHENYUN_LITE_APIUSERMODEL_H
