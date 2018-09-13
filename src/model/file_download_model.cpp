//
// Created by zzzhr on 2018/9/10.
//
#include "../util/common_api.h"
#include <cpprest/filestream.h>
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace utility;

using namespace web;
using namespace concurrency;
using namespace web::http;
using namespace web::http::client;

//using namespace functional::http::utilities;
#ifdef U
#undef U
#include "tbb/concurrent_vector.h"
#endif

#include "boost/filesystem.hpp"
#include "../util/simple_timer.h"
#include "../util/common_util.h"


#define DOWNLOADSTATUS_DOWNLOADING 1;
#define DOWNLOADSTATUS_WAITING 0;
#define DOWNLOADSTATUS_ERROR  -1;
#define DOWNLOADSTATUS_FINISH 2;

enum file_download_status {
    predending = 0,
    downloading = 1,
    finished = 2,
    failed = -1
};

struct SingleUrlTask{
    utility::size64_t fileSize;
    utility::size64_t processedSize;
    utility::string_t localPath;
    web::http::message_direction::direction direction;
    utility::string_t filename;
    utility::string_t remotePath;
    utility::string_t hash;
    int status;
};

struct DownloadTask{
    tbb::concurrent_vector<SingleUrlTask*> task;
    utility::size64_t fileSize;
    utility::size64_t processedSize;
    utility::string_t localPath;
    web::http::message_direction::direction direction;
    utility::string_t filename;
    utility::string_t remotePath;
    int fileCount;
    int type;
};

#include "file_download_model.h"
class FileDownloadModelEx:public FileDownloadModel{
public:
    FileDownloadModelEx():timer(){
        auto x = [&]() {
            if(!checking){
                checking = true;
                this->CheckTaskStatus();
                checking = false;
            }
        };
        timer.StartTimer(1000,x);
    };
    void StartDownloadFile(const web::json::value & value,const utility::string_t& downloadPath) override;
    ~FileDownloadModelEx();
private:
    void DownloadSingleFile(const web::json::value &value,const utility::string_t &url,SingleUrlTask *urlTask);
    void StartInnerDownload(SingleUrlTask* urlTask);
    void CheckTaskStatus(); //
    tbb::concurrent_vector<DownloadTask*> taskList;
    SimpleTimer timer;
    bool checking = false;
    size_t BlockCount(size64_t fileLength);
};


FileDownloadModel& FileDownloadModel::Instance() {
    static FileDownloadModelEx c;
    return c;

}

void FileDownloadModelEx::StartDownloadFile(const web::json::value &value,const utility::string_t& downloadPath) {
    utility::string_t localUrl = downloadPath;
    localUrl.push_back(boost::filesystem::path::preferred_separator);
    if(!value.has_field(_XPLATSTR("path"))){
        return;
    }
    auto path = value.at(_XPLATSTR("path")).as_string();
    //check task exists...
    for (auto task : taskList) {
        if(task->remotePath == path){
            return;
        }
    }
    // create new task...
    //
    auto task = new DownloadTask();
    //using try catch
    try
    {
        // fill data..
        task->remotePath = value.at(_XPLATSTR("path")).as_string();
        task->direction = message_direction::download;
        task->filename = value.at(_XPLATSTR("name")).as_string();
        task->fileCount = 0;
        task->fileSize = 0;
        task->processedSize = 0;
        task->localPath = localUrl.append(task->filename);
        task->type = value.at(_XPLATSTR("type")).as_integer();
        if(task->type == 1){
            std::cout << "Explorer all files" << std::endl;
        }
        else{
            //DownloadSingleFile(value);
            // Adding single file to task.
            auto singleTask = new SingleUrlTask();
            try {
                // add new task...
                singleTask->processedSize = 0;
                singleTask->fileSize = value.at(_XPLATSTR("size")).as_number().to_uint64();
                task->fileSize = singleTask->fileSize;
                task->fileCount = 1;
                singleTask->direction = task->direction;
                singleTask->filename = task->filename;
                singleTask->remotePath = task->remotePath;
                singleTask->localPath = task->localPath;
                task->task.push_back(singleTask);
                //std::cout << "Adding new task:" << singleTask->localPath << std::endl;
            }catch (std::exception &e){
                delete singleTask;
                throw e;
            }

        };
        this->taskList.push_back(task);
    } catch (std::exception &e){
        auto singleTaskList = task->task;
        for(auto singleTask : singleTaskList){
            delete singleTask;
        }
        delete task;
    }
    //return;
}

