cmake_minimum_required(VERSION 3.12)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/../../target/${XE_PLATFORM_PATH}/debug/bin/module)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/../../target/${XE_PLATFORM_PATH}/debug/bin/module)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/../../target/${XE_PLATFORM_PATH}/release/bin/module)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/../../target/${XE_PLATFORM_PATH}/release/bin/module)

FILE(GLOB SOURCE_FILES *.h *.hpp *.cpp *.inc)
add_library(D3DRHI ${SOURCE_FILES})

target_link_libraries(D3DRHI 
	Core
	
	dxgi
	d3d12
	d3dcompiler)
