//
// Created by zzzhr on 2018/10/25.
//

#ifndef QINGZHENYUN_LITE_APIUSERMODEL_H
#define QINGZHENYUN_LITE_APIUSERMODEL_H
#include <functional>
#include "../entity/response_entity.h"
#include "base/base_api_model.h"

namespace qingzhen::api{
    class api_user_model : base_api_model {
    public:
        static api_user_model& instance();
        void logout(std::function<void(response_entity)> &callback);
        pplx::task<response_entity> logout();

        pplx::task<response_entity> login(utility::string_t& country_code,
                utility::string_t& value, utility::string_t& password);

        pplx::task<response_entity>
        send_login_message(utility::string_t &country_code, utility::string_t &phone);

        pplx::task<response_entity> login_by_message(utility::string_t &phone_info, utility::string_t &code);

        void login(utility::string_t& country_code,
                utility::string_t& value, utility::string_t& password,std::function<void(response_entity)> &callback);
        web::json::value get_user_info();
        web::json::value set_user_info(web::json::value info);

        bool is_user_login();

        pplx::task<utility::string_t>  async_read_token();

    private:
        web::json::value user_info;
        bool user_login = false;
    };
}



#endif //QINGZHENYUN_LITE_APIUSERMODEL_H
