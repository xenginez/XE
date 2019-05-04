cmake_minimum_required(VERSION 3.13)

add_definitions(-DBASE_EXPORT)

aux_source_directory(./ SOURCE_FILES)
add_library(Base ${SOURCE_FILES})

if (APPLE)
	target_link_libraries(Base
			boost_filesystem
			)
endif (APPLE)