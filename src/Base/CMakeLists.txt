cmake_minimum_required(VERSION 3.12)

add_definitions(-DBASE_EXPORT)

FILE(GLOB SOURCE_FILES *.h *.hpp *.cpp *.inc)
add_library(Base ${SOURCE_FILES})

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
	target_link_libraries(Base
			boost_filesystem
			)
endif ()