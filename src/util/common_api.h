//
// Created by zzzhr on 2018/9/4.
//

#ifndef QINGZHENYUN_LITE_COMMON_APU_H
#define QINGZHENYUN_LITE_COMMON_APU_H

#include <cpprest/http_client.h>
#include "../entity/response_entity.h"

class CommonApi {
public:
    static CommonApi& Instance();
    pplx::task<ResponseEntity> PostData(const utility::string_t& uri, const web::json::value & data);
private:

    // CommonApi();
    // web::http::client::http_client_config _cfg;
    CommonApi():
    /*
     *
    raw_client(_XPLATSTR("https://api.6pan.cn"),_cfg)
    {
        _cfg.set_timeout(std::chrono::seconds(10));
    }
     */
    raw_client(_XPLATSTR("https://api.6pan.cn"))
    {
        //_cfg.set_timeout(std::chrono::seconds(10));
    }

    web::http::client::http_client raw_client;
};

#endif //QINGZHENYUN_LITE_COMMON_APU_H