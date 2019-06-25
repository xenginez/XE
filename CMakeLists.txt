cmake_minimum_required(VERSION 3.13)

project(XE)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(XE_PLATFORM_PATH linux)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(XE_PLATFORM_PATH win)
elseif (CMAKE_SYSTEM_NAME MATCHES "IOS")
	set(XE_PLATFORM_PATH ios)
elseif (CMAKE_SYSTEM_NAME MATCHES "Android")
	set(XE_PLATFORM_PATH android)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
	set(XE_PLATFORM_PATH mac)
else ()
	message(FATAL_ERROR ${CMAKE_SYSTEM_NAME}" Other")
endif ()

if (CMAKE_BUILD_TYPE MATCHES "Debug")
	set(XE_CONFIG debug)
	set(XE_TBB_POSTFIX _debug)
else()
	set(XE_CONFIG release)
	set(XE_TBB_POSTFIX)
endif()



set(BUILD_SHARED_LIBS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/target/${XE_PLATFORM_PATH}/debug/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/target/${XE_PLATFORM_PATH}/debug/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/target/${XE_PLATFORM_PATH}/release/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/target/${XE_PLATFORM_PATH}/release/bin)

include_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/depend/include
)

if (XE_PLATFORM_PATH MATCHES "mac")
	include_directories(/usr/local/include)
endif ()

link_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_CONFIG}
		${CMAKE_CURRENT_SOURCE_DIR}/depend/lib/${XE_PLATFORM_PATH}/${XE_CONFIG}
)

add_subdirectory(src)

add_dependencies(Memory Base)
add_dependencies(Reflect Base Memory)
add_dependencies(Utils Base Memory Reflect)
add_dependencies(Math Base Memory Reflect Utils)
add_dependencies(RHI Base Memory Reflect Utils Math)
add_dependencies(Interface Base Memory Reflect Utils Math RHI)
add_dependencies(Audio Base Memory Reflect Utils Math RHI Interface)
add_dependencies(Physics Base Memory Reflect Utils Math RHI Interface)
add_dependencies(Graphics Base Memory Reflect Utils Math RHI Interface)
add_dependencies(Animation Base Memory Reflect Utils Math RHI Interface)
add_dependencies(Navigation Base Memory Reflect Utils Math RHI Interface)
add_dependencies(GUI Base Memory Reflect Utils Math RHI Interface Graphics)
add_dependencies(World Base Memory Reflect Utils Math RHI Interface)
add_dependencies(AI Base Memory Reflect Utils Math RHI Interface World)
add_dependencies(Behavior Base Memory Reflect Utils Math RHI Interface Audio Physics Animation Navigation AI World)
add_dependencies(Render Base Memory Reflect Utils Math RHI Interface Graphics World GUI)
add_dependencies(Core Base Memory Reflect Utils Math RHI Interface Audio Physics Graphics Animation Navigation GUI AI World Behavior Render)
add_dependencies(XE Base Memory Reflect Utils Math RHI Interface Audio Physics Graphics Animation Navigation GUI AI World Behavior Render Core)

target_link_libraries(Base

		tbb${XE_TBB_POSTFIX}
		tbbmalloc${XE_TBB_POSTFIX}
		tbbmalloc_proxy${XE_TBB_POSTFIX}
		)

target_link_libraries(Memory
		Base)

target_link_libraries(Reflect
		Memory
		
		pugixml
		sqlite3
		libZipper-static
		)

target_link_libraries(Utils
		Reflect)

target_link_libraries(Math
		Utils)

target_link_libraries(RHI
		Math)

target_link_libraries(Interface
		RHI)

target_link_libraries(Audio
		Interface

		OpenAL32
		)

target_link_libraries(Physics
		Interface

		Bullet2FileLoader
		BulletInverseDynamicsUtils
		Bullet3Collision
		BulletRobotics
		Bullet3Common
		BulletSoftBody
		Bullet3Dynamics
		BulletWorldImporter
		Bullet3Geometry
		BulletXmlWorldImporter
		Bullet3OpenCL_clew
		ConvexDecomposition
		BulletCollision
		GIMPACTUtils
		BulletDynamics
		HACD
		BulletFileLoader
		LinearMath
		BulletInverseDynamics
		)

target_link_libraries(Graphics
		Interface)

target_link_libraries(Animation
		Interface)

target_link_libraries(Navigation
		Interface

		DebugUtils
		DetourCrowd
		Recast
		Detour
		DetourTileCache
		)

target_link_libraries(GUI
		Graphics)

target_link_libraries(World
		Interface)

target_link_libraries(AI
		World)

target_link_libraries(Behavior
		Audio Physics Animation Navigation AI)

target_link_libraries(Render
		World GUI)

target_link_libraries(Core
		Behavior Render
		)

target_link_libraries(XE
		Core)
