//
// Created by zzzhr on 2018/10/25.
//

#ifndef QINGZHENYUN_LITE_COMMON_FS_H
#define QINGZHENYUN_LITE_COMMON_FS_H


#ifdef _MSC_VER
#include <filesystem>
#include <system_error>
namespace common_fs = boost::filesystem;
namespace common_system = std::system;
#else
#include <boost/filesystem.hpp>
#include "boost/system/error_code.hpp"
namespace common_fs = boost::filesystem;
namespace common_system = boost::system;



#endif
#endif //QINGZHENYUN_LITE_COMMON_FS_H
