cmake_minimum_required(VERSION 3.9.0)
SET(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/scripts/buildsystems/vcpkg.cmake")
SET(LINKING_TYPE "dynamic")
SET(PROJECT_NAME "qingzhenyun-lite")
project(${PROJECT_NAME})
set(default_build_type "Debug")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
            STRING "Choose the type of build." FORCE)
endif()

if(MSVC)
    include(${CMAKE_SOURCE_DIR}/winmsvc.cmake)
else(MSVC)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
    find_package(wxWidgets REQUIRED COMPONENTS net core base)
    include(${wxWidgets_USE_FILE})
	find_package(Boost REQUIRED filesystem system chrono thread)
endif()
find_package(cpprestsdk CONFIG REQUIRED)
# include(${CMAKE_SOURCE_DIR}/FindLibtorrentRasterbar.cmake)
# find_package(FindLibtorrentRasterbar REQUIRED)
find_package(OpenSSL REQUIRED)


message(STATUS "CMAKE_BUILD_TYPE:${CMAKE_BUILD_TYPE}")
#file(GLOB helloworld_SRC
#    "*.h"
#    "*.cpp"
#)
if(MSVC)
    include_directories(
         "D:\\vlc-x86\\vlc-3.0.4\\sdk\\include"
	    "D:\\vlcpp"
    )

    link_directories(
        "D:\\vlc-x86\\vlc-3.0.4\\sdk\\link"
    )
elseif(APPLE)
    include_directories(
            "/Applications/VLC.app/Contents/MacOS/include"
            "/Users/zzzhr/Downloads/libvlcpp-master/vlcpp"
    )

    link_directories(
            "/Applications/VLC.app/Contents/MacOS/lib"
    )
endif()

# file(GLOB_RECURSE qingzhenyun_SRC  "*.h" "*.cpp")
file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp src/*.h src/*.xpm)
FOREACH(LETTER ${SRCS})
    string(FIND ${LETTER} "cmake-" SEARCH_POS)
    if(SEARCH_POS EQUAL -1)
        list(APPEND FINAL_RES ${LETTER})
    endif()
ENDFOREACH()
if(MSVC)
    add_executable(${PROJECT_NAME} WIN32 ${FINAL_RES} "icon.rc" "sample.ico")
else(MSVC)
    add_executable(${PROJECT_NAME} ${FINAL_RES})
endif()
if(MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES} ${Boost_LIBRARIES} "D:\\vlc-x86\\vlc-3.0.4\\sdk\\link\\libvlc.lib" "D:\\vlc-x86\\vlc-3.0.4\\sdk\\link\\libvlccore.lib" cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_boost_internal cpprestsdk::cpprestsdk_openssl_internal OpenSSL::SSL OpenSSL::Crypto)
else()
    target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} ${Boost_LIBRARIES} "/Applications/VLC.app/Contents/MacOS/lib/libvlc.5.dylib" "/Applications/VLC.app/Contents/MacOS/lib/libvlccore.9.dylib" cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_boost_internal cpprestsdk::cpprestsdk_openssl_internal OpenSSL::SSL OpenSSL::Crypto)
endif()