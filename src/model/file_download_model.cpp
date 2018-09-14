//
// Created by zzzhr on 2018/9/10.
//
#include "../util/common_api.h"

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


enum file_download_status {
    pretending = 0,
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

    void AddRefreshListener(const utility::string_t &key, wxWindow *window) override;

    void ForceRefresh(wxWindow *window) override;

    void StartDownloadFile(const web::json::value &value, const utility::string_t &downloadPath,
                           const utility::string_t &currentPath) override;
    ~FileDownloadModelEx();
private:
    void DownloadSingleFile(const web::json::value &value,const utility::string_t &url,SingleUrlTask *urlTask);
    void StartInnerDownload(SingleUrlTask* urlTask);
    void CheckTaskStatus(); //
    void CreateJsonReport();
    tbb::concurrent_vector<DownloadTask*> taskList;
    SimpleTimer timer;
    bool checking = false;
    std::map<utility::string_t, wxWindow *> refreshListener;
};


FileDownloadModel& FileDownloadModel::Instance() {
    static FileDownloadModelEx c;
    return c;

}

void FileDownloadModelEx::StartDownloadFile(const web::json::value &value, const utility::string_t &downloadPath,
                                            const utility::string_t &currentPath) {
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

    auto fileBuffer = std::make_shared<streambuf<uint8_t>>();
    // utility::size64_t upsize = 0, downsize = 0;
    streams::ostream responseStream = streams::bytestream::open_ostream<std::vector<uint8_t>>();
    http_client_config config;
    config.set_timeout(std::chrono::seconds(30));
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
    // check hash
    auto data = WcsFileHash(urlTask->localPath);
    if (urlTask->hash != data) {
        std::cout << "Download Failed, hash not match" << std::endl;
        urlTask->status = file_download_status::finished;
    } else {
        std::cout << "Download Success, hash match" << std::endl;
        urlTask->status = file_download_status::failed;
    }
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
            if (singleTask->status == file_download_status::pretending) {
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
            urlTask->hash = v.result.at(_XPLATSTR("storeId")).as_string();
            this->DownloadSingleFile(v.result, v.result.at(_XPLATSTR("downloadAddress")).as_string(),urlTask);
        }
        else{
            urlTask->status = file_download_status::failed;
        }
    });
}

void FileDownloadModelEx::AddRefreshListener(const utility::string_t &key, wxWindow *window) {
    refreshListener[key] = window;
}

void FileDownloadModelEx::ForceRefresh(wxWindow *window) {

}

void FileDownloadModelEx::CreateJsonReport() {
    web::json::array response = web::json::value::array().as_array();

    //web::json::value postParameters = web::json::value::array();

    //postParameters[0] = web::json::value::string(_XPLATSTR("Test1"));
    //postParameters[1] = web::json::value::string(L"Test2");
    for (auto task : taskList) {
        //response[1] = response;
    }
    web::json::value resp;
    //resp[0] = response;
}