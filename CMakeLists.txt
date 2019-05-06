cmake_minimum_required(VERSION 3.13)

project(XE)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(XE_PLATFORM_PATH linux)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(XE_PLATFORM_PATH win)
	if (CMAKE_BUILD_TYPE MATCHES "Debug")
		set(XE_BUILD_TYPE debug)
		set(TBB_SUFFIX _debug)
		set(BGFX_SUFFIX Debug)
		set(BULLET_SUFFIX _Debug)
	else ()
		set(XE_BUILD_TYPE release)
		set(TBB_SUFFIX)
		set(BGFX_SUFFIX Release)
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
		set(BGFX_SUFFIX Debug)
		set(BULLET_SUFFIX)
	else ()
		set(XE_BUILD_TYPE release)
		set(TBB_SUFFIX)
		set(BGFX_SUFFIX Release)
		set(BULLET_SUFFIX)
	endif ()
else ()
	set(XE_PLATFORM_PATH linux)
	message(FATAL_ERROR ${CMAKE_SYSTEM_NAME}" Other")
endif ()

set(BUILD_SHARED_LIBS ON)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/target/bin/${XE_BUILD_TYPE})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/target/bin/${XE_BUILD_TYPE})

include_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/target/include
)

link_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/target/bin/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}
		${CMAKE_CURRENT_SOURCE_DIR}/target/lib/${XE_PLATFORM_PATH}/${XE_BUILD_TYPE}
)

add_subdirectory(src)


set(XE_3RDPARTY_LIBRARIES
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

		DebugUtils
		DetourCrowd
		Recast
		Detour
		DetourTileCache

		OpenAL32
		pugixml
		sqlite3
		tbb${TBB_SUFFIX}
		tbbmalloc${TBB_SUFFIX}
		tbbmalloc_proxy${TBB_SUFFIX}
		bx${BGFX_SUFFIX}
		bgfx${BGFX_SUFFIX}
		bimg${BGFX_SUFFIX}
		bimg_decode${BGFX_SUFFIX}
		libZipper-static
		)

add_dependencies(Memory Base)
add_dependencies(Reflect Base Memory)
add_dependencies(Utils Base Memory Reflect)
add_dependencies(Math Base Memory Reflect Utils)
add_dependencies(Interface Base Memory Reflect Utils Math)
add_dependencies(Audio Base Memory Reflect Utils Math Interface)
add_dependencies(Physics Base Memory Reflect Utils Math Interface)
add_dependencies(Graphics Base Memory Reflect Utils Math Interface)
add_dependencies(Animation Base Memory Reflect Utils Math Interface)
add_dependencies(Navigation Base Memory Reflect Utils Math Interface)
add_dependencies(GUI Base Memory Reflect Utils Math Interface Graphics)
add_dependencies(AI Base Memory Reflect Utils Math Interface)
add_dependencies(World Base Memory Reflect Utils Math Interface)
add_dependencies(Behavior Base Memory Reflect Utils Math Interface Audio Physics Animation Navigation AI World)
add_dependencies(Render Base Memory Reflect Utils Math Interface Graphics World)
add_dependencies(Core Base Memory Reflect Utils Math Interface Audio Physics Graphics Animation Navigation GUI AI World Behavior Render)
add_dependencies(XE Base Memory Reflect Utils Math Interface Audio Physics Graphics Animation Navigation GUI AI World Behavior Render Core)

target_link_libraries(Base
		${XE_3RDPARTY_LIBRARIES})
target_link_libraries(Memory
		Base ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(Reflect
		Base Memory ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(Utils
		Base Memory Reflect ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(Math
		Base Memory Reflect Utils ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(Interface
		Base Memory Reflect Utils Math ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(Audio
		Base Memory Reflect Utils Math Interface ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(Physics
		Base Memory Reflect Utils Math Interface ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(Graphics
		Base Memory Reflect Utils Math Interface ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(Animation
		Base Memory Reflect Utils Math Interface ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(Navigation
		Base Memory Reflect Utils Math Interface ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(GUI
		Base Memory Reflect Utils Math Interface Graphics ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(AI
		Base Memory Reflect Utils Math Interface ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(World
		Base Memory Reflect Utils Math Interface ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(Behavior
		Base Memory Reflect Utils Math Interface Audio Physics Animation Navigation AI World ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(Render
		Base Memory Reflect Utils Math Interface Graphics World ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(Core
		Base Memory Reflect Utils Math Interface Audio Physics Graphics Animation Navigation GUI AI World Behavior Render ${XE_3RDPARTY_LIBRARIES})
target_link_libraries(XE
		Base Memory Reflect Utils Math Interface Audio Physics Graphics Animation Navigation GUI AI World Behavior Render Core ${XE_3RDPARTY_LIBRARIES})
