cmake_minimum_required(VERSION 3.12)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/modules/PhysX)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG}/modules/PhysX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/modules/PhysX)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE}/modules/PhysX)

FILE(GLOB SOURCE_FILES *.*)
add_library(PhysX SHARED ${SOURCE_FILES})
target_compile_definitions(PhysX PRIVATE -DPHYSX_EXPORT)

target_link_libraries(PhysX 
	XE
	)