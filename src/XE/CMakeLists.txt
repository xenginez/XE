cmake_minimum_required(VERSION 3.12)

add_executable(XE main.cpp)

FILE(GLOB LIBRARY_FILES ${CMAKE_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_CONFIG}/*.*)

foreach(LIBRARY_FILE ${LIBRARY_FILES})
	message("${LIBRARY_FILE}")
	add_custom_command(TARGET XE
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_FILE} "${CMAKE_SOURCE_DIR}/target/${XE_PLATFORM_PATH}/${XE_CONFIG}/bin"
				)
endforeach(LIBRARY_FILE)
