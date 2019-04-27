@echo off

set /a failed=0

if exist ../../project.cfg (
    echo Found the project.cfg
    cd ../../
) else (
    if exist project.cfg (
        echo Found the project.cfg
    ) else (
        echo Failed to find the project.cfg file, exitting.
        set /a failed=1
    )
)

if exist ../../user.cfg (
    echo Found the user.cfg
    cd ../../
) else (
    if exist user.cfg (
        echo Found the user.cfg
    ) else (
        echo Failed to find the user.cfg file, exitting.
        set /a failed=1
    )
)

if %failed%==1 (
    endlocal

    echo Failed to package the mod.

    cd %batchFileDirectory%
    goto:eof
)

set githubDirectory=%cd%\
set workbenchDataDirectory=%githubDirectory%Workbench\
set toolsDirectory=%workbenchDataDirectory%Tools\
set batchFileDirectory=%workbenchDataDirectory%BatchFiles\

set workbenchDirectory=
set modName=
set mods=
set workkbenchEXE=
set workbenchLaunchParams=

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg ModName') do (
    set modName=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg AdditionalWorkbenchMods') do (
    set mods=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg WorkbenchDirectory') do (
    set workbenchDirectory=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg WorkbenchEXE') do (
    set workkbenchEXE=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg WorkbenchLaunchParams') do (
    set workbenchLaunchParams=%%a
)

setlocal enableextensions enabledelayedexpansion

echo WorkbenchLaunchParams is: "%workbenchLaunchParams%"
if "%workbenchLaunchParams%"=="" (
    set /a failed=1
    echo WorkbenchLaunchParams parameter was not set in the project.cfg
)

echo WorkbenchEXE is: "%workkbenchEXE%"
if "%workkbenchEXE%"=="" (
    set /a failed=1
    echo WorkbenchEXE parameter was not set in the project.cfg
)

echo ModName is: "%modName%"
if "%modName%"=="" (
    set /a failed=1
    echo ModName parameter was not set in the project.cfg
)

echo AdditionalWorkbenchMods is: "%mods%"
if "%mods%"=="" (
    echo AdditionalWorkbenchMods parameter was not set in the project.cfg, ignoring.
    
    set mods=%modName%
) else (
    set mods=%mods%;%modName%
)

echo WorkbenchDirectory is: "%workbenchDirectory%"
if "%workbenchDirectory%"=="" (
    set /a failed=1
    echo WorkbenchDirectory parameter was not set in the project.cfg
)

if %failed%==1 (
    endlocal

    echo Failed to package the mod.

    cd %batchFileDirectory%
    pause
    goto:eof
)

chdir /d "%workbenchDirectory%"
echo start %workkbenchEXE% %workbenchLaunchParams% "-mod=%mods%" -dologs -adminlog -freezecheck -scriptDebug=true
start %workkbenchEXE% %workbenchLaunchParams% "-mod=%mods%" -dologs -adminlog -freezecheck -scriptDebug=true