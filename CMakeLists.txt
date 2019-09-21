cmake_minimum_required(VERSION 3.13)

project(XE)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
 
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

if (CMAKE_BUILD_TYPE MATCHES "Debug")
	set(XE_CONFIG debug)
	set(XE_TBB_POSTFIX _debug)
else()
	set(XE_CONFIG release)
	set(XE_TBB_POSTFIX)
endif()

option (USE_MATH "whether to use a high-precision float type" OFF)
option (USE_SHARED_LIBS "whether to use a dynamic library" ON)


if(USE_MATH)
	add_definitions(-DXE_DOUBLE)
endif()

if(USE_SHARED_LIBS)
	set(BUILD_SHARED_LIBS ON)
else()
	set(BUILD_SHARED_LIBS OFF)
endif()


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/target/${XE_PLATFORM_PATH}/debug/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/target/${XE_PLATFORM_PATH}/debug/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/target/${XE_PLATFORM_PATH}/release/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/target/${XE_PLATFORM_PATH}/release/bin)

include_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/depend/include
)

if (XE_PLATFORM_PATH MATCHES "mac")
	include_directories(/usr/local/include)
endif ()

link_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_CONFIG}
		${CMAKE_CURRENT_SOURCE_DIR}/depend/lib/${XE_PLATFORM_PATH}/${XE_CONFIG}
)



add_definitions(-DXE_EXPORT)

FILE(GLOB_RECURSE XE_SRC_FILES src/*.h src/*.hpp src/*.cpp src/*.inc)
add_library(XE ${XE_SRC_FILES})

if (XE_PLATFORM_PATH MATCHES "mac")
	target_link_libraries(XE 
	tbb${XE_TBB_POSTFIX}
	tbbmalloc${XE_TBB_POSTFIX}
	tbbmalloc_proxy${XE_TBB_POSTFIX}
	OpenAL32
	DebugUtils
	DetourCrowd
	Recast
	Detour
	DetourTileCache
	sqlite3
	boost_filesystem
	ik
	)
else()
	target_link_libraries(XE 
	tbb${XE_TBB_POSTFIX}
	tbbmalloc${XE_TBB_POSTFIX}
	tbbmalloc_proxy${XE_TBB_POSTFIX}
	OpenAL32
	DebugUtils
	DetourCrowd
	Recast
	Detour
	DetourTileCache
	sqlite3
	ik
	)
endif ()


FILE(GLOB LIBRARY_FILES depend/bin/${XE_PLATFORM_PATH}/${XE_CONFIG}/*.*)
foreach(LIBRARY_FILE ${LIBRARY_FILES})
	message("${LIBRARY_FILE}")
	add_custom_command(TARGET XE
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_FILE} "${CMAKE_SOURCE_DIR}/target/${XE_PLATFORM_PATH}/${XE_CONFIG}/bin"
				)
endforeach(LIBRARY_FILE)
