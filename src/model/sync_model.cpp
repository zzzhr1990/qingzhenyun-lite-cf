//
// Created by zzzhr on 2018/9/10.
//
#include "../util/common_api.h"
#ifdef __WXWINDOWS__
#pragma comment(lib, "bcrypt.lib")
#endif // __WXWINDOWS__
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
#include <boost/uuid/uuid_generators.hpp>
#include <boost/filesystem.hpp>
#include <boost/uuid/uuid.hpp>
#ifdef U
#undef U
#endif
#define U(x) _XPLATSTR(x)
#endif
#include "../util/simple_timer.h"
#include "../util/common_util.h"
#include "../common/common_event_ids.h"
#include <wx/filename.h>
#include "../util/wcs_toolbox.h"
#include <wx/dir.h>





#include "sync_model.h"

class SyncModelEx : public SyncModel {
public:
    SyncModelEx() : timer() {
        auto x = [&]() {
            if (!checking) {
                checking = true;
                this->CheckTaskStatus();
                checking = false;
            }
        };
        timer.StartTimer(1000, x);
    };

    void AddRefreshListener(const utility::string_t &key, wxWindow *window) override;

    void ReportSpeed(wxWindow *window) override;

    void ForceRefresh(wxWindow *window) override;

    void StartDownloadFile(const web::json::value &value, const utility::string_t &downloadPath,
                           const utility::string_t &currentPath) override;

    void StartUploadFile(const wxArrayString &fileNames,
                         const utility::string_t &currentPath) override;


    ~SyncModelEx();

private:
    void DownloadSingleFile(const web::json::value &value, const utility::string_t &url, wcs::SingleUrlTask *urlTask);

    void StartInnerDownload(wcs::SingleUrlTask *urlTask);

    void StartInnerUpload(wcs::SingleUrlTask *urlTask);

    void StartUploadFile(wcs::SingleUrlTask *urlTask, const utility::string_t &postUrl, const utility::string_t &token,
                         const utility::string_t &path);

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

    tbb::concurrent_vector<wcs::DownloadTask *> taskList;
    SimpleTimer timer;
    bool checking = false;
    bool allFinished = true;
    std::map<utility::string_t, wxWindow *> refreshListener;
};


SyncModel &SyncModel::Instance() {
    static SyncModelEx c;
    return c;

}

void SyncModelEx::StartDownloadFile(const web::json::value &value, const utility::string_t &downloadPath,
                                    const utility::string_t &currentPath) {
    utility::string_t localUrl = downloadPath;
    localUrl.push_back(boost::filesystem::path::preferred_separator);
    if (!value.has_field(_XPLATSTR("path"))) {
        return;
    }
    auto path = value.at(_XPLATSTR("path")).as_string();
    //check task exists...
    for (auto task : taskList) {
        if (task->remotePath == path) {
            return;
        }
    }
    // create new task...
    //
    auto task = new wcs::DownloadTask();
    //using try catch
    try {
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
        task->status = wcs::file_download_status::pretending;
        task->progress = 0;
        if (task->type == 1) {
            std::cout << "Explorer all files" << std::endl;
        } else {
            // DownloadSingleFile(value);
            // Adding single file to task.
            auto singleTask = new wcs::SingleUrlTask();
            try {
                // add new task...
                singleTask->retryCount = 5;
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
            } catch (std::exception &e) {
                delete singleTask;
                throw e;
            }

        };
        this->taskList.push_back(task);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        auto singleTaskList = task->task;
        for (auto singleTask : singleTaskList) {
            delete singleTask;
        }
        delete task;
    }
    //return;
}

