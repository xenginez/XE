cmake_minimum_required(VERSION 3.12)

add_definitions(-DINTERFACE_EXPORT)

aux_source_directory(./ SOURCE_FILES)
add_library(Interface ${SOURCE_FILES})
