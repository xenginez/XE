cmake_minimum_required(VERSION 3.13)

project(XE)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/target/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/target/bin)

include_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/target/include
)

link_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/target/bin
		${THIRDPARTY_LIBRARY_PATH}
)

add_subdirectory(src)


set(XE_3RDPARTY_LIBRARIES
		Bullet2FileLoader
		Bullet3Collision
		Bullet3Common
		Bullet3Dynamics
		Bullet3Geometry
		Bullet3OpenCL_clew
		BulletCollision
		BulletDynamics
		BulletInverseDynamics
		BulletSoftBody
		DebugUtils
		Detour
		DetourCrowd
		DetourTileCache
		LinearMath
		Recast
		openal
		Zipper
		pugixml
		sqlite3
		tbb
		tbbmalloc
		tbbmalloc_proxy
		bgfx-shared-libRelease
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
