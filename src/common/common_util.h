//
// Created by zzzhr on 2018/10/27.
//

#ifndef QINGZHENYUN_LITE_COMMON_UTIL_HPP
#define QINGZHENYUN_LITE_COMMON_UTIL_HPP

#include "cpprest/details/basic_types.h"
#include "./common_fs.h"

namespace qingzhen {
    class util {
    public:
        static std::string random_string();
		static utility::string_t format_remote_path(utility::string_t str);
        static utility::string_t random_string_t();
        static utility::string_t utf8_to_md5(utility::string_t& str);
        static time_t get_current_linux_timestamp();
		static utility::string_t convert_path(const common_fs::path &path);
    };
}

#endif //QINGZHENYUN_LITE_COMMON_UTIL_HPP
