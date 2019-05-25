cmake_minimum_required(VERSION 3.12)

add_definitions(-DPHYSICS_EXPORT)

aux_source_directory(./ SOURCE_FILES)
add_library(Physics ${SOURCE_FILES})
