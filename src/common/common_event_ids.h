//
// Created by zzzhr on 2018/9/4.
//

#ifndef QINGZHENYUN_LITE_COMMON_EVENT_IDS_H
#define QINGZHENYUN_LITE_COMMON_EVENT_IDS_H
#include "wx/wxprec.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#include "../entity/response_entity.h"
#endif
// #define COMMON_THREAD_EVENT_STRING = "@@@event"
enum {
    USER_AUTH_EXPIRED = 401,
    USER_LOGIN_RESPONSE = 1001,
    USER_REFRESH_RESPONSE = 1002,
    USER_LOGIN_FAILED_RESPONSE = 1003,
    USER_REMOTE_FILE_PAGE_DATA = 2001,
	USER_REMOTE_DIRECTORY_CREATE = 2002,
    USER_REMOTE_FILE_INFO = 2003,
    USER_REMOTE_FILE_DELETE = 2004,
    USER_REMOTE_TASK_PAGE_DATA = 3002,
	USER_REMOTE_TASK_CREATE = 3003,
	USER_GOTO_DIRECTORY = 3004,
	USER_REMOTE_TASK_URL_PARSED = 4002,
	USER_REMOTE_TASK_URL_START = 4003,
    USER_SYNC_LIST_REFRESH = 4004,
    USER_SYNC_SPEED_REFRESH = 4005,
	USER_PREVIEW_INFO = 5002,
    PAGE_TIMER_TICK = 5003
};

static void SendCommonThreadEvent(wxWindow* handler,const int& type_id, const ResponseEntity & v, const bool & checkMessage=false) {
    if(checkMessage){
        if(v.status == 401 || v.status == 403){
            if(handler == nullptr){
                return;
            }
            wxThreadEvent event(wxEVT_THREAD, handler->GetId());
            // event.SetString(COMMON_THREAD_EVENT_STRING);
            event.SetInt(USER_AUTH_EXPIRED);
            event.SetPayload(v);
            wxQueueEvent(handler, event.Clone());
            return;
        }
    }
    wxThreadEvent event(wxEVT_THREAD, handler->GetId());
	auto ts = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	event.SetTimestamp(ts);
    event.SetId(handler->GetId());
    event.SetInt(type_id);
    event.SetPayload(v);
    wxQueueEvent(handler, event.Clone());
}
#endif //QINGZHENYUN_LITE_COMMON_EVENT_IDS_H
