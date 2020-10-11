@echo off

cd /D "%~dp0"

set /a failed=0

if exist ../project.cfg (
	echo Found the project.cfg
) else (
	echo Failed to find the project.cfg file, exitting.
	set /a failed=1
)

if exist ../user.cfg (
	echo Found the user.cfg
) else (
	echo Failed to find the user.cfg file, exitting.
	set /a failed=1
)

if %failed%==1 (
    endlocal

    echo Failed to package the mod.
    goto:eof
)

set port=0
set password=
set gameDirectory=
set serverDirectory=
set serverProfileDirectory=
set serverConfig=
set modName=
set mods=
set mission=
set clientEXE=
set serverEXE=
set clientLaunchParams=
set serverLaunchParams=
set modBuildDirectory=
set playerName=

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ModName') do (
    set modName=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg AdditionalMPMods') do (
    set mods=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg Port') do (
    set port=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ServerPassword') do (
    set password=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg GameDirectory') do (
    set gameDirectory=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ServerDirectory') do (
    set serverDirectory=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ServerProfileDirectory') do (
    set serverProfileDirectory=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ServerConfig') do (
    set serverConfig=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg MPMission') do (
    set mission=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ClientEXE') do (
    set clientEXE=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ServerEXE') do (
    set serverEXE=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ClientLaunchParams') do (
    set clientLaunchParams=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ServerLaunchParams') do (
    set serverLaunchParams=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg PlayerName') do (
    set playerName=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ModBuildDirectory') do (
	set modBuildDirectory=%%a
)

setlocal enableextensions enabledelayedexpansion

echo ClientLaunchParams is: "%clientLaunchParams%"
if "%clientLaunchParams%"=="" (
    echo ClientLaunchParams parameter was not set in the project.cfg, continuing.
)

echo ServerLaunchParams is: "%serverLaunchParams%"
if "%serverLaunchParams%"=="" (
    echo ServerLaunchParams parameter was not set in the project.cfg, continuing.
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
    echo AdditionalMPMods parameter was not set in the project.cfg, continuing.
    
    set mods=%modName%
) else (
    set mods=%mods%;%modName%
)

echo Port is: "%port%"
if "%port%"==0 (
    echo Port parameter was not set in the project.cfg, using 2302.
    set port=-port=2302
) else (
    set port=-port=%port%
)

echo ServerPassword is: "%password%"
if "%password%"=="" (
    echo ServerPassword parameter was not set in the project.cfg, continuing.
) else (
    set password=-password=%password%
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

echo ServerConfig is: "%serverConfig%"
if "%serverConfig%"=="" (
    set /a failed=1
    echo ServerConfig parameter was not set in the project.cfg
)

echo PlayerName is: "%playerName%"
if "%playerName%"=="" (
    echo PlayerName parameter was not set in the project.cfg, continuing.
) else (
    set playerName=-name=%playerName%
)

echo ModBuildDirectory is: "%modBuildDirectory%"
if "%modBuildDirectory%"=="" (
	set /a failed=1
	echo ModBuildDirectory parameter was not set in the project.cfg
)

if %failed%==1 (
    endlocal

    echo Failed to package the mod.
    goto:eof
)

CALL Exit.bat

for %%a in ("%mods:;=" "%") do (
    set mod=%%~a
    if not defined modList (
        set modList=%modBuildDirectory%!mod!
    ) else (
        set modList=!modList!;%modBuildDirectory%!mod!
    )
)

chdir /d "%serverDirectory%"
echo start %serverEXE% %serverLaunchParams% "-config=%serverConfig%" "%port%" "-profiles=%serverProfileDirectory%" -dologs -adminlog -freezecheck "-scriptDebug=true" "-cpuCount=4" "-mission=%mission%" "-mod=%modList%"
start %serverEXE% %serverLaunchParams% "-config=%serverConfig%" "%port%" "-profiles=%serverProfileDirectory%" -dologs -adminlog -freezecheck "-scriptDebug=true" "-cpuCount=4" "-mission=%mission%" "-mod=%modList%"

TIMEOUT /T 5 /NOBREAK

chdir /d "%gameDirectory%"
echo start %clientEXE% %clientLaunchParams% "-connect=127.0.0.1" "%port%" "%playerName%" "%password%" "-mod=%modList%" -dologs -adminlog -freezecheck "-scriptDebug=true"
start %clientEXE% %clientLaunchParams% "-connect=127.0.0.1" "%port%" "%playerName%" "%password%" "-mod=%modList%" -dologs -adminlog -freezecheck "-scriptDebug=true"