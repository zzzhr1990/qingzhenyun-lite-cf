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
    };
}



#endif //QINGZHENYUN_LITE_APIUSERMODEL_H
