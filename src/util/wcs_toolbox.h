//
// Created by zzzhr on 2018/9/19.
//
#ifdef _MSC_VER
#pragma comment(lib, "bcrypt.lib")
#endif // _MSC_VER
#ifndef QINGZHENYUN_LITE_WCS_TOOLBOX_H
#define QINGZHENYUN_LITE_WCS_TOOLBOX_H
#include <iostream>
#include <cpprest/details/basic_types.h>
#include <cpprest/http_client.h>
#include "../entity/task_info.h"

namespace wcs{
    class WcsToolbox {
    public:
        static std::vector<unsigned char> ReadVectorFromStream(std::istream &iss,const size_t& maxBufferSize = 1024);
        static utility::size64_t ReadBlockFromStream(std::istream &iss,const utility::size64_t &blockSize,size_t &bufferSize,unsigned char *tempDigest);
        static utility::size64_t HashFile(const utility::string_t &filePath, utility::string_t & base64Result,SingleUrlTask *task);
        static utility::size64_t HashFileStream(std::istream &iss, const utility::size64_t &blockSize,size_t &bufferSize, utility::string_t & base64Result,SingleUrlTask *task);
        static utility::size64_t PostFile(const utility::string_t &uploadUrl, const utility::string_t &filePath,const utility::string_t &uploadToken, SingleUrlTask *task = nullptr);
        static web::http::client::http_client CreateWcsClient(const utility::string_t& url);
        static web::http::http_request CreateWcsRequest(const web::http::method& mtd = web::http::methods::POST);
        static utility::string_t PostBlock(web::http::client::http_client &client,const utility::string_t &uploadToken,
                                    const std::vector<unsigned char> &buffer,
                                    const long &blockIndex,
                                    const utility::string_t &batch);
        static utility::string_t MakeFile(web::http::client::http_client &client,
                                   const utility::string_t &uploadToken,
                                   const utility::string_t &batch,
                                   const utility::string_t &blocks, const utility::size64_t &size);
    };
}


#endif //QINGZHENYUN_LITE_WCS_TOOLBOX_H
