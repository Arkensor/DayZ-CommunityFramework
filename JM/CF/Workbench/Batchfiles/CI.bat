@echo off
setlocal enabledelayedexpansion

set skipPboCleanup=0
set skipEnumSpecialPaths=0
set modsToBuild=Main
set killGame=1
set killWorkbench=0

:OPTIONS
REM parse command line options
if "%~1"=="" goto MAIN
if /I "%~1"=="rebuildAll" (
	REM handled by CI1.bat
) else if /I "%~1"=="skipPboCleanup" (
	echo Command line option skipPboCleanup found - not removing orphaned PBOs
	set skipPboCleanup=1
) else if /I "%~1"=="noIgnore" (
	REM handled by CI1.bat
) else if /I "%~1"=="skipEnumSpecialPaths" (
	echo Command line option skipEnumSpecialPaths found - skipping check for changed "special" file paths
	set skipEnumSpecialPaths=1
) else if /I "%~1"=="killGame" (
	echo Command line option killGame found - will close all instances of game ^(client/server^) if running
	set killGame=1
) else if /I "%~1"=="killWorkbench" (
	echo Command line option killWorkbench found - will close all instances of Workbench if running
	set killWorkbench=1
)
shift /1
goto OPTIONS

:MAIN

if %killGame%==1 CALL Exit.bat
if %killWorkbench%==1 taskkill /F /IM workbenchApp.exe /T

set "modsToCheck=%modsToBuild%"

cd /D "%~dp0"

set success=1

if exist "..\project.cfg.bat" del "..\project.cfg.bat"

for /f "usebackq delims=" %%a in ( ../project.cfg ) do (
	echo set %%a>>"..\project.cfg.bat"
)

call "..\project.cfg.bat"

if exist "..\user.cfg.bat" del "..\user.cfg.bat"

for /f "usebackq delims=" %%a in ( ../user.cfg ) do (
	echo set %%a>>"..\user.cfg.bat"
)

call "..\user.cfg.bat"

pushd "%workDrive%%prefixLinkRoot%\"

echo %date% %time% Getting config paths...
dir /B /S config.cpp > "%workDrive%Temp\%PrefixLinkRoot%-ALL-configpaths-unfiltered.list"
echo %date% %time% ...got config paths

if %skipEnumSpecialPaths% NEQ 1 (
	call "%~dp0CI0_EnumSpecialPaths.bat" ALL
)

popd

if exist "%~dp0..\Logs\*.failure" del "%~dp0..\Logs\*.failure"
if exist "%~dp0..\Logs\*.tmp" del "%~dp0..\Logs\*.tmp"
if exist "%~dp0..\Logs\*.success" del "%~dp0..\Logs\*.success"

REM Build + pack mod
if not exist CI_Build.bat (
	echo ERROR: %cd%\CI_Build.bat does not exist.>>"%workDrive%%prefixLinkRoot%\Workbench\Logs\Build.log"
	goto end
)
echo !date! !time! CI_Build.bat is starting
echo %time% > "%~dp0..\Logs\Build.tmp"
start "%%a" CI_Build.bat skipEnumPaths exitCmd %*

:loop
echo Waiting 1 seconds
ping -n 2 127.0.0.1 >NUL
set running=0
if exist %~dp0..\Logs\Build.tmp (
	set /a running+=1
	echo CI_Build.bat is running
)
if %running%==0 goto end
goto loop

:end
if exist %~dp0..\Logs\Build.failure (
	set success=0
)
if "!success!" NEQ "1" (
	echo /////////////////////////////////////////////////////////////>>"%workDrive%%prefixLinkRoot%\Workbench\Logs\Build.log"
	echo %date% %time% Something went wrong, check logs. Failed builds:>>"%workDrive%%prefixLinkRoot%\Workbench\Logs\Build.log"
	if exist Build.failure echo %%a>>"%workDrive%%prefixLinkRoot%\Workbench\Logs\Build.log"
	echo /////////////////////////////////////////////////////////////>>"%workDrive%%prefixLinkRoot%\Workbench\Logs\Build.log"
) else (
	if not exist %~dp0..\Logs\Build.success (
		set success=0
		echo %date% %time% ERROR: Building Mod did not finish successfully.>>"%workDrive%%prefixLinkRoot%\Workbench\Logs\Build.log"
	)
)
if "!success!"=="1" echo %date% %time% Successfully packaged all mods.>>"%workDrive%%prefixLinkRoot%\Workbench\Logs\Build.log"
type "%workDrive%%prefixLinkRoot%\Workbench\Logs\Build.log"
if "!success!" NEQ "1" goto abort

endlocal
exit /B 0

:abort
endlocal
REM Has to be the last line so it sets the exitcode
exit /B 1