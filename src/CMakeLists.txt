cmake_minimum_required(VERSION 3.13)

FILE(GLOB_RECURSE SOURCE_FILES *.*)
add_library(XE SHARED ${SOURCE_FILES})

target_compile_definitions(XE PRIVATE -DXE_EXPORT)

target_link_libraries(XE
		tbb${XE_TBB_POSTFIX}
		tbbmalloc${XE_TBB_POSTFIX}
		tbbmalloc_proxy${XE_TBB_POSTFIX}
		OpenAL32
		DebugUtils
		DetourCrowd
		Recast
		Detour
		DetourTileCache
		sqlite3
		ik
		astc-codec
		astc
		bgfx
		bimg
		bx
		edtaa3
		etc1
		etc2
		iqa
		nvtt
		pvrtc
		squish
		PhysX${XE_PHYSX_POSTFIX}
		PhysXCharacterKinematic_static_64
		PhysXCommon${XE_PHYSX_POSTFIX}
		PhysXCooking${XE_PHYSX_POSTFIX}
		PhysXExtensions_static_64
		PhysXFoundation${XE_PHYSX_POSTFIX}
		PhysXPvdSDK_static_64
		PhysXVehicle_static_64
		fmod${XE_FMOD_POSTFIX}
		fmodstudio${XE_FMOD_POSTFIX}
		)

FILE(GLOB LIBRARY_FILES ../depend/bin/${XE_PLATFORM_PATH}/${XE_CONFIG}/*.*)
foreach (LIBRARY_FILE ${LIBRARY_FILES})
	add_custom_command(TARGET XE
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${LIBRARY_FILE} "$ENV{XE_PATH}/${XE_CONFIG}/bin"
			)
endforeach (LIBRARY_FILE)


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
mkdir.bat
Navigation
Physics
Reflect
Render
Scene
Utils)
foreach(INC_DIR ${INC_DIRS})

	FILE(GLOB INC_FILES ${INC_DIR}/*.h ${INC_DIR}/*.hpp ${INC_DIR}/*.inc)
	foreach (INC_FILE ${INC_FILES})
		add_custom_command(TARGET XE
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy ${INC_FILE} "$ENV{XE_PATH}/include/${INC_DIR}"
				)
	endforeach (INC_FILE)

endforeach (INC_DIR)
