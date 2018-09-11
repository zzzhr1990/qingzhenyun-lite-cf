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


struct SingleUrlTask{
    utility::size64_t fileSize;
    utility::size64_t processedSize;
    utility::string_t localPath;
    web::http::message_direction::direction direction;
    utility::string_t filename;
    utility::string_t remotePath;
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
    void StartDownloadFile(const web::json::value & value) override;
    ~FileDownloadModelEx();
private:
    //tbb::concurrent_vector<DownloadTask&> taskList;
    void DownloadSingleFile(const web::json::value & value);
    void DownloadTestFile(const utility::string_t& url);
    tbb::concurrent_vector<DownloadTask*> taskList;

};


FileDownloadModel& FileDownloadModel::Instance() {
    static FileDownloadModelEx c;
    return c;

}

void FileDownloadModelEx::StartDownloadFile(const web::json::value &value) {
    std::cout << "Start Download File... " << boost::filesystem::path::preferred_separator << std::endl;
    utility::string_t localUrl = _XPLATSTR("/Users/zzzhr/Downloads/test");
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

void FileDownloadModelEx::DownloadSingleFile(const web::json::value &value) {

}

void FileDownloadModelEx::DownloadTestFile(const utility::string_t &url) {

}

FileDownloadModelEx::~FileDownloadModelEx() {
    for (auto task : taskList) {
        // use first and second
        auto singleTaskList = task->task;
        for(auto singleTask : singleTaskList){
            delete singleTask;
        }
        delete task;
    }
}

/*
void FileDownloadModelEx::~FileDownloadModelEx() {

}
 */
