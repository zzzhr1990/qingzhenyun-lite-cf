//
// Created by zzzhr on 2018/9/19.
//
#ifdef __WXWINDOWS__
#pragma comment(lib, "bcrypt.lib")
#endif // __WXWINDOWS__
#include "wcs_toolbox.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <thread>

std::vector<unsigned char> wcs::WcsToolbox::ReadVectorFromStream(std::istream &iss, const size_t &maxBufferSize) {
    if (iss.eof()) {
        return std::vector<unsigned char>(0);
    }
    size_t read = 0;
    std::vector<unsigned char> buffer = std::vector<unsigned char>(maxBufferSize);
    while (read < maxBufferSize && !iss.eof()) {
        auto readChar = static_cast<unsigned char>(iss.get());

        if (iss.eof()) {
            break;
        }
        buffer[read] = readChar;
        read++;
    }
    //buffer.resize()
    if (read < maxBufferSize) {
        buffer.resize(read);
    }
    return buffer;
}

utility::size64_t wcs::WcsToolbox::ReadBlockFromStream(std::istream &iss,
                                                       const utility::size64_t &blockSize,
                                                       size_t &bufferSize,
                                                       unsigned char *tempDigest) {
    SHA_CTX shaCtx;
    SHA1_Init(&shaCtx);

    utility::size64_t blockRead = 0;
    while (blockRead < blockSize) {
        auto buffer = ReadVectorFromStream(iss, bufferSize);
        auto bufferReadSize = buffer.size();
        if (bufferReadSize <= 0) {
            //block read finished
            break;
            // Hash
        }
        SHA1_Update(&shaCtx, buffer.data(), bufferReadSize);
        blockRead += bufferReadSize;
    }

    SHA1_Final(tempDigest, &shaCtx);

    return blockRead;
}

utility::size64_t
wcs::WcsToolbox::HashFileStream(std::istream &iss, const utility::size64_t &blockSize, size_t &bufferSize,
                                utility::string_t &base64Result,SingleUrlTask *task) {
    utility::size64_t fileRead = 0;
    if(task!= nullptr){
        task->status = file_download_status::hashing;
    }
    std::vector<unsigned char> rec = std::vector<unsigned char>();
    while (true){
        unsigned char tempDigest[SHA_DIGEST_LENGTH];
        utility::size64_t currentRead = ReadBlockFromStream(iss, blockSize, bufferSize,tempDigest);
        if(currentRead <= 0){
            break;
        }
        for(auto &c : tempDigest){
            rec.push_back(c);
        }
        fileRead += currentRead;
        if(task!= nullptr){
            task->processedSize = fileRead;
        }
        //ConvertSizeToDisplay(fileRead);
    }
    const unsigned char BYTE_LOW_4 = 0x16;
    const unsigned char BYTE_OVER_4 = 0x96;
    size_t digestSize = rec.size();
    unsigned char finalDigest[SHA_DIGEST_LENGTH + 1];
    std::cout << digestSize << std::endl;
    if(digestSize == SHA_DIGEST_LENGTH){
        finalDigest[0] = BYTE_LOW_4;
        for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {//SHA1 20
            finalDigest[i + 1] = rec[i];
        }
        //Single file
    }else{
        //finalDigest[0] = BYTE_OVER_4;
        unsigned char tempDigest[SHA_DIGEST_LENGTH];
        SHA_CTX shaCtx;
        SHA1_Init(&shaCtx);
        SHA1_Update(&shaCtx, rec.data(), digestSize);
        SHA1_Final(tempDigest, &shaCtx);
        finalDigest[0] = BYTE_OVER_4;
        for (auto i = 0; i < SHA_DIGEST_LENGTH; ++i) {//0x96
            finalDigest[i + 1] = tempDigest[i];
        }
    }

    std::vector<unsigned char> v(std::begin(finalDigest), std::end(finalDigest));
    auto base64 = utility::conversions::to_base64(v);
    //char * ch = base64.data();

    for (auto &i : base64) {
        if (i == '+') {
            i = '-';
        }

        if (i == '/') {
            i = '_';
        }
    }

    base64Result = base64;

    return fileRead;
}

web::http::client::http_client wcs::WcsToolbox::CreateWcsClient(const utility::string_t &url) {
    // = ;
    web::http::client::http_client_config config;
    config.set_timeout(std::chrono::seconds(30));
    config.set_chunksize(1024 * 4);
    web::http::client::http_client client(url, config);
    return client;
}

web::http::http_request wcs::WcsToolbox::CreateWcsRequest(const web::http::method &mtd) {
    // = ;
    web::http::http_request request(mtd);
    auto & headers = request.headers();
    headers.add(web::http::header_names::accept, _XPLATSTR("application/json"));
    return request;
}

