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
    private:
        utility::string_t token;
    };
};


#endif //QINGZHENYUN_LITE_TOKEN_STORE_H
