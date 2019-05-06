cmake_minimum_required(VERSION 3.13)

add_definitions(-DGRAPHICS_EXPORT)

aux_source_directory(./ SOURCE_FILES)
add_library(Graphics ${SOURCE_FILES})


if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
	target_link_libraries(Graphics
			bgfx-shared-lib${BGFX_SUFFIX}
			)
endif ()