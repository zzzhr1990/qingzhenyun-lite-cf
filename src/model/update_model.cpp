//
// Created by zzzhr on 2018/10/19.
//

#include "update_model.h"
#include "../common/common_event_ids.h"
#include "../util/common_api.h"
#include <wx/platinfo.h>
#include <cpprest/http_client.h>


void UpdateModel::CheckUpdate(wxWindow *handler) {
    auto platform = wxPlatformInfo::Get();
    web::json::value value = web::json::value();
    value[_XPLATSTR("platform")] = web::json::value::number(platform.GetOperatingSystemId());
    value[_XPLATSTR("type")] = web::json::value::number(this->GetType());
    value[_XPLATSTR("version")] = web::json::value::number(this->GetCurrentVersion());
    value[_XPLATSTR("arch")] = web::json::value::number(platform.GetArchitecture() == wxArchitecture::wxARCH_64 ? 64 : 32);
    CommonApi::Instance().PostData(U("/v1/user/checkUpdate"), value).then([handler,this](ResponseEntity v) {
        if (this->terminated){
            return;
        }
        SendCommonThreadEvent(handler, PROGRAM_UPDATE_INFO, v);
    });
}

UpdateModel &UpdateModel::Instance() {
    static UpdateModel c;
    return c;
}

void UpdateModel::Terminate() {
    terminated = true;
}

