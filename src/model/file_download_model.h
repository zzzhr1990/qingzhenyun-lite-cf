//
// Created by zzzhr on 2018/9/10.
//

#ifndef QINGZHENYUN_LITE_FILE_DOWNLOAD_MODEL_H
#define QINGZHENYUN_LITE_FILE_DOWNLOAD_MODEL_H
#include "cpprest/http_client.h"
//#include "tbb/concurrent_vector.h"
//#include "../entity/download_task.hpp"
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP

#include "wx/wx.h"

#endif

class FileDownloadModel {
public:
    static FileDownloadModel& Instance();

    virtual void StartDownloadFile(const web::json::value &value, const utility::string_t &downloadPath,
                                   const utility::string_t &currentPath) = 0;
    //void DownloadTestFile(const utility::string_t& url);
    //void TestFunction();

    virtual void AddRefreshListener(const utility::string_t &key, wxWindow *window) = 0;

    virtual void ForceRefresh(wxWindow *window) = 0;

    virtual void ReportSpeed(wxWindow* window) = 0;
private:
    //void DownloadSingleFile(const web::json::value & value);
    //DownloadTask downloadTask;
};



#endif //QINGZHENYUN_LITE_FILE_DOWNLOAD_MODEL_H
