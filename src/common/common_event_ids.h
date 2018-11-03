//
// Created by zzzhr on 2018/9/4.
//

#ifndef QINGZHENYUN_LITE_COMMON_EVENT_IDS_H
#define QINGZHENYUN_LITE_COMMON_EVENT_IDS_H
#include "common_wx.h"
#include "../entity/response_entity.h"
// #define COMMON_THREAD_EVENT_STRING = "@@@event"
enum {
    USER_AUTH_EXPIRED = 401,
	USER_GOTO_DIRECTORY = 3004,
    USER_SYNC_LIST_REFRESH = 4004,
    USER_SYNC_SPEED_REFRESH = 4005,
	USER_PREVIEW_INFO = 5002,
    PAGE_TIMER_TICK = 5003,
    VIDEO_LOG_MESSAGE = 5004,
    VIDEO_PREVIEW_FRAME_CLOSE = 5005,
    VIDEO_PLAYER_WAKEUP = 5006
};

static void SendCommonThreadEvent(wxWindow* handler,const int& type_id, const response_entity & v, const bool & checkMessage=false) {
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
