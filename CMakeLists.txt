cmake_minimum_required(VERSION 3.12)

project(XE)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release")

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(XE_PLATFORM_PATH linux)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(XE_PLATFORM_PATH win)
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
		set(XE_BUILD_TYPE debug)
		set(TBB_SUFFIX _debug)
		set(BULLET_SUFFIX _Debug)
	else ()
		set(XE_BUILD_TYPE release)
		set(TBB_SUFFIX)
		set(BULLET_SUFFIX)
	endif ()
elseif (CMAKE_SYSTEM_NAME MATCHES "IOS")
	set(XE_PLATFORM_PATH ios)
elseif (CMAKE_SYSTEM_NAME MATCHES "Android")
	set(XE_PLATFORM_PATH android)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
	set(XE_PLATFORM_PATH mac)
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
		set(XE_BUILD_TYPE debug)
		set(TBB_SUFFIX _debug)
		set(BULLET_SUFFIX)
	else ()
		set(XE_BUILD_TYPE release)
		set(TBB_SUFFIX)
		set(BULLET_SUFFIX)
	endif ()
else ()
	set(XE_PLATFORM_PATH linux)
	message(FATAL_ERROR ${CMAKE_SYSTEM_NAME}" Other")
endif ()

set(BUILD_SHARED_LIBS ON)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/target/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/target/bin)

include_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/depend/include
)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
	include_directories(/usr/local/include)
endif ()

link_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/depend/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}
		${CMAKE_CURRENT_SOURCE_DIR}/depend/lib/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}
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
add_dependencies(AI Base Memory Reflect Utils Math RHI Interface)
add_dependencies(World Base Memory Reflect Utils Math RHI Interface)
add_dependencies(Behavior Base Memory Reflect Utils Math RHI Interface Audio Physics Animation Navigation AI World)
add_dependencies(Render Base Memory Reflect Utils Math RHI Interface Graphics World GUI)
add_dependencies(Core Base Memory Reflect Utils Math RHI Interface Audio Physics Graphics Animation Navigation GUI AI World Behavior Render)
add_dependencies(XE Base Memory Reflect Utils Math RHI Interface Audio Physics Graphics Animation Navigation GUI AI World Behavior Render Core)

target_link_libraries(Base

		tbb${TBB_SUFFIX}
		tbbmalloc${TBB_SUFFIX}
		tbbmalloc_proxy${TBB_SUFFIX}
		)

target_link_libraries(Memory
		Base)

target_link_libraries(Reflect
		Memory

		Zipper-static
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

		Bullet2FileLoader${BULLET_SUFFIX}
		BulletInverseDynamicsUtils${BULLET_SUFFIX}
		Bullet3Collision${BULLET_SUFFIX}
		BulletRobotics${BULLET_SUFFIX}
		Bullet3Common${BULLET_SUFFIX}
		BulletSoftBody${BULLET_SUFFIX}
		Bullet3Dynamics${BULLET_SUFFIX}
		BulletWorldImporter${BULLET_SUFFIX}
		Bullet3Geometry${BULLET_SUFFIX}
		BulletXmlWorldImporter${BULLET_SUFFIX}
		Bullet3OpenCL_clew${BULLET_SUFFIX}
		ConvexDecomposition${BULLET_SUFFIX}
		BulletCollision${BULLET_SUFFIX}
		GIMPACTUtils${BULLET_SUFFIX}
		BulletDynamics${BULLET_SUFFIX}
		HACD${BULLET_SUFFIX}
		BulletFileLoader${BULLET_SUFFIX}
		LinearMath${BULLET_SUFFIX}
		BulletInverseDynamics${BULLET_SUFFIX}
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

target_link_libraries(AI
		Interface)

target_link_libraries(World
		Interface)

target_link_libraries(Behavior
		Audio Physics Animation Navigation AI World)

target_link_libraries(Render
		Graphics World GUI)

target_link_libraries(Core
		Behavior Render GUI

		pugixml
		sqlite3
		)

target_link_libraries(XE
		Core)
