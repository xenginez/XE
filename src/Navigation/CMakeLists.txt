cmake_minimum_required(VERSION 3.12)

add_definitions(-DNAVIGATION_EXPORT)

FILE(GLOB SOURCE_FILES *.h *.hpp *.cpp *.inc)
add_library(Navigation ${SOURCE_FILES})
