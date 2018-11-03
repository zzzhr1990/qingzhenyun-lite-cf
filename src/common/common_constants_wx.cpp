//
// Created by zzzhr on 2018/11/2.
//

#include "common_constants_wx.h"

using namespace qingzhen::app;
const std::pair<wxString,wxString> common_constants:: DEFAULT_COUNTRY_CODE_PAIR [7] = {
        std::pair<wxString,wxString>(wxT("Default"),wxT("")),
        std::pair<wxString,wxString>(wxT("PRC (+86)"),wxT("86")),
        std::pair<wxString,wxString>(wxT("HonKong (+852)"),wxT("852")),
        std::pair<wxString,wxString>(wxT("Macao (+853)"),wxT("853")),
        std::pair<wxString,wxString>(wxT("Taiwan (+886)"),wxT("886")),
        std::pair<wxString,wxString>(wxT("USA (+1)"),wxT("1")),
        std::pair<wxString,wxString>(wxT("Japan (+81)"),wxT("81")),
};

wxArrayString common_constants::get_country_code_array() {
    wxArrayString arrayString;
    for(auto &p : DEFAULT_COUNTRY_CODE_PAIR){
        arrayString.Add(p.first);
    }
    return arrayString;
}

wxString common_constants::get_country_code(wxChoice *choice) {
    if(choice == nullptr){
        return wxString();
    }
    auto select = choice->GetSelection();
    if(select < (7 - 1)){
        return wxString();
    }
    return DEFAULT_COUNTRY_CODE_PAIR[select].second;
}