void FileDownloadModelEx::DownloadSingleFile(const web::json::value &value,const utility::string_t &url,SingleUrlTask *urlTask) {
    //Okay,Starting Download...
    const method mtd = methods::GET;
    std::cout << "Downloading file to " << urlTask->localPath << std::endl;
    auto fileBuffer = std::make_shared<streambuf<uint8_t>>();
    // utility::size64_t upsize = 0, downsize = 0;
    streams::ostream responseStream = streams::bytestream::open_ostream<std::vector<uint8_t>>();
    http_client_config config;
    //config.set_timeout(1000 * 30);
    config.set_chunksize(1024 * 4);
    http_client client(url, config);
    http_request msg(mtd);
    msg.set_progress_handler(
            [&,urlTask](message_direction::direction direction, utility::size64_t so_far)
            {
                //std::cout << "Progress called..." << so_far << std::endl;
                //calls += 1;

                //if (direction == message_direction::upload)
                urlTask->processedSize = so_far;
                //else
                //    urlTask->processedSize = so_far;


                /*
                if(urlTask->fileSize > 0){
                    std::cout << "Progress ...(" << so_far * 100 / urlTask->fileSize << "):" << so_far << std::endl;
                }
                 */

                //msg.body()
                //msg.get_response()
            });
    auto cx = file_buffer<uint8_t>::open(urlTask->localPath, std::ios::out).then([=,&client,&msg](streambuf<uint8_t> outFile) {
                *fileBuffer = outFile;
                msg.set_response_stream(outFile);
                return client.request(msg);
            })
            .then([=](http_response response) -> pplx::task<http_response>
                  {
                      return response.content_ready();
                  }).then([=](http_response response)->pplx::task<void> {
                return fileBuffer->close();
            });
    try {
        cx.get();
        // calc tags..

        urlTask->status = file_download_status::finished;
    }catch (std::exception &ex){
        std::cout << "Download failed:" << ex.what() << std::endl;
        urlTask->status = file_download_status::failed;
        return;
    }
    unsigned char BYTE_LOW_4 = 0x16;
    unsigned char BYTE_OVER_4 =  0x96;
    file_buffer<uint8_t>::open(urlTask->localPath, std::ios::in).then([&,urlTask](streambuf<uint8_t> outFile){
        size64_t size =  outFile.size();
        auto blockCount = BlockCount(size);
        unsigned char finalDigest[ SHA_DIGEST_LENGTH + 1];
        if (blockCount <= 1) {

            unsigned char tempDigest[SHA_DIGEST_LENGTH];
            outFile.set_buffer_size(1024,std::ios::in);
            auto fSize = size;
            SHA_CTX shaCtx;
            SHA1_Init( &shaCtx );
            while (fSize > 0){
                unsigned char buffer[1024];
                auto actSize = outFile.getn(buffer, 1024).get();
                // calc sha1
                SHA1_Update(&shaCtx,buffer, actSize);
                fSize -= actSize;
            }
            SHA1_Final( tempDigest, &shaCtx );
            finalDigest[0] = BYTE_LOW_4;
            for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {//SHA1 20
                finalDigest[i + 1] = tempDigest[i];
            }
        }else{
            int BLOCK_BITS = 22;
            int BLOCK_SIZE = 1 << BLOCK_BITS;//2^22 = 4M
            unsigned char rec[ SHA_DIGEST_LENGTH * blockCount];
            unsigned char tempDigest[SHA_DIGEST_LENGTH];
            finalDigest[0] = BYTE_OVER_4;
            int i, cnt = 0;
            outFile.set_buffer_size(1024,std::ios::in);
            auto fSize = size;
            for (i = 0; i < blockCount; i++) {
                SHA_CTX shaCtx;
                SHA1_Init( &shaCtx );
                // Read Block..
                size_t currentRead = 0;
                while (fSize > 0){

                    unsigned char buffer[1024];
                    auto actSize = outFile.getn(buffer, 1024).get();
                    // calc sha1
                    SHA1_Update(&shaCtx,buffer, actSize);
                    fSize -= actSize;
                    currentRead += actSize;
                    if(currentRead >= BLOCK_SIZE){
                        break;
                    }
                }
                SHA1_Final( tempDigest, &shaCtx );
                for (unsigned char j : tempDigest) {
                    rec[cnt++] = j;
                }
            }
            //again. sh1
            unsigned char fDigest[SHA_DIGEST_LENGTH];
            SHA_CTX shaCtx;
            SHA1_Init( &shaCtx );
            SHA1_Update(&shaCtx,rec, SHA_DIGEST_LENGTH * blockCount);
            SHA1_Final( fDigest, &shaCtx );
            for (i = 0; i < SHA_DIGEST_LENGTH; ++i) {//0x96
                finalDigest[i + 1] = fDigest[i];
            }
        }
        //unsigned char * enc_output ;
        auto res = Base64Encode(finalDigest, SHA_DIGEST_LENGTH + 1, false, true);
        if(urlTask->hash.c_str() == res){
            urlTask->status = file_download_status::finished;
        }else{
            urlTask->status = file_download_status::failed;
            std::cout << "Hash check failed. Local Hash: " << res << " Remote: " << urlTask->hash << std::endl;
        }
        free(res);
        return outFile.close();
        //
    }).get();
    std::cout << "Download Fin..." << std::endl;
}

