//
// Created by zzzhr on 2018/10/25.
//

#ifndef QINGZHENYUN_LITE_COMMON_FS_H
#define QINGZHENYUN_LITE_COMMON_FS_H

#include <boost/filesystem.hpp>
#ifdef _MSC_VER
namespace common_fs = boost::filesystem;
#else
namespace common_fs = boost::filesystem;
#endif
#endif //QINGZHENYUN_LITE_COMMON_FS_H
