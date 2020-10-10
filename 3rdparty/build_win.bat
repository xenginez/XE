set MSBUILD=()

if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" (
    set MSBUILD="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
    goto :FOUND_MSBUILD
)
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvars64.bat" (
    set MSBUILD="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvars64.bat"
    goto :FOUND_MSBUILD
)
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvars64.bat" (
	set MSBUILD="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvars64.bat"
    goto :FOUND_MSBUILD
)

if %MSBUILD%==() (
    echo "I couldn't find MSBuild on your PC. Make sure it's installed somewhere, and if it's not in the above if statements (in build.bat), add it."
    goto :EXIT
) 

:FOUND_MSBUILD
call %%MSBUILD%%
set RD3_PATH=%cd%



echo "update git submodule"
git submodule update --init --recursive

:BUILD_OZZ
cd %RD3_PATH%
echo "build ozz-animation debug"
mkdir .\ozz-animation\build
cd .\ozz-animation\build
cmake -Dozz_build_msvc_rt_dll=ON -Dozz_build_fbx=OFF -Dozz_build_gltf=OFF -Dozz_build_howtos=OFF -Dozz_build_postfix=OFF -Dozz_build_samples=OFF -Dozz_build_simd_ref=ON -Dozz_build_tests=OFF -Dozz_build_tools=OFF -Dozz_run_tests_headless=OFF -DCMAKE_INSTALL_PREFIX=.\install\ .. -G "Visual Studio 16 2019" 
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Debug ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy ozz-animation debug file to depend"
xcopy %cd%\install\lib\ozz_animation.lib %RD3_PATH%\..\depend\lib\win\debug\ /y
xcopy %cd%\install\lib\ozz_base.lib %RD3_PATH%\..\depend\lib\win\debug\ /y
xcopy %cd%\install\lib\ozz_geometry.lib %RD3_PATH%\..\depend\lib\win\debug\ /y
xcopy %cd%\install\lib\ozz_options.lib %RD3_PATH%\..\depend\lib\win\debug\ /y
del %cd%\install\ /f /s /q

echo "build ozz-animation release"
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy ozz-animation release file to depend"
xcopy %cd%\install\lib\ozz_animation.lib %RD3_PATH%\..\depend\lib\win\release\ /y
xcopy %cd%\install\lib\ozz_base.lib %RD3_PATH%\..\depend\lib\win\release\ /y
xcopy %cd%\install\lib\ozz_geometry.lib %RD3_PATH%\..\depend\lib\win\release\ /y
xcopy %cd%\install\lib\ozz_options.lib %RD3_PATH%\..\depend\lib\win\release\ /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /s /e /y
del %cd%\install\ /f /s /q


:BUILD_TBB
echo "build tbb debug"
cd %RD3_PATH%
mkdir .\tbb\build
cd .\tbb\build
cmake -DTBB_BUILD_STATIC=OFF -DTBB_BUILD_TESTS=OFF -DCMAKE_DEBUG_POSTFIX=_debug -DCMAKE_INSTALL_PREFIX=.\install\ .. -G "Visual Studio 16 2019" 
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Debug ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy tbb debug file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
del %cd%\install\ /f /s /q

echo "build tbb release"
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy tbb release file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /s /e /y
del %cd%\install\ /f /s /q


:BUILD_RECASTNAVIGATION
echo "build recastnavigation debug"
cd %RD3_PATH%
mkdir .\recastnavigation\build
cd .\recastnavigation\build
cmake -DRECASTNAVIGATION_DEMO=OFF -DRECASTNAVIGATION_EXAMPLES=OFF -DRECASTNAVIGATION_TESTS=OFF -DCMAKE_INSTALL_PREFIX=.\install\ .. -G "Visual Studio 16 2019" 
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Debug ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy recastnavigation debug file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
del %cd%\install\ /f /s /q

echo "build recastnavigation release"
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy recastnavigation release file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\recastnavigation\ /s /e /y
del %cd%\install\ /f /s /q


