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
#endif
#include <tbb/concurrent_vector.h>


#include <boost/filesystem.hpp>
#include "../util/simple_timer.h"
#include "../util/common_util.h"
#include "../common/common_event_ids.h"

enum file_download_status {
    pretending = 0,
    downloading = 1,
    finished = 2,
    failed = -1,
    info = 3
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
	utility::string_t localDirectory;
    web::http::message_direction::direction direction;
    utility::string_t filename;
    utility::string_t remotePath;
    int fileCount;
    int type;
    int status;
    int progress;
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
    void ReportSpeed(wxWindow* window) override;

    void ForceRefresh(wxWindow *window) override;

    void StartDownloadFile(const web::json::value &value, const utility::string_t &downloadPath,
                           const utility::string_t &currentPath) override;
    void StartUploadFile(const wxArrayString &fileNames,
                         const utility::string_t &currentPath) override;



    ~FileDownloadModelEx();
private:
    void DownloadSingleFile(const web::json::value &value,const utility::string_t &url,SingleUrlTask *urlTask);
    void StartInnerDownload(SingleUrlTask* urlTask);
    void CheckTaskStatus(); //
    void ReportStatus();

    long lastRefreshTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    size64_t lastUpSize = 0;
    size64_t lastDownSize = 0;
    size64_t upSpeed = 0;
    size64_t downSpeed = 0;
    int upCount = 0;
    int downCount = 0;
    web::json::value CreateJsonReport();
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
		task->localDirectory = localUrl;
        task->localPath = localUrl.append(task->filename);
        task->type = value.at(_XPLATSTR("type")).as_integer();
        task->status = file_download_status::pretending;
        task->progress = 0;
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
		std::cout << e.what() << std::endl;
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
                //std::cout<< "Setting Download:" << urlTask->processedSize << std::endl;
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
        std::cout << "Download Failed, hash not match Remote:" << urlTask->hash << " Local:" << data << std::endl;
        urlTask->status = file_download_status::failed;
    } else {
        urlTask->status = file_download_status::finished;
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
    unsigned int upWorkingTaskCount = 0;
	unsigned int downWorkingTaskCount = 0;
	unsigned int totalTaskLimit = 5;
    long current = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto timeDiff = current - lastRefreshTime;
    bool check = timeDiff > 0;
    size64_t upSize = 0;
    size64_t downSize = 0;
    for (auto task : taskList) {
        auto singleTaskList = task->task;
        for(auto singleTask : singleTaskList){
            //delete singleTask;

            if(singleTask->direction == message_direction::download){
                if(singleTask->status == file_download_status::downloading){
                    downWorkingTaskCount++;
                }
                downSize += singleTask->processedSize;
            }else{
                if(singleTask->status == file_download_status::downloading){
                    upWorkingTaskCount++;
                }
                upSize += singleTask->processedSize;
            }
            //singleTask->processedSize
            //std::cout << singleTask->filename << std::endl;
            //std::cout << singleTask->processedSize << std::endl;
            // check fin..
        }
        auto size = singleTaskList.size();
        if(size == 1){
            task->status = singleTaskList[0]->status;
            task->processedSize = singleTaskList[0]->processedSize;
            task->fileSize = singleTaskList[0]->fileSize;
            task->progress = (static_cast<int>(task->processedSize * 100 / task->fileSize));
            if(task->progress > 100){
                task->progress = 100;
            }
            if(task->progress < 0){
                task->progress = 0;
            }
        }
    }
    if(check){
        auto upDiff = upSize - lastUpSize;
        auto downDiff = downSize - lastDownSize;
        lastUpSize = upSize;
        lastDownSize = downSize;


        downSpeed = downDiff / timeDiff;
        upSpeed = upDiff / timeDiff;
        lastRefreshTime = current;
    }
    //uint needAdd = totalTaskLimit - workingTaskCount;
    downCount = downWorkingTaskCount;
    upCount = upWorkingTaskCount;
    for (auto task : taskList) {
        auto singleTaskList = task->task;
        for(auto singleTask : singleTaskList){
            //delete singleTask;
            if (singleTask->status == file_download_status::pretending) {
                //workingTaskCount++;
                auto needAdd = totalTaskLimit - downWorkingTaskCount;
                if(needAdd < 1){
                    return;
                }else{
                    singleTask->status = file_download_status::info;
                    this->StartInnerDownload(singleTask);
                    //singleTask->status = file_download_status::downloading;
                    downWorkingTaskCount++;
                }
            }
        }
    }



    //ReportStatus();
}

