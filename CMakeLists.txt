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
#	find_package(Boost REQUIRED filesystem)
else(MSVC)
    set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
    find_package(wxWidgets REQUIRED COMPONENTS net core base all)
    include(${wxWidgets_USE_FILE})
endif()
if(APPLE)
	find_library(IOKit IOKit)
	#find_library(Keneral Keneral)
endif()
find_package(Boost REQUIRED filesystem system chrono thread random)
find_package(cpprestsdk CONFIG REQUIRED)
# include(${CMAKE_SOURCE_DIR}/FindLibtorrentRasterbar.cmake)
# find_package(FindLibtorrentRasterbar REQUIRED)
find_package(OpenSSL REQUIRED)

message(STATUS "CMAKE_BUILD_TYPE:${CMAKE_BUILD_TYPE}")
#file(GLOB helloworld_SRC
#    "*.h"
#    "*.cpp"
#)
if(APPLE)
	include_directories(
    	"${CMAKE_CURRENT_SOURCE_DIR}/lib/include ${IOKit}"
	)
	else()
	include_directories(
			"${CMAKE_CURRENT_SOURCE_DIR}/lib/include"
	)
endif()
find_package(TBB CONFIG REQUIRED)

file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp src/*.hpp src/*.h src/*.xpm)
file(GLOB IMAGES_SOURCE ${CMAKE_CURRENT_SOURCE_DIR} images/*.jpg images/*.png images/*.bmp images/*.gif)
#FOREACH(LETTER ${SRCS})
#    string(FIND ${LETTER} "cmake-" SEARCH_POS)
#    if(SEARCH_POS EQUAL -1)
#        list(APPEND FINAL_RES ${LETTER})
#    endif()
#ENDFOREACH()
if(MSVC)
#	SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
#		${PROJECT_SOURCE_DIR}/bin/windows/i686/lib CACHE
#		PATH ${PROJECT_BINARY_DIR} FORCE)
#	SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY
#		${PROJECT_SOURCE_DIR}/bin/windows/i686/dll CACHE
#		PATH ${PROJECT_BINARY_DIR} FORCE)
	#ADD_CUSTOM_COMMAND( TARGET ${PROJECT_NAME} POST_BUILD
	#	COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/bin/windows/i686/dll/*.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>"
	#	COMMENT "copying dlls ��"
	#)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		file(GLOB dll_SRC
			"bin/windows/x86_64/dll/*.dll"
			)
		file(GLOB dll_LIB
			"bin/windows/x86_64/lib/*.lib"
			)
	else()
		file(GLOB dll_SRC
			"bin/windows/i686/dll/*.dll"
			)
		file(GLOB dll_LIB
			"bin/windows/i686/lib/*.lib"
			)
	endif()
	
	add_custom_target(CopyDLLs
		COMMAND ${CMAKE_COMMAND} -E copy ${dll_SRC} "${CMAKE_BINARY_DIR}"
	)
    add_executable(${PROJECT_NAME} WIN32 ${SRCS} "icon.rc" "sample.ico")
else(MSVC)
    add_executable(${PROJECT_NAME} ${SRCS})
endif()
add_custom_target(CopyImages
	COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/images"
	COMMAND ${CMAKE_COMMAND} -E copy ${IMAGES_SOURCE} "${CMAKE_BINARY_DIR}/images"
)
#file(GLOB mo_SRC
#		"trans/*.mo"
#)
#add_custom_target(CopyMos
#	COMMAND ${CMAKE_COMMAND} -E copy ${mo_SRC} "${CMAKE_BINARY_DIR}"
#)
#add_dependencies(${PROJECT_NAME} CopyMos)
add_dependencies(${PROJECT_NAME} CopyImages)
if(MSVC)
	add_dependencies(${PROJECT_NAME} CopyDLLs)
    target_link_libraries(${PROJECT_NAME} PRIVATE TBB::tbb ${wxWidgets_LIBRARIES} ${Boost_LIBRARIES} ${dll_LIB} cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_boost_internal cpprestsdk::cpprestsdk_openssl_internal OpenSSL::SSL OpenSSL::Crypto)
else()
    target_link_libraries(${PROJECT_NAME} ${IOKit} TBB::tbb ${wxWidgets_LIBRARIES} ${Boost_LIBRARIES} "/usr/local/opt/mpv/lib/libmpv.dylib" cpprestsdk::cpprest cpprestsdk::cpprestsdk_zlib_internal cpprestsdk::cpprestsdk_boost_internal cpprestsdk::cpprestsdk_openssl_internal OpenSSL::SSL OpenSSL::Crypto)
endif()