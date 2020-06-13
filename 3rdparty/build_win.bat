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
call %NMAKE%
set RD3_PATH=%cd%

goto :BUILD_RECASTNAVIGATION

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

:BUILD_ZIPPER
echo "build zipper debug"
cd %RD3_PATH%
mkdir .\zipper\build\debug
cd .\zipper\build\debug
cmake -DTBB_BUILD_STATIC=OFF -DTBB_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=.\install\ ..\..\ -G "NMake Makefiles" 
nmake
nmake install
echo "copy zipper debug file to depend"
xcopy %cd%\install\lib\*.* %RD3_PATH%\..\depend\lib\win\debug\ /s /e /y
xcopy %cd%\install\bin\*.* %RD3_PATH%\..\depend\bin\win\debug\ /s /e /y
echo "build zipper release"
cd %RD3_PATH%
mkdir .\zipper\build\release
cd .\zipper\build\release
cmake -DTBB_BUILD_STATIC=OFF -DTBB_BUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=.\install\ ..\..\ -G "NMake Makefiles" 
nmake
nmake install
echo "copy zipper release file to depend"
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


:EXIT
pause