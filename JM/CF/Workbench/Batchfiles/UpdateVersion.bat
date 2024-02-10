@echo off
setlocal enableextensions enabledelayedexpansion

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

if exist "%~dp0..\project.cfg.bat" del "%~dp0..\project.cfg.bat"

for /f "usebackq delims=" %%a in ( "%~dp0..\project.cfg" ) do (
	echo set %%a>>"%~dp0..\project.cfg.bat"
)

call "%~dp0..\project.cfg.bat"

if exist "%~dp0..\user.cfg.bat" del "%~dp0..\user.cfg.bat"

for /f "usebackq delims=" %%a in ( "%~dp0..\user.cfg" ) do (
	echo set %%a>>"%~dp0..\user.cfg.bat"
)

call "%~dp0..\user.cfg.bat"

echo WorkDrive is: "%workDrive%"
if "%workDrive%"=="" (
    set /a failed=1
    echo WorkDrive parameter was not set in the project.cfg
)

echo VersionFileLocation is: "%versionFileLocation%"
if "%versionFileLocation%"=="" (
    set /a failed=1
    echo VersionFileLocation parameter was not set in the project.cfg
)

if %failed%==1 (
    endlocal

    echo Failed to package the mod.
    goto:eof
)

for /f "tokens=1-3 delims=." %%a in (%workDrive%%versionFileLocation%) do (
	set majorVersion=%%a
	set minorVersion=%%b
    echo MajorVersion was: %%a
    echo MinorVersion was: %%b
    echo BuildVersion was: %%c
    set /a build=%%c+1
	if !build! GTR 9999 (
		echo MinorVersion was: !minorVersion!
		set /a minorVersion+=1
		echo MinorVersion is: !minorVersion!
		set build=0
	)
    set version=!majorVersion!.!minorVersion!.!build!
    echo BuildVersion is: !build!
)

echo %version%>%workDrive%%versionFileLocation%
echo Version: %version%

endlocal