size_t FileDownloadModelEx::BlockCount(size64_t fileLength) {
    int BLOCK_BITS = 22;
    int BLOCK_SIZE = 1 << BLOCK_BITS;

    return ((fileLength + (BLOCK_SIZE - 1)) >> BLOCK_BITS);
}

FileDownloadModelEx::~FileDownloadModelEx() {
    timer.Expire();
    for (auto task : taskList) {
        // use first and second
        auto singleTaskList = task->task;
        for(auto singleTask : singleTaskList){
            delete singleTask;
        }
        delete task;
    }

}

void FileDownloadModelEx::CheckTaskStatus() {
    uint workingTaskCount = 0;
    uint totalTaskLimit = 5;

    for (auto task : taskList) {
        auto singleTaskList = task->task;
        for(auto singleTask : singleTaskList){
            //delete singleTask;
            if(singleTask->status == file_download_status::downloading){
                workingTaskCount++;
            }
        }
    }
    //uint needAdd = totalTaskLimit - workingTaskCount;
    for (auto task : taskList) {
        auto singleTaskList = task->task;
        for(auto singleTask : singleTaskList){
            //delete singleTask;
            if(singleTask->status == file_download_status::predending){
                //workingTaskCount++;
                this->StartInnerDownload(singleTask);
                auto needAdd = totalTaskLimit - workingTaskCount;
                if(needAdd < 1){
                    return;
                }else{
                    singleTask->status = file_download_status::downloading;
                    workingTaskCount++;
                }
            }
        }
    }
}

void FileDownloadModelEx::StartInnerDownload(SingleUrlTask *urlTask) {
    //Request File info
    web::json::value request;
    request[_XPLATSTR("path")] = web::json::value::string(urlTask->remotePath);
    CommonApi::Instance().PostData(_XPLATSTR("/v1/files/get"),request).then([&,urlTask](ResponseEntity v){
        //SendCommonThreadEvent(handler,USER_REMOTE_FILE_PAGE_DATA,v, true);
        if(v.success && v.result.has_field(_XPLATSTR("downloadAddress"))){
            //std::cout << v.result.at(_XPLATSTR("downloadAddress")).as_string() << std::endl;
            //this->DownloadTestFile(v.result.at(_XPLATSTR("downloadAddress")).as_string());
            urlTask->hash = v.result.at(_XPLATSTR("storeId")).as_string();
            this->DownloadSingleFile(v.result, v.result.at(_XPLATSTR("downloadAddress")).as_string(),urlTask);
        }
        else{
            //std::cout << "File Could not be download!" << std::endl;
            urlTask->status = file_download_status::failed;
        }
    });
}
/*
FileDownloadModelEx::FileDownloadModelEx() {
    UserModel():timer(){

        auto path = wxGetCwd() + wxFileName::GetPathSeparator() + "token.history";
        wxTextFile tfile(path);
        if (tfile.Exists()) {
            if (tfile.Open(wxConvUTF8)) {
                auto str = tfile.GetLastLine();
                if (str.length() > 0) {
                    currentToken = str;
                }
                tfile.Close();
            }
        }

        //currentToken = U("");
    }
}
*/
/*
void FileDownloadModelEx::~FileDownloadModelEx() {

}
 */