void FileDownloadModelEx::StartInnerDownload(SingleUrlTask *urlTask) {
    //Request File info
    web::json::value request;
    request[_XPLATSTR("path")] = web::json::value::string(urlTask->remotePath);
    CommonApi::Instance().PostData(_XPLATSTR("/v1/files/get"),request).then([&,urlTask](ResponseEntity v){
        //SendCommonThreadEvent(handler,USER_REMOTE_FILE_PAGE_DATA,v, true);
        if(v.success && v.result.has_field(_XPLATSTR("downloadAddress"))){
            urlTask->hash = v.result.at(_XPLATSTR("storeId")).as_string();
            urlTask->status = file_download_status::downloading;
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
    //Use PPLX
    pplx::create_task([&]() {
        // return response;
        // std::cout << "REPORT_STATUS" << std::endl;
        this->ReportStatus();
    });
}

web::json::value FileDownloadModelEx::CreateJsonReport() {
    web::json::array response = web::json::value::array().as_array();

    //web::json::value postParameters = web::json::value::array();

    //postParameters[0] = web::json::value::string(_XPLATSTR("Test1"));
    //postParameters[1] = web::json::value::string(L"Test2");
    std::vector<web::json::value> value;
    for (auto task : taskList) {
        web::json::value reportTask;
        reportTask[_XPLATSTR("processedSize")] = web::json::value::number(task->processedSize);
        reportTask[_XPLATSTR("name")] = web::json::value::string(task->filename);
        reportTask[_XPLATSTR("type")] = web::json::value::number(task->type);
        reportTask[_XPLATSTR("localPath")] = web::json::value::string(task->localPath);
		reportTask[_XPLATSTR("localDirectory")] = web::json::value::string(task->localDirectory);
        reportTask[_XPLATSTR("remotePath")] = web::json::value::string(task->remotePath);
        reportTask[_XPLATSTR("size")] = web::json::value::number(task->fileSize);
        reportTask[_XPLATSTR("direction")] = web::json::value::number(task->direction);
        reportTask[_XPLATSTR("fileCount")] = web::json::value::number(task->fileCount);
        reportTask[_XPLATSTR("status")] = web::json::value::number(task->status);
        reportTask[_XPLATSTR("progress")] = web::json::value::number(task->progress);
		//localDirectory
        //reportTask[_XPLATSTR("fileCount")] = web::json::value::number(task->);
        value.push_back(reportTask);
    }
    return web::json::value::array(value);
    //resp[0] = response;
}

void FileDownloadModelEx::ReportStatus() {
    if (!refreshListener.empty()) {
        for (auto &x : refreshListener) {
            ResponseEntity responseEntity;
            responseEntity.status = 200;
            responseEntity.success = true;
            responseEntity.result = CreateJsonReport();
            SendCommonThreadEvent(x.second, USER_SYNC_LIST_REFRESH, responseEntity, false);
        }
    }
}

void FileDownloadModelEx::ReportSpeed(wxWindow* window) {
    pplx::create_task([&,window]() {
        ResponseEntity responseEntity;
        responseEntity.status = 200;
        responseEntity.success = true;
        web::json::value reportTask;
        reportTask[_XPLATSTR("upCount")] = web::json::value::number(this->upCount);
        reportTask[_XPLATSTR("downCount")] = web::json::value::number(this->downCount);
        reportTask[_XPLATSTR("upSpeed")] = web::json::value::number(this->upSpeed);
        reportTask[_XPLATSTR("downSpeed")] = web::json::value::number(this->downSpeed);
        responseEntity.result = reportTask;
        SendCommonThreadEvent(window, USER_SYNC_SPEED_REFRESH, responseEntity, false);
    });

}

void FileDownloadModelEx::StartUploadFile(const wxArrayString &fileNames, const utility::string_t &currentPath) {

}
