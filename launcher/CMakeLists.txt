cmake_minimum_required(VERSION 3.13)

project(Launcher)
set(CMAKE_CXX_STANDARD 17)
add_executable(Launcher ${XE_PLATFORM}/main.cpp)
target_link_libraries(Launcher XE)