cmake_minimum_required(VERSION 3.12)

FILE(GLOB SOURCE_FILES *.h *.hpp *.cpp *.inc)
add_library(D3DRHI ${SOURCE_FILES})

target_link_libraries(D3DRHI 
	Core)