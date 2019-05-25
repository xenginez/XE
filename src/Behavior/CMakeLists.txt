cmake_minimum_required(VERSION 3.12)

add_definitions(-DBEHAVIOR_EXPORT)

aux_source_directory(./ SOURCE_FILES)
add_library(Behavior ${SOURCE_FILES})
