cmake_minimum_required(VERSION 3.12)

add_definitions(-DBASE_EXPORT -D__TBB_NO_IMPLICIT_LINKAGE -D__TBBMALLOC_NO_IMPLICIT_LINKAGE)

aux_source_directory(./ SOURCE_FILES)
add_library(Base ${SOURCE_FILES})

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
	target_link_libraries(Base
			boost_filesystem
			)
endif ()