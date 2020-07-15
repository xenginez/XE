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
goto :BUILD_OPENAL
echo "update git submodule"
git submodule update --init --recursive

:BUILD_IK
cd %RD3_PATH%
echo "build ik debug"
mkdir .\ik\build
cd .\ik\build
cmake -DIK_LIB_TYPE=SHARED -DIK_PRECISION=float -DIK_PIC=OFF -DCMAKE_INSTALL_PREFIX=.\install\ .. -G "Visual Studio 16 2019" 
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Debug ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy ik debug file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
del %cd%\install\ /f /s /q

echo "build ik release"
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy ik release file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
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
mkdir .\zlib\build
cd .\zlib\build
cmake -DCMAKE_INSTALL_PREFIX=.\install\ -DINSTALL_BIN_DIR=.\install\bin\ -DINSTALL_INC_DIR=.\install\include\zlib\ -DINSTALL_LIB_DIR=.\install\lib\ -DINSTALL_MAN_DIR=.\install\man\ -DINSTALL_PKGCONFIG_DIR=.\install\pkgconfig\ .. -G "Visual Studio 16 2019"
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Debug ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false
    
echo "copy zlib debug file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
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
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /s /e /y
del %cd%\install\ /f /s /q


:BUILD_LIBSIMDPP
echo "build libsimdpp debug"
cd %RD3_PATH%
mkdir .\libsimdpp\build
cd .\libsimdpp\build
cmake -DCMAKE_INSTALL_PREFIX=.\install\ .. -G "Visual Studio 16 2019" 
msbuild.exe ".\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Debug ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy zipper debug file to depend"
xcopy %cd%\install\include\libsimdpp-2.1\*.* %RD3_PATH%\..\src\Math\libsimdpp\ /s /e /y
del %cd%\install\ /f /s /q


:BUILD_PHYSX
echo "build phyxs debug"
cd %RD3_PATH%
call %cd%\PhysX\physx\generate_projects.bat vc16win64
msbuild.exe "%cd%\PhysX\physx\compiler\vc16win64\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Debug ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy phyxs debug file to depend"
xcopy %cd%\PhysX\physx\install\vc16win64\PhysX\bin\win.x86_64.vc142.md\debug\*.dll %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
xcopy %cd%\PhysX\physx\install\vc16win64\PhysX\bin\win.x86_64.vc142.md\debug\*.pdb %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
xcopy %cd%\PhysX\physx\install\vc16win64\PhysX\bin\win.x86_64.vc142.md\debug\*.lib %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
del %cd%\PhysX\physx\install\ /f /s /q

echo "build phyxs release"
cd %RD3_PATH%
msbuild.exe "%cd%\PhysX\physx\compiler\vc16win64\INSTALL.vcxproj"  /m /nr:true ^
    /p:Configuration=Release ^
    /p:Platform=x64 ^
    /p:AppxBundlePlatforms=x64 ^
    /p:UseSubFolderForOutputDirDuringMultiPlatformBuild=false

echo "copy phyxs release file to depend"
xcopy %cd%\PhysX\physx\install\vc16win64\PhysX\bin\win.x86_64.vc142.md\release\*.dll %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\PhysX\physx\install\vc16win64\PhysX\bin\win.x86_64.vc142.md\release\*.pdb %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\PhysX\physx\install\vc16win64\PhysX\bin\win.x86_64.vc142.md\release\*.lib %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\PhysX\physx\install\vc16win64\PhysX\include\*.* %RD3_PATH%\..\depend\include\PhysX\ /s /e /y
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
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
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
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\release\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\release\ /s /e /y
xcopy %cd%\install\include\*.* %RD3_PATH%\..\depend\include\ /s /e /y
del %cd%\install\ /f /s /q

:EXIT
pause