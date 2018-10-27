//
// Created by zzzhr on 2018/10/25.
//

#ifndef QINGZHENYUN_LITE_TOKEN_STORE_H
#define QINGZHENYUN_LITE_TOKEN_STORE_H

#include <cpprest/json.h>

namespace qingzhen::api {
    class token_store {
    public:
        static token_store& instance();
        void update_token(utility::string_t& token);
        void remove_token();
        void save_token();
        utility::string_t get_token();
        pplx::task<utility::string_t> async_read_token();
    private:
        utility::string_t token;
        bool first_time = true;
        time_t last_update_time;
    };
};


#endif //QINGZHENYUN_LITE_TOKEN_STORE_H
