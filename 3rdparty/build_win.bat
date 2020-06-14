set NMAKE=()
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat" (
    set NMAKE="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"
    goto :FOUND_NMAKE
)
if exist "%ProgramFiles%\Microsoft Visual Studio\2019\Professional\Common7\Tools\VsDevCmd.bat" (
    set NMAKE="%ProgramFiles%\Microsoft Visual Studio\2019\Professional\Common7\Tools\VsDevCmd.bat"
    goto :FOUND_NMAKE
)
if exist "%ProgramFiles%\Microsoft Visual Studio\2019\Enterprise\Common7\Tools\VsDevCmd.bat" (
    set NMAKE="%ProgramFiles%\Microsoft Visual Studio\2019\Enterprise\Common7\Tools\VsDevCmd.bat"
    goto :FOUND_NMAKE
)

if %NMAKE%==() (
    echo "I couldn't find nmake on your PC. Make sure it's installed somewhere, and if it's not in the above if statements (in VsDevCmd.bat), add it."
    goto :EXIT
) 

:FOUND_NMAKE
::git submodule update --init --recursive

call %NMAKE%
set RD3_PATH=%cd%

:BUILD_IK
echo "build ik debug"
cd %RD3_PATH%
mkdir .\ik\build\debug
cd .\ik\build\debug
cmake -DIK_LIB_TYPE=SHARED -DIK_PRECISION=float -DIK_PIC=OFF -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=.\install\ ..\..\ -G "NMake Makefiles" 
nmake
nmake install
echo "copy ik debug file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
echo "build ik release"
cd %RD3_PATH%
mkdir .\ik\build\release
cd .\ik\build\release
cmake -DIK_LIB_TYPE=SHARED -DIK_PRECISION=float -DIK_PIC=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.\install\ ..\..\ -G "NMake Makefiles" 
nmake
nmake install
echo "copy ik release file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /s /e /y


:BUILD_TBB
echo "build tbb debug"
cd %RD3_PATH%
mkdir .\tbb\build\debug
cd .\tbb\build\debug
cmake -DTBB_BUILD_STATIC=OFF -DTBB_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=.\install\ ..\..\ -G "NMake Makefiles" 
nmake
nmake install
echo "copy tbb debug file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
echo "build tbb release"
cd %RD3_PATH%
mkdir .\tbb\build\release
cd .\tbb\build\release
cmake -DTBB_BUILD_STATIC=OFF -DTBB_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.\install\ ..\..\ -G "NMake Makefiles" 
nmake
nmake install
echo "copy tbb release file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /s /e /y


:BUILD_STB
echo "copy stb head file to depend"
cd %RD3_PATH%
xcopy %cd%\stb\*.h %RD3_PATH%\..\depend\include\stb\ /s /e /y


:BUILD_RAPIDJSON
echo "copy rapidjson head file to depend"
cd %RD3_PATH%
xcopy %cd%\rapidjson\include\*.* %RD3_PATH%\..\depend\include\ /s /e /y


:BUILD_RECASTNAVIGATION
echo "build recastnavigation debug"
cd %RD3_PATH%
mkdir .\recastnavigation\build\debug
cd .\recastnavigation\build\debug
cmake -DRECASTNAVIGATION_DEMO=OFF -DRECASTNAVIGATION_EXAMPLES=OFF -DRECASTNAVIGATION_TESTS=OFF -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=.\install\ ..\..\ -G "NMake Makefiles" 
nmake
nmake install
echo "copy recastnavigation debug file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
echo "build recastnavigation release"
cd %RD3_PATH%
mkdir .\recastnavigation\build\release
cd .\recastnavigation\build\release
cmake -DRECASTNAVIGATION_DEMO=OFF -DRECASTNAVIGATION_EXAMPLES=OFF -DRECASTNAVIGATION_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.\install\ ..\..\ -G "NMake Makefiles" 
nmake
nmake install
echo "copy recastnavigation release file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /s /e /y

:BUILD_IMGUI
echo "copy imgui head file to depend"
cd %RD3_PATH%
xcopy %cd%\imgui\imgui.cpp %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imgui.h %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imgui_demo.cpp %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imgui_draw.cpp %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imgui_widgets.cpp %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imgui_internal.h %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imconfig.h %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imstb_rectpack.h %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imstb_textedit.h %RD3_PATH%\..\src\GUI\ /y
xcopy %cd%\imgui\imstb_truetype.h %RD3_PATH%\..\src\GUI\ /y