utility::string_t
wcs::WcsToolbox::PostBlock(web::http::client::http_client &client, const utility::string_t &uploadToken,
                           const std::vector<unsigned char> &buffer, const long &blockIndex,
                           const utility::string_t &batch) {
    // PB
    auto readSize = buffer.size();
    utility::stringstream_t stream;
    stream << boost::format(_XPLATSTR("/mkblk/%1%/%2%")) % readSize % blockIndex;
    auto postUrl = stream.str();
    int tryTimes = 10;
    while ( tryTimes > 0)
    {
        try {
            auto request = CreateWcsRequest();
            web::uri_builder post_uri(postUrl);
            request.set_request_uri(post_uri.to_string());
            request.headers().add(web::http::header_names::content_type, _XPLATSTR("application/octet-stream"));
            //UploadBatch
            request.headers().add(_XPLATSTR("UploadBatch"), batch);
            request.headers().add(_XPLATSTR("Authorization"), uploadToken);
            request.set_body(buffer);
            web::json::value createBlkResult = client.request(request).get().extract_json(true).get();
            if (createBlkResult.has_field(_XPLATSTR("ctx"))) {
                return createBlkResult.at(_XPLATSTR("ctx")).as_string();
            }else{
                std::cout << "Post failed" << createBlkResult.serialize() << std::endl;
            }
        }catch (std::exception &e){
            std::cout << "Make block fail: " << e.what() << std::endl;
        }
        tryTimes -= 1;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    return utility::string_t();
}

utility::string_t
wcs::WcsToolbox::MakeFile(web::http::client::http_client &client, const utility::string_t &uploadToken,
                          const utility::string_t &batch, const utility::string_t &blocks,
                          const utility::size64_t &size) {
    utility::stringstream_t stream;
    stream << boost::format(_XPLATSTR("/mkfile/%1%")) % size;
    //string_t blkUrl = wxString::Format(wxT("/mkblk/%lld/%ld"), readSize, blockIndex);
    auto postUrl = stream.str();

    int tryTimes = 10;
    while ( tryTimes > 0){
        try {
            auto request = CreateWcsRequest();
            web::uri_builder post_uri(postUrl);
            request.set_request_uri(post_uri.to_string());
            request.headers().add(web::http::header_names::content_type, _XPLATSTR("text/plain"));
            request.headers().add(_XPLATSTR("UploadBatch"), batch);
            request.headers().add(_XPLATSTR("Authorization"), uploadToken);
            request.set_body(blocks);
            web::json::value createFileResult = client.request(request).get().extract_json(true).get();
            if (createFileResult.has_field(_XPLATSTR("hash"))) {
                return createFileResult.at(_XPLATSTR("hash")).as_string();
            }else{
                std::cout << "Post failed" << createFileResult.serialize() << std::endl;
                //return utility::string_t();
            }
        }catch (std::exception &e){
            std::cout << e.what() << std::endl;
        }
        tryTimes--;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    return utility::string_t();
}

utility::size64_t wcs::WcsToolbox::PostFile(const utility::string_t &uploadUrl, const utility::string_t &filePath,
                                            const utility::string_t &uploadToken, SingleUrlTask *task) {
    // Upload File
    //bool success = false;
    //// read binary file.
    ////    std::ifstream file(filePath, std::ios::binary);
    ////    std::vector<char> data;
    // 
    ////    file >> std::noskipws;
    ////    std::copy(std::istream_iterator<char>(file), std::istream_iterator<char>(), std::back_inserter(data));
    utility::size64_t BLOCK_SIZE = 1024 * 1024 * 4;
    utility::size64_t readBytes = 0;

    std::filebuf in;
    if (!in.open(filePath, std::ios::in)) {
        std::cout << "fail to open file" << std::endl;
        if(task != nullptr){
            task ->status = wcs::file_download_status::failed;
            task->error = sync_download_error::file_exception;
        }
        return 0;
    }
    // clear all errors
    if(task != nullptr){
        task ->status = wcs::file_download_status::proccessing;
        task ->error = wcs::sync_download_error::none;
    }
    std::istream iss(&in);
    // create Client
    auto client = CreateWcsClient(uploadUrl);
    boost::uuids::uuid id = boost::uuids::random_generator()();
    auto batch = boost::lexical_cast<utility::string_t>(id);
    //size_t block
    long index = 0;
    utility::string_t blocks;
    try {
        while (true){
            std::vector<unsigned char> buffer = ReadVectorFromStream(iss,BLOCK_SIZE);
            auto bufferReadSize = buffer.size();
            if(bufferReadSize <= 0){
                break;
            }
            utility::string_t blockCtx = PostBlock(client,uploadToken, buffer, index,batch);
            if(blockCtx.empty()){
                throw std::exception();
            }
            readBytes += bufferReadSize;
            if(index > 0){
                blocks += (_XPLATSTR(",") + blockCtx);
            }else{
                blocks += blockCtx;
            }
            index++;
            if(task != nullptr){
                task ->processedSize = readBytes;
            }
        }

        // std::cout << "MKFILE" << std::endl;
        //Do MKFILE
        utility::string_t fileHash = MakeFile(client,uploadToken,batch,blocks,readBytes);
        if(fileHash.empty()){
            task->status = wcs::file_download_status::failed;
            task->error = sync_download_error::upload_part_error;
        }
        if(task != nullptr){
            if(task->hash != fileHash){
                task->status = wcs::file_download_status::failed;
                task->error = sync_download_error::none;
            }else {
                task->error = sync_download_error::none;
                task->fileSize = readBytes;
                task->status = wcs::file_download_status::finished;
            }
        }
    }catch (std::exception &e){
        std::cout << e.what() << std::endl;
        if(task != nullptr){
            task ->status = wcs::file_download_status::failed;
            if(task->error == sync_download_error::none){
                task->error = sync_download_error::upload_part_error;
            }
        }
    }

    in.close();

    return readBytes;
}

utility::size64_t wcs::WcsToolbox::HashFile(const utility::string_t &filePath, utility::string_t &base64Result,
                                            wcs::SingleUrlTask *task) {
    std::filebuf in;
    if (!in.open(filePath, std::ios::in)) {
        std::cout << "fail to open file" << std::endl;
        if(task != nullptr){
            task ->status = wcs::file_download_status::failed;
            task->error = sync_download_error::file_exception;
        }
        return 0;
    }
    std::istream iss(&in);
    utility::size64_t MAX_BLOCK_SIZE = 1024 * 1024 * 4;
    size_t MAX_BUFFER_SIZE = 1024;
    utility::size64_t fileSize = HashFileStream(iss, MAX_BLOCK_SIZE,MAX_BUFFER_SIZE,base64Result,task);
    in.close();
    return fileSize;
}
