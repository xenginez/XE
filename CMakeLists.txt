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

option (USE_MATH "whether to use a high-precision float type" OFF)
option (USE_SHARED_LIBS "whether to use a dynamic library" ON)


if( USE_MATH)
	add_definitions(-DXE_DOUBLE)
endif()

if( USE_SHARED_LIBS)
	set(BUILD_SHARED_LIBS ON)
else()
	set(BUILD_SHARED_LIBS OFF)
endif()


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

add_dependencies(GC			Base)
add_dependencies(Reflect	Base GC)
add_dependencies(Utils		Base GC Reflect)
add_dependencies(Math		Base GC Reflect Utils)
add_dependencies(RHI		Base GC Reflect Utils Math)
add_dependencies(PHI		Base GC Reflect Utils Math)
add_dependencies(Audio		Base GC Reflect Utils Math)
add_dependencies(World		Base GC Reflect Utils Math)
add_dependencies(Physics	Base GC Reflect Utils Math PHI)
add_dependencies(AI			Base GC Reflect Utils Math RHI)
add_dependencies(Graphics	Base GC Reflect Utils Math RHI)
add_dependencies(Navigation Base GC Reflect Utils Math RHI)
add_dependencies(Render		Base GC Reflect Utils Math RHI Graphics)
add_dependencies(GUI		Base GC Reflect Utils Math RHI Graphics Render)
add_dependencies(Animation	Base GC Reflect Utils Math RHI Graphics Render)
add_dependencies(Interface	Base GC Reflect Utils Math RHI Audio World AI Physics Graphics Navigation Render GUI Animation)
add_dependencies(Components	Base GC Reflect Utils Math RHI Audio World AI Physics Graphics Navigation Render GUI Animation Interface)
add_dependencies(Core		Base GC Reflect Utils Math RHI Audio World AI Physics Graphics Navigation Render GUI Animation Interface Components)
add_dependencies(XE			Base GC Reflect Utils Math RHI Audio World AI Physics Graphics Navigation Render GUI Animation Interface Components Core)

target_link_libraries(Base

		tbb${XE_TBB_POSTFIX}
		tbbmalloc${XE_TBB_POSTFIX}
		tbbmalloc_proxy${XE_TBB_POSTFIX}
		)

target_link_libraries(GC
		Base)

target_link_libraries(Reflect
		GC
		)

target_link_libraries(Utils
		Reflect)

target_link_libraries(Math
		Utils)
		
target_link_libraries(PHI
		Math)

target_link_libraries(RHI
		Math)

target_link_libraries(Audio
		Math

		OpenAL32
		)

target_link_libraries(World
		Math)

target_link_libraries(Physics
		PHI
		)

target_link_libraries(AI
		RHI)

target_link_libraries(Graphics
		RHI)

target_link_libraries(Navigation
		RHI

		DebugUtils
		DetourCrowd
		Recast
		Detour
		DetourTileCache
		)

target_link_libraries(Render
		Graphics)

target_link_libraries(GUI
		Render)

target_link_libraries(Animation
		Render)

target_link_libraries(Interface
		 Audio
		 World
		 AI
		 Physics
		 Navigation
		 GUI
		 Animation)

target_link_libraries(Components
		Interface)

target_link_libraries(Core
		Components

		sqlite3
		)

target_link_libraries(XE
		Core)