:BUILD_ZLIB
echo "build zlib debug"
cd %RD3_PATH%
mkdir .\zlib\build\debug
cd .\zlib\build\debug
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=.\install\ -DINSTALL_BIN_DIR=.\install\bin\ -DINSTALL_INC_DIR=.\install\include\zlib\ -DINSTALL_LIB_DIR=.\install\lib\ -DINSTALL_MAN_DIR=.\install\man\ -DINSTALL_PKGCONFIG_DIR=.\install\pkgconfig\ ..\..\ -G "NMake Makefiles"
nmake
nmake install
echo "copy zlib debug file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
echo "build zlib release"
cd %RD3_PATH%
mkdir .\zlib\build\release
cd .\zlib\build\release
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.\install\ -DINSTALL_BIN_DIR=.\install\bin\ -DINSTALL_INC_DIR=.\install\include\zlib\ -DINSTALL_LIB_DIR=.\install\lib\ -DINSTALL_MAN_DIR=.\install\man\ -DINSTALL_PKGCONFIG_DIR=.\install\pkgconfig\ ..\..\ -G "NMake Makefiles"
nmake
nmake install
echo "copy zlib release file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /s /e /y

:BUILD_ZIPPER
echo "build zipper debug"
cd %RD3_PATH%
mkdir .\zipper\build\debug
cd .\zipper\build\debug
cmake -DLIBZ_INCLUDE_DIR=%RD3_PATH%\..\depend\include\zlib\ -DLIBZ_LIBRARY=%RD3_PATH%\..\depend\lib\win\debug\zlibstaticd.lib -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=.\install\ ..\..\ -G "NMake Makefiles" 
nmake
nmake install
echo "copy zipper debug file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
echo "build zipper release"
cd %RD3_PATH%
mkdir .\zipper\build\release
cd .\zipper\build\release
cmake -DLIBZ_INCLUDE_DIR=%RD3_PATH%\..\depend\include\zlib\ -DLIBZ_LIBRARY=%RD3_PATH%\..\depend\lib\win\release\zlibstatic.lib -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.\install\ ..\..\ -G "NMake Makefiles" 
nmake
nmake install
echo "copy zipper release file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /s /e /y


:BUILD_PHYSX
echo "build phyxs debug"
cd %RD3_PATH%
set PHYSX_ROOT_PATH=%RD3_PATH%\PhysX\physx\
set PATH=%PATH%;%PHYSX_ROOT_PATH%;%PHYSX_ROOT_PATH%\source\compiler\cmake
mkdir .\PhysX\physx\compiler\public\build\debug
cd .\PhysX\physx\compiler\public\build\debug
cmake -DTARGET_BUILD_PLATFORM=windows -DPX_OUTPUT_ARCH=x86 --no-warn-unused-cli -DPHYSX_ROOT_DIR=%PHYSX_ROOT_PATH% -DPM_VSWHERE_PATH=%PHYSX_ROOT_PATH%/../externals/VsWhere -DCMAKEMODULES_PATH=%PHYSX_ROOT_PATH%/../externals/CMakeModules -DPXSHARED_PATH=%PHYSX_ROOT_PATH%/../pxshared -DPM_TARGA_PATH=%PHYSX_ROOT_PATH%/../externals/targa -DPM_PATHS=%PHYSX_ROOT_PATH%/../externals/CMakeModules;%PHYSX_ROOT_PATH%/../externals/targa -DCMAKE_PREFIX_PATH=%RD3_PATH%/PhysX/physx/../externals/CMakeModules;%RD3_PATH%/PhysX/physx/../externals/targa -DPHYSX_ROOT_DIR=%RD3_PATH%/PhysX/physx -DPX_OUTPUT_LIB_DIR=%RD3_PATH%/PhysX/physx -DPX_OUTPUT_BIN_DIR=%RD3_PATH%/PhysX/physx -DPX_BUILDSNIPPETS=TRUE -DPX_BUILDPUBLICSAMPLES=TRUE -DPX_GENERATE_STATIC_LIBRARIES=FALSE -DNV_USE_STATIC_WINCRT=TRUE -DNV_USE_DEBUG_WINCRT=TRUE -DPX_FLOAT_POINT_PRECISE_MATH=FALSE -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=.\install\ ..\..\ -G "NMake Makefiles" 
nmake
nmake install
pause
echo "copy phyxs debug file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
echo "build phyxs release"
cd %RD3_PATH%
mkdir .\PhysX\physx\compiler\public\build\release
cd .\PhysX\physx\compiler\public\build\release
cmake -DCMAKE_INSTALL_PREFIX=.\install\ ..\..\ -G "NMake Makefiles" 
nmake
nmake install
echo "copy phyxs release file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /s /e /y


:EXIT
pause