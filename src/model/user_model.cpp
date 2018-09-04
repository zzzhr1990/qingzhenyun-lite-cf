//
// Created by zzzhr on 2018/9/4.
//

#include "user_model.h"
#include "../common/common_event_ids.h"

UserModel &UserModel::Instance() {
    static UserModel c;
    return c;
}

utility::string_t &UserModel::GetToken() {
    return this->currentToken;
}

bool UserModel::IsUserLogin() {
    if(!this->login){
        return false;
    } else{
        return !currentToken.empty();
    }
}

void UserModel::StartUserCheckLoop(wxWindow *handler) {
    // this loop validate user login
    if(threadRunning){
        return;
    }else{
        threadRunning = true;
    }
    auto x = [&](wxWindow* handler) {
        long current =  std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        if (!this->currentToken.empty()) {
            long time_diff = current - lastRefreshTime;
            if(time_diff > 10){
                lastRefreshTime = current;
                this->CheckUserAvailable(handler);
            }else{
                std::cout << time_diff << std::endl;
            }
        }
    };
    timer.StartTimer(1000 * 30, std::bind(x, handler), true); // refresh user data every 30 sec.
}

void UserModel::CheckUserAvailable(wxWindow* handler) {
    const auto &task = CommonApi::Instance().PostData(U("/v1/user/info"), web::json::value::object(false));
    task.then([&, handler](ResponseEntity v){
        lastRefreshTime = 0;
        if(v.success){
            SendCommonThreadEvent(handler,USER_REFRESH_RESPONSE,v);
            this->userInfo = v.result;
        }else{
            if(v.status > 400 && v.status < 500){
                SendCommonThreadEvent(handler,USER_LOGIN_FAILED_RESPONSE,v);
            }
        }
    });
}

void UserModel::CheckToken(wxWindow* handler) {
    const auto &task = CommonApi::Instance().PostData(U("/v1/user/info"), web::json::value::object(false));
    task.then([&, handler](ResponseEntity v){
        if(v.success){
            SendCommonThreadEvent(handler,USER_LOGIN_RESPONSE,v);
        }else{
            SendCommonThreadEvent(handler,USER_LOGIN_FAILED_RESPONSE,v);
        }
    });
}

void UserModel::UpdateToken(const utility::string_t &token) {
    this->currentToken = token;
}

void UserModel::Terminate() {
    if(threadRunning){
        this->timer.Expire();
    }
    threadRunning = false;
}

void UserModel::GetUserInfo(wxWindow *handler) {

}

void UserModel::TryLogin(wxWindow *handler, const utility::string_t &value, const utility::string_t &password) {
    web::json::value json_v;
    json_v[U("value")] = web::json::value::string(value);
    json_v[U("password")] = web::json::value::string(password);
    const auto &task = CommonApi::Instance().PostData(U("/v1/user/login"), json_v);
    task.then([&,handler](ResponseEntity v){
        if(v.success){
            //Send success event.
            SendCommonThreadEvent(handler,USER_LOGIN_RESPONSE,v);
        }else{
            SendCommonThreadEvent(handler,USER_LOGIN_FAILED_RESPONSE,v);
        }
    });
}

void UserModel::SetUserInfo(web::json::value v, const bool& login) {
    if(login){
        this->login = true;
    }
    this->userInfo = v;
}

void UserModel::Logout() {
    Terminate();
    this->login = false;
    this->userInfo = web::json::value::object(false);
}

