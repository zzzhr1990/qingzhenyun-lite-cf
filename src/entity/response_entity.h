//
// Created by zzzhr on 2018/9/4.
//
#ifndef FUCK_ResponseEntity_H
#define FUCK_ResponseEntity_H
#include <cpprest/http_client.h>

struct ResponseEntity
{
    /*
    ResponseEntity(const bool &success, const web::json::value & result, const int &code) {
    this->success = success;
    this->result = result;
    this->code = code;
    };
    */

    /*
     * utility::stringstream_t stream;
        payload.result.serialize(stream);

        std::cout << stream.str() << std::endl;
     */
    bool success;
    web::json::value  result;
    utility::string_t  code;
    int status;
    utility::string_t message;
};


#endif //QINGZHENYUN_LITE_RESPONSE_ENTITY_H
