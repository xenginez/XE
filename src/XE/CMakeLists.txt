cmake_minimum_required(VERSION 3.13)

add_executable(XE main.cpp)



if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
	else ()
	endif ()
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
	else ()
	endif ()
elseif (CMAKE_SYSTEM_NAME MATCHES "IOS")
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
	else ()
	endif ()
elseif (CMAKE_SYSTEM_NAME MATCHES "Android")
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
	else ()
	endif ()
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
		add_custom_command(TARGET XE
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libopenal.1.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libOpenAL32.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libopenal.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libbgfx-shared-libDebug.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libtbb_debug.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libboost_filesystem.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libtbbmalloc_debug.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libopenal.1.19.1.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libtbbmalloc_proxy_debug.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				)
	else ()
		add_custom_command(TARGET XE
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libAI.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libopenal.1.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libOpenAL32.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libopenal.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libbgfx-shared-libRelease.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libtbb.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libboost_filesystem.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libtbbmalloc.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libopenal.1.19.1.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}/libtbbmalloc_proxy.dylib" "${CMAKE_SOURCE_DIR}/target/bin"
				)
	endif ()
endif ()
