@echo off
setlocal enabledelayedexpansion

:: Set the base directory to the script location (folder where the batch file is)
set BASE_DIR=%~dp0

:: Set the source directory (the folder where your source files are located)
set SCR_DIR=src

:: Change to the src directory (relative to the base folder)
pushd "%BASE_DIR%\%SCR_DIR%"

:: Loop through all *.cpp files in src and print their relative paths
for /r %%f in (*.cpp) do (
    :: Extract the path relative to src
    set "relative_path=%%f"
    set "relative_path=!relative_path:%BASE_DIR%%SCR_DIR%\=!"

    :: Print the relative path
    echo !relative_path!
)

:: Return to the original directory
popd

endlocal