:BUILD_ZLIB
echo "build zlib debug"
cd %RD3_PATH%
mkdir .\zlib\build
cd .\zlib\build
cmake -DCMAKE_INSTALL_PREFIX=.\install\ -DINSTALL_BIN_DIR=.\install\bin\ -DINSTALL_INC_DIR=.\install\include\zlib\ -DINSTALL_LIB_DIR=.\install\lib\ -DINSTALL_MAN_DIR=.\install\man\ -DINSTALL_PKGCONFIG_DIR=.\install\pkgconfig\ .. -G "Visual Studio 16 2019"
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Debug ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false
    
echo "copy zlib debug file to depend"
xcopy %cd%\install\lib\zlibd.lib %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
del %cd%\install\ /f /s /q

echo "build zlib release"
cd %RD3_PATH%
mkdir .\zlib\build
cd .\zlib\build
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false
echo "copy zlib release file to depend"
xcopy %cd%\install\lib\zlib.lib %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /s /e /y
del %cd%\install\ /f /s /q


:BUILD_PHYSX
echo "build phyxs debug"
cd %RD3_PATH%

(for /f "delims=" %%a in (%RD3_PATH%\PhysX\physx\source\foundation\include\PsAllocator.h) do (
set "str=%%a"
setlocal enabledelayedexpansion
set "str=!str:typeinfo.h=typeinfo!"
echo,!str!
endlocal
))>"setup.tmp"
move /y "%RD3_PATH%\setup.tmp" "%RD3_PATH%\PhysX\physx\source\foundation\include\PsAllocator.h"

(for /f "delims=" %%a in (%RD3_PATH%\PhysX\physx\buildtools\presets\public\vc16win64.xml) do (
set "str=%%a"
setlocal enabledelayedexpansion
set "str=!str:True=False!"
echo,!str!
endlocal
))>"setup.tmp"
move /y "%RD3_PATH%\setup.tmp" "%RD3_PATH%\PhysX\physx\buildtools\presets\public\vc16win64.xml"

call %cd%\PhysX\physx\generate_projects.bat vc16win64
msbuild.exe "%cd%\PhysX\physx\compiler\vc16win64\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Debug ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy phyxs debug file to depend"
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\debug\*.dll %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\debug\*.pdb %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\debug\*.lib %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
del %cd%\PhysX\physx\install\ /f /s /q

echo "build phyxs release"
cd %RD3_PATH%
msbuild.exe "%cd%\PhysX\physx\compiler\vc16win64\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy phyxs release file to depend"
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\*.dll %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\*.pdb %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\*.lib %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\include\*.* %RD3_PATH%\..\depend\include\PhysX\ /s /e /y
xcopy %cd%\PhysX\physx\install\vc15win64\PxShared\include\*.* %RD3_PATH%\..\depend\include\PhysX\ /s /e /y
del %cd%\PhysX\physx\install\ /f /s /q


:BUILD_OPENAL
echo "build openal debug"
cd %RD3_PATH%
mkdir .\openal-soft\build
cd .\openal-soft\build
cmake -DALSOFT_INSTALL_EXAMPLES=OFF -DALSOFT_INSTALL_UTILS=OFF -DALSOFT_UPDATE_BUILD_VERSION=OFF -DALSOFT_UTILS=OFF -DCMAKE_INSTALL_PREFIX=.\install\ .. -G "Visual Studio 16 2019"
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Debug ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy openal debug file to depend"
xcopy %cd%\install\lib\*.lib %RD3_PATH%\..\depend\lib\win\debug\ /e /y
xcopy %cd%\install\bin\*.dll %RD3_PATH%\..\depend\bin\win\debug\ /e /y
del %cd%\install\ /f /s /q

echo "build openal release"
cd %RD3_PATH%
mkdir .\openal-soft\build
cd .\openal-soft\build
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false
echo "copy openal release file to depend"
xcopy %cd%\install\lib\*.lib %RD3_PATH%\..\depend\lib\win\release\ /e /y
xcopy %cd%\install\bin\*.dll %RD3_PATH%\..\depend\bin\win\release\ /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /s /e /y
del %cd%\install\ /f /s /q


