@echo off

set /a failed=0

if exist ../../project.cfg (
    echo Found the project.cfg
    cd ../../
) else (
    echo project.cfg doesn't exist in first directory, trying the next possible directory.
    if exist project.cfg (
        echo Found the project.cfg
    ) else (
        echo Failed to find the project.cfg
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

set /a port=0
set password=
set gameDirectory=
set serverDirectory=
set serverProfileDirectory=
set modName=
set mods=
set mission=
set clientEXE=
set serverEXE=
set clientLaunchParams=
set serverLaunchParams=
set workDrive=

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg WorkDrive') do (
    set workDrive=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg ModName') do (
    set modName=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg AdditionalMPMods') do (
    set mods=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg Port') do (
    set /a port=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg ServerPassword') do (
    set password=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg GameDirectory') do (
    set gameDirectory=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg ServerDirectory') do (
    set serverDirectory=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg ServerProfileDirectory') do (
    set serverProfileDirectory=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg MPMission') do (
    set mission=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg ClientEXE') do (
    set clientEXE=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg ServerEXE') do (
    set serverEXE=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg ClientLaunchParams') do (
    set clientLaunchParams=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg ServerLaunchParams') do (
    set serverLaunchParams=%%a
)

setlocal enableextensions enabledelayedexpansion

echo WorkDrive is: "%workDrive%"
if "%workDrive%"=="" (
    set /a failed=1
    echo WorkDrive parameter was not set in the project.cfg
)

echo ClientLaunchParams is: "%clientLaunchParams%"
if "%clientLaunchParams%"=="" (
    set /a failed=1
    echo ClientLaunchParams parameter was not set in the project.cfg
)

echo ServerLaunchParams is: "%serverLaunchParams%"
if "%serverLaunchParams%"=="" (
    set /a failed=1
    echo ServerLaunchParams parameter was not set in the project.cfg
)

echo ClientEXE is: "%clientEXE%"
if "%clientEXE%"=="" (
    set /a failed=1
    echo ClientEXE parameter was not set in the project.cfg
)

echo ServerEXE is: "%serverEXE%"
if "%serverEXE%"=="" (
    set /a failed=1
    echo ServerEXE parameter was not set in the project.cfg
)

echo MPMission is: "%mission%"
if "%mission%"=="" (
    set /a failed=1
    echo MPMission parameter was not set in the project.cfg
)

echo ModName is: "%modName%"
if "%modName%"=="" (
    set /a failed=1
    echo ModName parameter was not set in the project.cfg
)

echo AdditionalMPMods is: "%mods%"
if "%mods%"=="" (
    echo AdditionalMPMods parameter was not set in the project.cfg, ignoring.
    
    set mods=%modName%
) else (
    set mods=%mods%;%modName%
)

echo Port is: "%port%"
if "%port%"==0 (
    set /a failed=1
    echo Port parameter was not set in the project.cfg
)

echo ServerPassword is: "%password%"
if "%password%"=="" (
    set /a failed=1
    echo ServerPassword parameter was not set in the project.cfg
)

echo GameDirectory is: "%gameDirectory%"
if "%gameDirectory%"=="" (
    set /a failed=1
    echo GameDirectory parameter was not set in the project.cfg
)

echo ServerDirectory is: "%serverDirectory%"
if "%serverDirectory%"=="" (
    set /a failed=1
    echo ServerDirectory parameter was not set in the project.cfg
)

echo ServerProfileDirectory is: "%serverProfileDirectory%"
if "%serverProfileDirectory%"=="" (
    set /a failed=1
    echo ServerProfileDirectory parameter was not set in the project.cfg
)

if %failed%==1 (
    endlocal

    echo Failed to package the mod.

    cd %batchFileDirectory%
    goto:eof
)

CALL %batchFileDirectory%Exit.bat

chdir /d "%serverDirectory%"
echo start "" "%serverDirectory%%serverEXE%" %serverLaunchParams% -scrAllowFileWrite -config=serverDZ.cfg -port=%port% "-profiles=%serverProfileDirectory%" -password=%password% -dologs -adminlog -freezecheck -scriptDebug=true -cpuCount=4 "-mission=%mission%" "-mod=%mods%"
start "" "%serverDirectory%%serverEXE%" %serverLaunchParams% -scrAllowFileWrite -config=serverDZ.cfg -port=%port% "-profiles=%serverProfileDirectory%" -password=%password% -dologs -adminlog -freezecheck -scriptDebug=true -cpuCount=4 "-mission=%mission%" "-mod=%mods%"

TIMEOUT /T 5 /NOBREAK

chdir /d "%gameDirectory%"
echo start "" "%gameDirectory%%clientEXE%" %clientLaunchParams% -connect=127.0.0.1 -port=%port% -password=%password% "-mod=%mods%" -dologs -adminlog -freezecheck -scriptDebug=true
start "" "%gameDirectory%%clientEXE%" %clientLaunchParams% -connect=127.0.0.1 -port=%port% -password=%password% "-mod=%mods%" -dologs -adminlog -freezecheck -scriptDebug=true