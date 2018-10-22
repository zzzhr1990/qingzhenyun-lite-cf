//
// Created by zzzhr on 2018/10/19.
//

#ifndef QINGZHENYUN_LITE_UPDATE_MODEL_H
#define QINGZHENYUN_LITE_UPDATE_MODEL_H

#include "../common/common_wx.h"

class UpdateModel{
public:
    void CheckUpdate(wxWindow* handler);

    int GetCurrentVersion() {
        return 0;
    }

    wxString GetDisplayVersion(){
        return wxT("0.0.0");
    }

    const int GetType(){
        return 10;
    }

    void Terminate();

    static UpdateModel& Instance();

private:
    bool terminated = false;
};


#endif //QINGZHENYUN_LITE_UPDATE_MODEL_H
