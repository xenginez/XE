cmake_minimum_required(VERSION 3.13)

project(XE)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif ()

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(XE_PLATFORM linux)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(XE_PLATFORM win)
elseif (CMAKE_SYSTEM_NAME MATCHES "IOS")
	set(XE_PLATFORM ios)
elseif (CMAKE_SYSTEM_NAME MATCHES "Android")
	set(XE_PLATFORM android)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
	set(XE_PLATFORM mac)
else ()
	message(FATAL_ERROR ${CMAKE_SYSTEM_NAME}" Other")
endif ()

if (CMAKE_BUILD_TYPE MATCHES "Debug")
	set(XE_CONFIG debug)
	set(XE_TBB_POSTFIX _debug)
	set(XE_FMOD_POSTFIX L)
	set(XE_POSTFIX d)
else ()
	set(XE_CONFIG release)
	set(XE_TBB_POSTFIX)
	set(XE_FMOD_POSTFIX)
	set(XE_POSTFIX)
endif ()

if(WIN32)
	set(XE_PHYSX_POSTFIX _64)
else()
	set(XE_PHYSX_POSTFIX _static_64)
endif()

option(USE_MATH "whether to use a high-precision float type" OFF)


if (USE_MATH)
	add_definitions(-DXE_DOUBLE)
endif ()

if (USE_SHARED_LIBS)
	set(BUILD_SHARED_LIBS ON)
else ()
	set(BUILD_SHARED_LIBS OFF)
endif ()


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/target/debug/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/target/debug/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/target/release/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/target/release/bin)

include_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/depend/include
)

link_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/depend/bin/${XE_PLATFORM}/${XE_CONFIG}
		${CMAKE_CURRENT_SOURCE_DIR}/depend/lib/${XE_PLATFORM}/${XE_CONFIG}
		${CMAKE_CURRENT_SOURCE_DIR}/target/${XE_CONFIG}/bin
)


add_subdirectory(src)
add_subdirectory(modules)
add_subdirectory(launcher)