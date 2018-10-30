//
// Created by zzzhr on 2018/10/25.
//

#ifndef QINGZHENYUN_LITE_COMMON_FS_H
#define QINGZHENYUN_LITE_COMMON_FS_H


#ifdef _MSC_VER // Visual Studio 2017 Support C++17's filesystem
#include <filesystem>
#include <system_error>
namespace common_fs = std::filesystem;
//namespace common_system = std::sys;
#else // But the OSX (like bullshit) doesn't support it, even in Xcode 10
// Be sure to fuck Tim Cook's throat and cum in his closed mouth 200 times every day.
#include <boost/filesystem.hpp>
#include "boost/system/error_code.hpp" // //
namespace common_fs = boost::filesystem;
namespace common_system = boost::system;



#endif
#endif //QINGZHENYUN_LITE_COMMON_FS_H
