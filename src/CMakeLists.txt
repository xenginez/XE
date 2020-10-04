cmake_minimum_required(VERSION 3.13)

FILE(GLOB_RECURSE SOURCE_FILES *.*)
add_library(XE ${XE_LIB_TYPE} ${SOURCE_FILES})

target_compile_definitions(XE PRIVATE -DXE_EXPORT)

target_link_libraries(XE
		DebugUtils
		Detour
		DetourCrowd
		DetourTileCache
		ik
		PhysXCharacterKinematic_static_64
		PhysXCommon_64
		PhysXCooking_64
		PhysXExtensions_static_64
		PhysXFoundation_64
		PhysXPvdSDK_static_64
		PhysXTask_static_64
		PhysXVehicle_static_64
		PhysX_64
		Recast
		tbb${XE_TBB_POSTFIX}
		tbbmalloc${XE_TBB_POSTFIX}
		tbbmalloc_proxy${XE_TBB_POSTFIX}
		zlib${XE_ZLIB_POSTFIX}
		OpenAL32
		sqlite3
		)

set(INC_DIRS 
AI
Animation
Audio
Base
Component
Core
GC
Graphics
GUI
Interface
Math
Navigation
Physics
Reflect
Render
Scene
Utils)
foreach(INC_DIR ${INC_DIRS})

	add_custom_command(TARGET XE
					POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_SOURCE_DIR}/../target/include/${INC_DIR}"
					COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/../target/include/${INC_DIR}"
					)

	FILE(GLOB INC_FILES ${INC_DIR}/*.h ${INC_DIR}/*.hpp ${INC_DIR}/*.inc)
	foreach (INC_FILE ${INC_FILES})
		add_custom_command(TARGET XE
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy ${INC_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/../target/include/${INC_DIR}"
				)
	endforeach (INC_FILE)

	message("copy include: " ${INC_DIR})

endforeach (INC_DIR)

FILE(GLOB LIBRARY_FILES ../depend/bin/${XE_PLATFORM}/${XE_CONFIG}/*.*)
foreach (LIBRARY_FILE ${LIBRARY_FILES})
	add_custom_command(TARGET XE
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_FILE} "${CMAKE_CURRENT_SOURCE_DIR}/../target/${XE_CONFIG}/bin/"
			)
endforeach (LIBRARY_FILE)
