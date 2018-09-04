//
// Created by zzzhr on 2018/9/4.
//

#ifndef QINGZHENYUN_LITE_USERMODEL_H
#define QINGZHENYUN_LITE_USERMODEL_H
#include "wx/wxprec.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include "cpprest/http_client.h"
#include "../util/simple_timer.h"
#include "../util/common_api.h"

class UserModel {
public:
    static UserModel& Instance();
    void GetUserInfo(wxWindow* handler);
    void StartUserCheckLoop(wxWindow* handler);
    void SetUserInfo(web::json::value v,const bool& login = false);
    bool IsUserLogin();
    void Logout();
    void CheckToken(wxWindow* handler);
    void UpdateToken(const utility::string_t& token);
    utility::string_t & GetToken();
    void Terminate();
    void TryLogin(wxWindow* handler,const utility::string_t& value,const utility::string_t &password);
private:
    UserModel():timer(){

    }
    ~UserModel(){
        this->Terminate();

    };
    void CheckUserAvailable(wxWindow* handler);
    SimpleTimer timer;
    utility::string_t currentToken = U("");
    web::json::value userInfo;
    bool login = false;
    bool threadRunning = false;
    long lastRefreshTime = 0;
};

#endif //QINGZHENYUN_LITE_USERMODEL_H
