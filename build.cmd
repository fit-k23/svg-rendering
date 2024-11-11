@echo off
setlocal enabledelayedexpansion

set BASE_DIR=%~dp0
set GPP_BIN=
set FLAGS=-std=c++17 -lgdiplus -lgdi32
set SRC_DIR=src
set SRC_FILES=
set BUILD_OUTPUT=svg_rendering.exe

where /q g++.exe
if %ERRORLEVEL%==0 (
    set GPP_BIN=g++
) else (
    echo [!] Could not find g++ binary. Cancelling...
    goto END
)

echo [#] Found G++ binary. Building...

pushd %BASE_DIR%\%SRC_DIR%

for /r %%f in (*.cpp) do (
    set "relative_path=%%f"
    set "relative_path=%SRC_DIR%^\!relative_path:%BASE_DIR%%SRC_DIR%\=!"

    echo [+] Adding !relative_path!
    set SRC_FILES=!SRC_FILES! !relative_path!
)

popd

@echo on
%GPP_BIN%%SRC_FILES% -o %BUILD_OUTPUT% %FLAGS%
@echo off
if %ERRORLEVEL%==0 (
    echo:
	echo [#] Done^^! The build was saved to: %BASE_DIR%%BUILD_OUTPUT%
	echo Press enter to exit or wait 5s...
)
:END
timeout 5 > NUL
@REM pause 1
:RAGEQUIT
endlocal