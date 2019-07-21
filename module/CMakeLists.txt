cmake_minimum_required(VERSION 3.12)

project(Module)

set(CMAKE_CXX_STANDARD 17)

option (USE_MATH "whether to use a high-precision float type" OFF)
option (USE_SHARED_LIBS "whether to use a dynamic library" ON)

if( USE_MATH)
	add_definitions(-DXE_DOUBLE)
endif()

if( USE_SHARED_LIBS)
	set(BUILD_SHARED_LIBS ON)
else()
	set(BUILD_SHARED_LIBS OFF)
endif()

if (CMAKE_BUILD_TYPE MATCHES "Debug")
	set(XE_CONFIG debug)
else()
	set(XE_CONFIG release)
endif()

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(XE_PLATFORM_PATH linux)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(XE_PLATFORM_PATH win)
elseif (CMAKE_SYSTEM_NAME MATCHES "IOS")
	set(XE_PLATFORM_PATH ios)
elseif (CMAKE_SYSTEM_NAME MATCHES "Android")
	set(XE_PLATFORM_PATH android)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
	set(XE_PLATFORM_PATH mac)
else ()
	message(FATAL_ERROR ${CMAKE_SYSTEM_NAME}" Other")
endif ()

include_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/../src
		${CMAKE_CURRENT_SOURCE_DIR}/../depend/include
)

link_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/../target/${XE_PLATFORM_PATH}/${XE_CONFIG}/bin
		${CMAKE_CURRENT_SOURCE_DIR}/../depend/bin/${XE_PLATFORM_PATH}/${XE_CONFIG}
		${CMAKE_CURRENT_SOURCE_DIR}/../depend/lib/${XE_PLATFORM_PATH}/${XE_CONFIG}
)


if (CMAKE_SYSTEM_NAME MATCHES "Linux")

elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
	add_subdirectory(D3DRHI)
elseif (CMAKE_SYSTEM_NAME MATCHES "IOS")

elseif (CMAKE_SYSTEM_NAME MATCHES "Android")

elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")

else ()
	message(FATAL_ERROR ${CMAKE_SYSTEM_NAME}" Other")
endif ()
