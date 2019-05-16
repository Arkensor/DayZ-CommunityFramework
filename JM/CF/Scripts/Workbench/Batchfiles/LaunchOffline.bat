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
set modBuildDirectory=

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ModName') do (
	set modName=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg AdditionalSPMods') do (
	set mods=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg Port') do (
	set /a port=%%a
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

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg SPMission') do (
	set mission=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ClientEXE') do (
	set clientEXE=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ClientLaunchParams') do (
	set clientLaunchParams=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ModBuildDirectory') do (
	set modBuildDirectory=%%a
)

setlocal enableextensions enabledelayedexpansion

echo ClientEXE is: "%clientEXE%"
if "%clientEXE%"=="" (
	set /a failed=1
	echo ClientEXE parameter was not set in the project.cfg
)

echo ClientLaunchParams is: "%clientLaunchParams%"
if "%clientLaunchParams%"=="" (
	set /a failed=1
	echo ClientLaunchParams parameter was not set in the project.cfg
)

echo ModName is: "%modName%"
if "%modName%"=="" (
	set /a failed=1
	echo ModName parameter was not set in the project.cfg
)

echo AdditionalSPMods is: "%mods%"
if "%mods%"=="" (
	echo AdditionalSPMods parameter was not set in the project.cfg, ignoring.
	
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

chdir /d "%gameDirectory%"
echo start %clientEXE% %clientLaunchParams% "-mod=%modList%" "-mission=%mission%" -dologs -adminlog -freezecheck -scriptDebug=true
start %clientEXE% %clientLaunchParams% "-mod=%modList%" "-mission=%mission%" -dologs -adminlog -freezecheck -scriptDebug=true

endlocal