void
SyncModelEx::DownloadSingleFile(const web::json::value &value, const utility::string_t &url, wcs::SingleUrlTask *urlTask) {
    //Okay,Starting Download...
    const method mtd = methods::GET;
    auto fileBuffer = std::make_shared<streambuf<uint8_t>>();
    streams::ostream responseStream = streams::bytestream::open_ostream<std::vector<uint8_t>>();
    http_client_config config;
    config.set_timeout(std::chrono::seconds(30));
    config.set_chunksize(1024 * 4);
    http_client client(url, config);
    http_request msg(mtd);
    msg.set_progress_handler(
            [&, urlTask](message_direction::direction direction, utility::size64_t so_far) {
                urlTask->processedSize = so_far;

            });
    auto cx = file_buffer<uint8_t>::open(urlTask->localPath, std::ios::out).then(
                    [=, &client, &msg](streambuf<uint8_t> outFile) {
                        *fileBuffer = outFile;
                        msg.set_response_stream(outFile);
                        return client.request(msg);
                    })
            .then([=](http_response response) -> pplx::task<http_response> {
                return response.content_ready();
            }).then([=](http_response response) -> pplx::task<void> {
                return fileBuffer->close();
            });
    try {
        cx.get();
    } catch (std::exception &ex) {
        urlTask->status = wcs::file_download_status::failed;
        urlTask->error = wcs::sync_download_error::unknown;
        std::cout << ex.what() << std::endl;
        return;
    }
    // check hash
    utility::string_t data;
	const auto &file = wxFileName(urlTask->localPath);
	if (file.GetSize() < urlTask->fileSize) {
		urlTask->status = wcs::file_download_status::failed;
		urlTask->error = wcs::sync_download_error::size_not_match;
		return;
	}
    wcs::WcsToolbox::HashFile(urlTask->localPath,data,urlTask);
    if (urlTask->hash != data) {
        //std::cout << "Download Failed, hash not match Remote:" << urlTask->hash << " Local:" << data << std::endl;
        urlTask->status = wcs::file_download_status::failed;
        urlTask->error = wcs::sync_download_error::hash_not_match;
    } else {
        urlTask->status = wcs::file_download_status::finished;
    }
}


SyncModelEx::~SyncModelEx() {
    timer.Expire();
    for (auto task : taskList) {
        // use first and second
        auto singleTaskList = task->task;
        for (auto singleTask : singleTaskList) {
            delete singleTask;
        }
        delete task;
    }

}

