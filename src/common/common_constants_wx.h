//
// Created by zzzhr on 2018/11/2.
//

#ifndef QINGZHENYUN_LITE_COMMON_CONSTANTS_H
#define QINGZHENYUN_LITE_COMMON_CONSTANTS_H

#include <utility>
#include "./common_wx.h"

namespace qingzhen::app{
    class common_constants {
    public:
        static const std::pair<wxString,wxString> DEFAULT_COUNTRY_CODE_PAIR [7];
        static wxArrayString get_country_code_array();
        static wxString get_country_code(wxChoice *choice);
    };
}



#endif //QINGZHENYUN_LITE_COMMON_CONSTANTS_H