:BUILD_SQLITE3
echo "build sqlite3-cmake debug"
cd %RD3_PATH%

echo PROJECT(sqlite3) > %RD3_PATH%\sqlite3-cmake\CMakeLists.txt
echo cmake_minimum_required(VERSION 2.8) >> %RD3_PATH%\sqlite3-cmake\CMakeLists.txt
echo include_directories(${CMAKE_SOURCE_DIR}/src) >> %RD3_PATH%\sqlite3-cmake\CMakeLists.txt
echo add_library(sqlite3 STATIC src/sqlite3.c src/sqlite3.h src/sqlite3ext.h) >> %RD3_PATH%\sqlite3-cmake\CMakeLists.txt
echo add_definitions(-DSQLITE_ENABLE_RTREE) >> %RD3_PATH%\sqlite3-cmake\CMakeLists.txt
echo add_definitions(-DSQLITE_ENABLE_FTS4) >> %RD3_PATH%\sqlite3-cmake\CMakeLists.txt
echo add_definitions(-DSQLITE_ENABLE_FTS5) >> %RD3_PATH%\sqlite3-cmake\CMakeLists.txt
echo add_definitions(-DSQLITE_ENABLE_JSON1) >> %RD3_PATH%\sqlite3-cmake\CMakeLists.txt
echo add_definitions(-DSQLITE_ENABLE_RBU) >> %RD3_PATH%\sqlite3-cmake\CMakeLists.txt
echo add_definitions(-DSQLITE_ENABLE_STAT4) >> %RD3_PATH%\sqlite3-cmake\CMakeLists.txt
echo #add_definitions(-DSQLITE_THREADSAFE=0) >> %RD3_PATH%\sqlite3-cmake\CMakeLists.txt
echo install(FILES src/sqlite3.h src/sqlite3ext.h DESTINATION include) >> %RD3_PATH%\sqlite3-cmake\CMakeLists.txt
echo install(TARGETS sqlite3 LIBRARY DESTINATION lib ARCHIVE DESTINATION lib) >> %RD3_PATH%\sqlite3-cmake\CMakeLists.txt

mkdir .\sqlite3-cmake\build
cd .\sqlite3-cmake\build
cmake -DCMAKE_INSTALL_PREFIX=.\install\ .. -G "Visual Studio 16 2019"
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Debug ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy sqlite3-cmake debug file to depend"
xcopy %cd%\install\lib\*.lib %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
xcopy %cd%\install\bin\*.dll %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
del %cd%\install\ /f /s /q

echo "build sqlite3-cmake release"
cd %RD3_PATH%
mkdir .\sqlite3-cmake\build
cd .\sqlite3-cmake\build
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false
echo "copy sqlite3-cmake release file to depend"
xcopy %cd%\install\lib\*.lib %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\install\bin\*.dll %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\sqlite3\ /s /e /y
del %cd%\install\ /f /s /q









:BUILD_IMGUI
echo "copy imgui head file to depend"
cd %RD3_PATH%
xcopy %cd%\imgui\imgui.cpp %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imgui.h %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imgui_draw.cpp %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imgui_widgets.cpp %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imgui_internal.h %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imconfig.h %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imstb_rectpack.h %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imstb_textedit.h %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imstb_truetype.h %RD3_PATH%\..\src\GUI\ /y


:BUILD_STB
echo "copy stb head file to depend"
cd %RD3_PATH%
xcopy %cd%\stb\*.h %RD3_PATH%\..\depend\include\stb\ /s /e /y


:BUILD_RAPIDJSON
echo "copy rapidjson head file to depend"
cd %RD3_PATH%
xcopy %cd%\rapidjson\include\*.* %RD3_PATH%\..\depend\include\ /s /e /y

:BUILD_MINIAUDIO
echo "copy miniaudio head file to depend"
cd %RD3_PATH%
xcopy %cd%\miniaudio\miniaudio.h %RD3_PATH%\..\depend\include\miniaudio\ /y
xcopy %cd%\miniaudio\extras\stb_vorbis.c %RD3_PATH%\..\depend\include\miniaudio\ /y


:EXIT
pause