void SyncModelEx::CheckTaskStatus() {
    bool _allFinished = true;
    unsigned int upWorkingTaskCount = 0;
    unsigned int downWorkingTaskCount = 0;
    unsigned int downloadTaskLimit = 5;
    unsigned int uploadTaskLimit = 2;
    long current = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto timeDiff = current - lastRefreshTime;
    bool check = timeDiff > 0;
    size64_t upSize = 0;
    size64_t downSize = 0;
    for (auto task : taskList) {
        auto singleTaskList = task->task;
        //auto size = singleTaskList.size();
        bool needChange = false;
        bool processing = false;
        utility::size64_t processedSize = 0;
        utility::size64_t fileSize = 0;
        //int progress = 0;
        int error = 0;
        int status = task->status;
        bool allFinish = true;
        for (auto singleTask : singleTaskList) {
            //delete singleTask;
            //
            if (status != wcs::file_download_status::finished) {
                needChange = true;
                if (singleTask->status != wcs::file_download_status::finished) {
                    status = singleTask->status;
                    if (singleTask->status == wcs::file_download_status::proccessing ||
                        singleTask->status == wcs::file_download_status::info || singleTask->status == wcs::file_download_status::hashing) {
                        processing = true;
                    }
                    allFinish = false;
                }

                processedSize += singleTask->processedSize;
                fileSize += singleTask->fileSize;
                error = singleTask->error;
                //progress = (static_cast<int>(task->fileSize > 0 ? (task->processedSize * 100 / task->fileSize) : 0));

                /*
                if(size == 1){
                    task->status = singleTaskList[0]->status;
                    task->processedSize = singleTaskList[0]->processedSize;
                    task->fileSize = singleTaskList[0]->fileSize;
                    task->
                    if(task->progress > 100){
                        task->progress = 100;
                    }
                    if(task->progress < 0){
                        task->progress = 0;
                    }
                    task->error = singleTaskList[0]->error;
                }else{

                }*/
            }
            if (singleTask->direction == message_direction::download) {
                if (singleTask->status == wcs::file_download_status::proccessing ||
                    singleTask->status == wcs::file_download_status::hashing ||
                    singleTask->status == wcs::file_download_status::info) {
                    downWorkingTaskCount++;
                    if(singleTask->status != wcs::file_download_status::hashing){
                        downSize += singleTask->processedSize;
                    }

                }

            } else {
                if (singleTask->status == wcs::file_download_status::proccessing ||
                    singleTask->status == wcs::file_download_status::hashing ||
                    singleTask->status == wcs::file_download_status::info) {
                    upWorkingTaskCount++;
                    if(singleTask->status != wcs::file_download_status::hashing){
                        upSize += singleTask->processedSize;
                    }

                }
            }
            //singleTask->processedSize
            //std::cout << singleTask->filename << std::endl;
            //std::cout << singleTask->processedSize << std::endl;
            // check fin..

        }

        //change status...
        if (needChange) {
            if (allFinish) {
                task->status = wcs::file_download_status::finished;
            } else {
                if (processing && task->fileCount > 1) {
                    task->status = wcs::file_download_status::proccessing;
                } else {
                    task->status = status;
               }

            }
            if (error != 0) {
                task->error = error;
            }
            if (fileSize > 0) {
                task->fileSize = fileSize;
            }
            if (processedSize > 0) {
                task->processedSize = processedSize;
            }
            int progress = (static_cast<int>(task->fileSize > 0 ? (task->processedSize * 100 / task->fileSize) : 0));
            if (progress > 100) {
                progress = 100;
            }
            if (progress < 0) {
                progress = 0;
            }
            task->progress = progress;
        }
    }
    if (check) {
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
        for (auto *singleTask : singleTaskList) {
            //delete singleTask;
            if (singleTask->status == wcs::file_download_status::pretending) {
                //workingTaskCount++;
                if (singleTask->direction == message_direction::download) {
                    auto needAdd = downloadTaskLimit - downWorkingTaskCount;
                    if (needAdd < 1) {
                        continue;
                    } else {
                        singleTask->status = wcs::file_download_status::info;
                        this->StartInnerDownload(singleTask);
                        //singleTask->status = file_download_status::proccessing;
                        downWorkingTaskCount++;
                    }
                } else {
                    auto needAdd = uploadTaskLimit - upWorkingTaskCount;
                    if (needAdd < 1) {
                        continue;
                    } else {
                        singleTask->status = wcs::file_download_status::info;
                        pplx::create_task([&,singleTask]{
                            this->StartInnerUpload(singleTask);
                        });

                        //singleTask->status = file_download_status::proccessing;
                        upWorkingTaskCount++;
                    }
                }
            }
        }
        if(task->status == wcs::file_download_status::finished || task->status == wcs::file_download_status::failed){
            if(task->status == wcs::file_download_status::finished && !singleTaskList.empty()){
                for (auto *p : task->task){
                    delete p;
                }
                task->task.clear();
            }
            /*
            if(task->status == wcs::file_download_status::finished && !singleTaskList.empty()){
                while (!singleTaskList.empty()){
                    singleTaskList.back();
                }
                for (auto singleTask : singleTaskList) {
                    delete singleTask;
                }
                //singleTaskList.clear();
                //task->fileCount = 0;
            }
             */
        }else{
            _allFinished = false;
        }
    }



    this->allFinished = _allFinished;
    //ReportStatus();
}

