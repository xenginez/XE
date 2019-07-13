cmake_minimum_required(VERSION 3.12)

add_definitions(-DCOMPONENTS_EXPORT)

FILE(GLOB SOURCE_FILES *.h *.hpp *.cpp *.inc)
add_library(Components ${SOURCE_FILES})
