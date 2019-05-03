cmake_minimum_required(VERSION 3.13)

add_definitions(-DRENDER_EXPORT)

aux_source_directory(./ SOURCE_FILES)
add_library(Render ${SOURCE_FILES})