void SyncModelEx::StartInnerDownload(wcs::SingleUrlTask *urlTask) {
    //Request File info
    web::json::value request;
    request[_XPLATSTR("path")] = web::json::value::string(urlTask->remotePath);
    CommonApi::Instance().PostData(_XPLATSTR("/v1/files/get"), request).then([&, urlTask](ResponseEntity v) {
        //SendCommonThreadEvent(handler,USER_REMOTE_FILE_PAGE_DATA,v, true);
        if (v.success && v.result.has_field(_XPLATSTR("downloadAddress"))) {
            urlTask->hash = v.result.at(_XPLATSTR("storeId")).as_string();
            urlTask->status = wcs::file_download_status::proccessing;
            this->DownloadSingleFile(v.result, v.result.at(_XPLATSTR("downloadAddress")).as_string(), urlTask);

        } else {
            urlTask->status = wcs::file_download_status::failed;
            urlTask->error = wcs::sync_download_error::url_api_error;
        }
    });
}

void SyncModelEx::StartInnerUpload(wcs::SingleUrlTask *urlTask) {
    //Request File info
    auto &filePath = urlTask->localPath;
    web::json::value request;
    request[_XPLATSTR("path")] = web::json::value::string(urlTask->remotePath);
    // calc hash
    auto file_hash = utility::string_t();
    wcs::WcsToolbox::HashFile(filePath,file_hash,urlTask);
    if (file_hash.empty()) {
        urlTask->status = wcs::file_download_status::failed;
        urlTask->error = wcs::sync_download_error::calc_hash_fail;
        return;
    }
    urlTask->hash = file_hash;
    request[_XPLATSTR("hash")] = web::json::value::string(file_hash);
    CommonApi::Instance().PostData(_XPLATSTR("/v1/store/token"), request).then(
            [&, urlTask, filePath](ResponseEntity v) {
                //SendCommonThreadEvent(handler,USER_REMOTE_FILE_PAGE_DATA,v, true);
                // && v.result.has_field(_XPLATSTR("downloadAddress"))) {
                //urlTask->hash = v.result.at(_XPLATSTR("storeId")).as_string();
                //urlTask->status = file_download_status::proccessing;
                //this->DownloadSingleFile(v.result, v.result.at(_XPLATSTR("downloadAddress")).as_string(), urlTask);
                if (v.success) {

                    if (v.result.has_field(_XPLATSTR("token"))) {
                        auto &token = v.result.at(_XPLATSTR("token")).as_string();
                        auto &uploadUrl = v.result.at(_XPLATSTR("uploadUrl")).as_string();
                        urlTask->status = wcs::file_download_status::proccessing;
                        this->StartUploadFile(urlTask, uploadUrl, token, filePath);
                    } else {
                        if (v.result.has_field(_XPLATSTR("storeId"))) {
                            urlTask->status = wcs::file_download_status::finished;
                            urlTask->processedSize = urlTask->fileSize;
                        } else {
                            urlTask->status = wcs::file_download_status::failed;
                            urlTask->error = wcs::sync_download_error::url_api_error;
                        }
                    }
                } else {
                    std::cout << "Get TOKEN FAIL" << std::endl;
                    urlTask->status = wcs::file_download_status::failed;
                    urlTask->error = wcs::sync_download_error::token_api_error;
                }
            });
}

void SyncModelEx::AddRefreshListener(const utility::string_t &key, wxWindow *window) {
    refreshListener[key] = window;
}

void SyncModelEx::ForceRefresh(wxWindow *window) {
    //Use PPLX
    pplx::create_task([&]() {
        // return response;
        // std::cout << "REPORT_STATUS" << std::endl;
        this->ReportStatus();
    });
}

web::json::value SyncModelEx::CreateJsonReport() {
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
        reportTask[_XPLATSTR("error")] = web::json::value::number(task->error);
        //localDirectory
        //reportTask[_XPLATSTR("fileCount")] = web::json::value::number(task->);
        value.push_back(reportTask);
    }
    return web::json::value::array(value);
    //resp[0] = response;
}

