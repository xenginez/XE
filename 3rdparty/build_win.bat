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
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /e /y
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
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\debug\ /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\debug\ /e /y
del %cd%\install\ /f /s /q

echo "build tbb release"
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy tbb release file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\release\ /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\release\ /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /e /y
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
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\debug\ /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\debug\ /e /y
del %cd%\install\ /f /s /q

echo "build recastnavigation release"
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy recastnavigation release file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\release\ /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\release\ /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\recastnavigation\ /e /y
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
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\debug\PhysX_64.dll %RD3_PATH%\..\depend\bin\win\debug\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\debug\PhysXCommon_64.dll %RD3_PATH%\..\depend\bin\win\debug\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\debug\PhysXFoundation_64.dll %RD3_PATH%\..\depend\bin\win\debug\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\debug\PhysX_64.pdb %RD3_PATH%\..\depend\bin\win\debug\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\debug\PhysXCommon_64.pdb %RD3_PATH%\..\depend\bin\win\debug\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\debug\PhysXFoundation_64.pdb %RD3_PATH%\..\depend\bin\win\debug\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\debug\PhysX_64.lib %RD3_PATH%\..\depend\lib\win\debug\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\debug\PhysXCommon_64.lib %RD3_PATH%\..\depend\lib\win\debug\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\debug\PhysXFoundation_64.lib %RD3_PATH%\..\depend\lib\win\debug\ /y
del %cd%\PhysX\physx\install\ /f /s /q

echo "build phyxs release"
cd %RD3_PATH%
msbuild.exe "%cd%\PhysX\physx\compiler\vc16win64\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy phyxs release file to depend"
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\*.dll %RD3_PATH%\..\depend\bin\win\release\ /e /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\*.pdb %RD3_PATH%\..\depend\bin\win\release\ /e /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\*.lib %RD3_PATH%\..\depend\lib\win\release\ /e /y

xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\PhysX_64.dll %RD3_PATH%\..\depend\bin\win\release\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\PhysXCommon_64.dll %RD3_PATH%\..\depend\bin\win\release\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\PhysXFoundation_64.dll %RD3_PATH%\..\depend\bin\win\release\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\PhysX_64.pdb %RD3_PATH%\..\depend\bin\win\release\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\PhysXCommon_64.pdb %RD3_PATH%\..\depend\bin\win\release\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\PhysXFoundation_64.pdb %RD3_PATH%\..\depend\bin\win\release\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\PhysX_64.lib %RD3_PATH%\..\depend\lib\win\release\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\PhysXCommon_64.lib %RD3_PATH%\..\depend\lib\win\release\ /y
xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\bin\win.x86_64.vc142.md\release\PhysXFoundation_64.lib %RD3_PATH%\..\depend\lib\win\release\ /y

xcopy %cd%\PhysX\physx\install\vc15win64\PhysX\include\*.* %RD3_PATH%\..\depend\include\PhysX\ /e /y
xcopy %cd%\PhysX\physx\install\vc15win64\PxShared\include\*.* %RD3_PATH%\..\depend\include\PhysX\ /e /y
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
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /e /y
del %cd%\install\ /f /s /q


:BUILD_LZ4
echo "build lz4 debug"
cd %RD3_PATH%
mkdir .\lz4\build\cmake\build
cd .\lz4\build\cmake\build
cmake -DBUILD_SHARED_LIB=OFF -DBUILD_STATIC_LIB=ON -DLZ4_BUILD_CIL=OFF -DLZ4_BUILD_LEGACY_LZ4C=OFF -DLZ4_POSITION_INDEPENDENT_LIB=OFF -DCMAKE_INSTALL_PREFIX=.\install\ .. -G "Visual Studio 16 2019"
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Debug ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false
echo "copy lz4 debug file to depend"
xcopy %cd%\install\lib\lz4.lib %RD3_PATH%\..\depend\lib\win\debug\ /e /y
xcopy %cd%\install\lib\lz4.pdb %RD3_PATH%\..\depend\lib\win\debug\ /e /y
del %cd%\install\ /f /s /q
echo "build lz4 release"
cd %RD3_PATH%
cd .\lz4\build\cmake\build
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false
echo "copy lz4 release file to depend"
xcopy %cd%\install\lib\lz4.lib %RD3_PATH%\..\depend\lib\win\release\ /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\lz4\ /e /y
del %cd%\install\ /f /s /q








:BUILD_IMGUI
echo "copy imgui head file to depend"
cd %RD3_PATH%
xcopy %cd%\imgui\imgui.cpp %RD3_PATH%\..\modules\GUI\ /y
xcopy %cd%\imgui\imgui.h %RD3_PATH%\..\modules\GUI\ /y
xcopy %cd%\imgui\imgui_draw.cpp %RD3_PATH%\..\modules\GUI\ /y
xcopy %cd%\imgui\imgui_widgets.cpp %RD3_PATH%\..\modules\GUI\ /y
xcopy %cd%\imgui\imgui_internal.h %RD3_PATH%\..\modules\GUI\ /y
xcopy %cd%\imgui\imconfig.h %RD3_PATH%\..\modules\GUI\ /y
xcopy %cd%\imgui\imstb_rectpack.h %RD3_PATH%\..\modules\GUI\ /y
xcopy %cd%\imgui\imstb_textedit.h %RD3_PATH%\..\modules\GUI\ /y
xcopy %cd%\imgui\imstb_truetype.h %RD3_PATH%\..\modules\GUI\ /y

:BUILD_STB
echo "copy stb head file to depend"
cd %RD3_PATH%
xcopy %cd%\stb\*.h %RD3_PATH%\..\depend\include\stb\ /e /y

:BUILD_RAPIDJSON
echo "copy rapidjson head file to depend"
cd %RD3_PATH%
xcopy %cd%\rapidjson\include\*.* %RD3_PATH%\..\depend\include\ /e /y

:BUILD_MINIAUDIO
echo "copy miniaudio head file to depend"
cd %RD3_PATH%
xcopy %cd%\miniaudio\miniaudio.h %RD3_PATH%\..\depend\include\miniaudio\ /y
xcopy %cd%\miniaudio\extras\stb_vorbis.c %RD3_PATH%\..\depend\include\miniaudio\ /y

:BUILD_CSV2
echo "copy csv2 head file to depend"
cd %RD3_PATH%
xcopy %cd%\csv2\single_include\csv2\csv2.hpp %RD3_PATH%\..\depend\include\csv2\ /e /y

:BUILD_D3DX12
echo "copy d3dx12 head file to depend"
cd %RD3_PATH%
xcopy %cd%\D3DX12\d3dx12.h %RD3_PATH%\..\depend\include\D3DX12\ /e /y

:BUILD_VULKAN
echo "copy vulkan head file to depend"
cd %RD3_PATH%
xcopy %cd%\Vulkan-Headers\include\vulkan\*.* %RD3_PATH%\..\depend\include\vulkan\ /e /y

:BUILD_VOLK
echo "copy volk head file to depend"
cd %RD3_PATH%
xcopy %cd%\volk\volk.h %RD3_PATH%\..\depend\include\volk\ /e /y
xcopy %cd%\volk\volk.c %RD3_PATH%\..\depend\include\volk\ /e /y


:EXIT
pause