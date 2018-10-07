@echo off

set workspaceDir=%~1
set gameDir=%~2
set serverDir=%~3
set modName=%~4

set profiles=%serverDir%\profiles\Server

taskkill /F /IM DayZ_x64.exe /T
taskkill /F /IM DayZServer_x64.exe /T

TIMEOUT /T 2 /NOBREAK

chdir /c "%workspaceDir%"
CALL deploy.bat "%workspaceDir%" "%gameDir%" "%serverDir%" "%modName%"

chdir /d "%serverDir%"

start DayZServer_x64.exe -config=serverDZ.cfg -port=2302 -profiles=%profiles% -dologs -scriptDebug=true -freezecheck -nosplash -noPause -noBenchmark -adminlog -netlog -cpuCount=4 -mod=%modName%;

TIMEOUT /T 2 /NOBREAK

chdir /d "%gameDir%"

start DayZ_BE.exe -exe DayZ_x64.exe -connect=127.0.0.1 -port=2302 -dologs -scriptDebug=true -freezecheck -nosplash -noPause -noBenchmark -adminlog -netlog -name=COMTester -mod=%modName%