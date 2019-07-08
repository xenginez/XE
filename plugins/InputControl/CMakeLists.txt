cmake_minimum_required(VERSION 3.12)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/../../target/${XE_PLATFORM_PATH}/debug/bin/plugin/InputControl)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/../../target/${XE_PLATFORM_PATH}/debug/bin/plugin/InputControl)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/../../target/${XE_PLATFORM_PATH}/release/bin/plugin/InputControl)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/../../target/${XE_PLATFORM_PATH}/release/bin/plugin/InputControl)

FILE(GLOB SOURCE_FILES *.h *.hpp *.cpp *.mm *.inc)
add_library(InputControl ${SOURCE_FILES})

target_link_libraries(InputControl 
	Core
	)

add_custom_command(TARGET InputControl
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/plugin.xml "${CMAKE_SOURCE_DIR}/target/${XE_PLATFORM_PATH}/${XE_CONFIG}/bin/plugin/InputControl"
			)
