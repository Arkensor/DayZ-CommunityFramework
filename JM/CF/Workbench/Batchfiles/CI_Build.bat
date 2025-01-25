@echo off
setlocal

set modName=%~n0
set modName=%modName:~3%

set exitCmd=0

:OPTIONS
REM parse command line options
if "%~1"=="" goto MAIN
if /I "%~1"=="exitCmd" (
	echo Command line option exitCmd found - will close host cmd.exe after running
	set exitCmd=1
)
shift /1
goto OPTIONS

:MAIN
if not exist "%~dp0..\Logs" mkdir "%~dp0..\Logs"

where tee > nul 2>&1
if errorlevel 1 (
	REM tee not available, just redirect to logfile
	echo Please wait, working...
	call "%~dp0CI1.bat" %modName% %* > "%~dp0..\Logs\%modName%.log" 2>&1
) else (
	REM tee available
	call "%~dp0CI1.bat" %modName% %* | tee "%~dp0..\Logs\%modName%.log"
)
set exitcode=0
if exist "%~dp0..\Logs\Build.failure" set exitcode=1
if not exist "%~dp0..\Logs\Build.success" set exitcode=1
if %exitCmd%==0 exit /B %exitcode%
exit %exitcode%
