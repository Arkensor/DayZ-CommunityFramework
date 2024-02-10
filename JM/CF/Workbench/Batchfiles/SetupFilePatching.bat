@echo off
setlocal enableextensions enabledelayedexpansion 

cd /D "%~dp0"

set /a failed=0

set ModPrefixFile=Prefixes.txt
set /a ModPrefixIndex=0
set /a Length=0
set /a InclusiveLength=0

for /F "usebackq delims=" %%A in (%ModPrefixFile%) do (
	call echo %%ModPrefixIndex%%
	call echo %%A
	set ModPrefixDirectories[!ModPrefixIndex!]=%%A
	set /a ModPrefixIndex+=1
	set /a Length+=1
)

set /a InclusiveLength=%Length%-1

REM Set the root of your workdrive here!
set WorkDriveRoot=P:\

REM Don't touch the file after here unless you know what you are doing!

echo Searching for DayZ Tools...

for /F "Tokens=2* skip=2" %%A In ('REG QUERY "HKCU\Software\bohemia interactive\Dayz Tools" /v "Path" 2^>nul') do (
	set "_DAYZTOOLSPATH=%%B"
)

if "_DAYZTOOLSPATH" == "" (
	set /a failed=1
	echo.DayZ Tools was not set in the registry path.
) else (
	echo.Found DayZ Tools at "%_DAYZTOOLSPATH%"
)

echo Searching for DayZ...

for /F "Tokens=2* skip=2" %%A In ('REG QUERY "HKLM\SOFTWARE\Wow6432Node\bohemia interactive\Dayz" /v "main" 2^>nul') do (
	set "_DAYZPATH=%%B"
)

if "_DAYZPATH" == "" (
	set /a failed=1
	echo.DayZ was not set in the registry path.
) else (
	echo.Found DayZ at "%_DAYZPATH%"
)

echo Searching for DayZ Exp...

for /F "Tokens=2* skip=2" %%A In ('REG QUERY "HKLM\SOFTWARE\Wow6432Node\bohemia interactive\Dayz exp" /v "main" 2^>nul') do (
	set "_DAYZEXPPATH=%%B"
)

if "_DAYZEXPPATH" == "" (
	set /a failed=1
	echo.DayZ Exp was not set in the registry path.
) else (
	echo.Found DayZ Exp at "%_DAYZEXPPATH%"
)

if %failed%==1 (
	endlocal

	echo Failed to obtain paths.
	pause
	goto:eof
)

set "ServerDirectory=%_DAYZPATH%Server"
set "ClientDirectory=%_DAYZPATH%"
set "ExpClientDirectory=%_DAYZEXPPATH%"
set "ExpServerDirectory=%_DAYZPATH% Server Exp"
set "WorkbenchDirectory=%_DAYZTOOLSPATH%\Bin\Workbench"


echo.[101;93m The following variables being used are [0m
echo.[31m WorkDriveRoot:[0m "%WorkDriveRoot%"
echo.[31m ServerDirectory:[0m "%ServerDirectory%"
echo.[31m ClientDirectory:[0m "%ClientDirectory%"
echo.[31m ExpClientDirectory:[0m "%ExpClientDirectory%"
echo.[31m ExpServerDirectory:[0m "%ExpServerDirectory%"
echo.[31m WorkbenchDirectory:[0m "%WorkbenchDirectory%"
echo.[31m Mod Prefix Directories (total %Length%): [0m

for /l %%n in (0,1,%InclusiveLength%) do ( 
	echo.	!ModPrefixDirectories[%%n]! 
)

:PROMPT
SET /P AREYOUSURE=[101;93m Are you sure you want to continue? (Y/[N]) [0m
IF /I "%AREYOUSURE%" NEQ "Y" GOTO END

echo.[101;93m Setting up workbench addons symlink [0m
rmdir "%WorkbenchDirectory%\Addons\"
mklink /J "%WorkbenchDirectory%\Addons\" "%ClientDirectory%\Addons\"

echo.[101;93m Setting up the symbollic links for the server [0m
for /l %%n in (0,1,%InclusiveLength%-1) do (
	echo.[33mCreating \!ModPrefixDirectories[%%n]!\ link[0m
	rmdir "%ServerDirectory%\!ModPrefixDirectories[%%n]!\"
	mklink /J "%ServerDirectory%\!ModPrefixDirectories[%%n]!\" "%WorkDriveRoot%!ModPrefixDirectories[%%n]!\"\
)

echo.[101;93m Setting up the symbollic links for the client [0m
for /l %%n in (0,1,%InclusiveLength%-1) do (
	echo.[33mCreating \!ModPrefixDirectories[%%n]!\ link[0m
	rmdir "%ClientDirectory%\!ModPrefixDirectories[%%n]!\"
	mklink /J "%ClientDirectory%\!ModPrefixDirectories[%%n]!\" "%WorkDriveRoot%!ModPrefixDirectories[%%n]!\"\
)

echo.[101;93m Setting up the symbollic links for the experimental client [0m
for /l %%n in (0,1,%InclusiveLength%-1) do (
	echo.[33mCreating \!ModPrefixDirectories[%%n]!\ link[0m
	rmdir "%ExpClientDirectory%\!ModPrefixDirectories[%%n]!\"
	mkdir "%ExpClientDirectory%\!ModPrefixDirectories[%%n]!\..\"
	mklink /J "%ExpClientDirectory%\!ModPrefixDirectories[%%n]!\" "%WorkDriveRoot%!ModPrefixDirectories[%%n]!\"\
)

echo.[101;93m Setting up the symbollic links for the experimental server [0m
for /l %%n in (0,1,%InclusiveLength%-1) do (
	echo.[33mCreating \!ModPrefixDirectories[%%n]!\ link[0m
	rmdir "%ExpServerDirectory%\!ModPrefixDirectories[%%n]!\"
	mkdir "%ExpServerDirectory%\!ModPrefixDirectories[%%n]!\..\"
	mklink /J "%ExpServerDirectory%\!ModPrefixDirectories[%%n]!\" "%WorkDriveRoot%!ModPrefixDirectories[%%n]!\"\
)

:END
endlocal

pause