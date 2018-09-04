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
    USER_REMOTE_TASK_PAGE_DATA = 2002
};

static void SendCommonThreadEvent(wxWindow* handler,const int& type_id, const ResponseEntity & v, const bool & checkMessage=false) {
    if(checkMessage){
        if(v.status == 401 || v.status == 403){
            wxThreadEvent event(wxEVT_THREAD, handler->GetId());
            // event.SetString(COMMON_THREAD_EVENT_STRING);
            event.SetInt(USER_AUTH_EXPIRED);
            event.SetPayload(v);
            wxQueueEvent(handler, event.Clone());
            return;
        }
    }
    wxThreadEvent event(wxEVT_THREAD, handler->GetId());
    event.SetId(handler->GetId());
    event.SetInt(type_id);
    event.SetPayload(v);
    wxQueueEvent(handler, event.Clone());
}
#endif //QINGZHENYUN_LITE_COMMON_EVENT_IDS_H
