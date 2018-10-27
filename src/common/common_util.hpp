//
// Created by zzzhr on 2018/10/27.
//

#ifndef QINGZHENYUN_LITE_COMMON_UTIL_HPP
#define QINGZHENYUN_LITE_COMMON_UTIL_HPP

#include "cpprest/details/basic_types.h"
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <chrono>
namespace qingzhen {
    class util {
    public:
        static utility::string_t utf8_to_md5(utility::string_t& str) {
            unsigned char digest[16];
            const char* string = str.data();

            MD5_CTX ctx;
            MD5_Init(&ctx);
            MD5_Update(&ctx, string, strlen(string));
            MD5_Final(digest, &ctx);
            //MD5_DIGEST_LENGTH
            char mdString[MD5_DIGEST_LENGTH * 2 + 1];
            for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
                sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
            std::string res = std::string(mdString);
            return utility::conversions::to_string_t(res);
        }

        static time_t get_current_linux_timestamp(){
            return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        }
    };
}

#endif //QINGZHENYUN_LITE_COMMON_UTIL_HPP
