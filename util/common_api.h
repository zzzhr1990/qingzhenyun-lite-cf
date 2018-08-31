//
// Created by zzzhr on 2018/8/23.
//

#ifndef FUCK_COMMON_API_H
#define FUCK_COMMON_API_H

#include <cpprest/http_client.h>
#include "../entity/response_entity.h"
class CommonApi {
public:
    static CommonApi& Instance();
    pplx::task<ResponseEntity> PostData(const utility::string_t& uri, const web::json::value & data);
private:
    web::http::client::http_client_config _cfg;
    CommonApi():

    raw_client(_XPLATSTR("https://api.6pan.cn"))
    {
        _cfg.set_timeout(std::chrono::seconds(10));
    }

    web::http::client::http_client raw_client;
};

#endif //FUCK_COMMON_API_H