void SyncModelEx::ReportStatus() {
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

void SyncModelEx::ReportSpeed(wxWindow *window) {
    pplx::create_task([&, window]() {
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

void SyncModelEx::StartUploadFile(const wxArrayString &fileNames, const utility::string_t &currentPath) {
    // do it async

    pplx::create_task([&, fileNames, currentPath]() {
        // for each files.

        for (size_t i = 0; i < fileNames.GetCount(); ++i) {
            // m_list.AddToPlayList(files[i]);
            //std::cout << "Drag file:" << fileNames[i] << std::endl;
            auto task = new wcs::DownloadTask();
            auto path = fileNames[i];
            const auto &file = wxFileName(path);
            const auto &name = file.GetFullName();
            const auto &remote = currentPath + "/" + name;

            task->remotePath = remote;
            task->direction = message_direction::upload;
            task->filename = name;
            task->fileCount = 0;
            task->fileSize = 0;
            task->processedSize = 0;

            task->localPath = path;
            task->localDirectory = path.BeforeLast(wxFileName::GetPathSeparator());
            task->type = 0;
            task->status = wcs::file_download_status::pretending;

            //std::cout << "file " << path << " type" << file.IsDir() << " size:" << file.GetSize() << std::endl;
            //wxFile1.

            if (file.Exists(wxFILE_EXISTS_REGULAR)) {
                if (file.IsFileReadable()) {
                    // add file direct to upload list
                    auto singleTask = new wcs::SingleUrlTask();
                    singleTask->retryCount = 5;
                    singleTask->processedSize = 0;
                    singleTask->fileSize = file.GetSize().GetValue();
                    task->fileSize = singleTask->fileSize;
                    task->fileCount = 1;
                    singleTask->direction = task->direction;
                    singleTask->filename = task->filename;
                    singleTask->remotePath = task->remotePath;
                    singleTask->localPath = task->localPath;
                    task->task.push_back(singleTask);
                } else {
                    continue;
                }
            } else if (file.Exists(wxFILE_EXISTS_DIR)) {
                if (file.IsDirReadable()) {
                    //file.get
                    wxDir dir(path);
                    //dir.
                    wxArrayString childFolders;
                    // wxDIR_FILES | wxDIR_HIDDEN
                    wxDir::GetAllFiles(path, &childFolders, wxEmptyString);

                    for (size_t ix = 0; ix < childFolders.GetCount(); ++ix) {
                        auto filePath = childFolders[ix];
                        auto relativePath = filePath.SubString(path.length(), filePath.length());
                        // Create Requests..
                        wxFileName single = wxFileName(filePath);
                        if (single.Exists(wxFILE_EXISTS_REGULAR)) {
                            if (single.IsFileReadable()) {
                                // add file direct to upload list
                                auto singleTask = new wcs::SingleUrlTask();
                                singleTask->retryCount = 5;
                                singleTask->processedSize = 0;
                                singleTask->fileSize = single.GetSize().GetValue();
                                task->fileSize += singleTask->fileSize;
                                task->fileCount += 1;
                                singleTask->direction = task->direction;
                                singleTask->filename = single.GetFullName();
                                singleTask->remotePath = task->remotePath + relativePath;
                                singleTask->localPath = filePath;
                                task->task.push_back(singleTask);
                            } else {
                                continue;
                            }
                        }

                    }
                }
            } else {

                // is dir, not support now.
                /*
                if (file.IsDirReadable()) {
                    //file.get
                    wxDir dir(path);
                    dir.
                }
                 */
                /*
                wxArrayString *childFolders = new wxArrayString;
                wxDir::GetAllFiles(path,childFolders);

                for (size_t ix = 0; ix < childFolders->GetCount(); ++ix) {
                    // m_list.AddToPlayList(files[i]);
                    std::cout << "Child file:" << std::endl;
                }
                */

            }

            if (task->fileCount > 0) {
                this->taskList.push_back(task);
            } else {
                delete task;
            }
        }
    });
}


void
SyncModelEx::StartUploadFile(wcs::SingleUrlTask *urlTask, const utility::string_t &postUrl, const utility::string_t &token,
                             const utility::string_t &path) {

    wcs::WcsToolbox::PostFile(postUrl, path, token, urlTask);
}
