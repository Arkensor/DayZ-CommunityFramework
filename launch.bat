@echo off

set workspaceDir=%~1
set gameDir=%~2
set serverDir=%~3
set modName=%~4

set profiles=%serverDir%\profiles\Server

taskkill /F /IM DayZ_x64.exe /T
taskkill /F /IM DayZServer_x64.exe /T

TIMEOUT /T 1 /NOBREAK

chdir /c "%workspaceDir%"
CALL deploy.bat %1 %2 %3 %4

chdir /d "%serverDir%"

start DayZServer_x64.exe -config=serverDZ.cfg -port=2302 "-profiles=%profiles%" -dologs -adminlog -freezecheck -scriptDebug=true -cpuCount=4 -mod=RPCFramework;%modName%

TIMEOUT /T 2 /NOBREAK

chdir /d "%gameDir%"

start DayZ_BE.exe -exe DayZ_x64.exe -password=abc123 -connect=127.0.0.1 -port=2302 -noPause -noBenchmark -dologs -adminlog -netlog -scriptDebug=true -name=Jacob_Mango -freezecheck -mod=RPCFramework;%modName%

REM start DayZ_BE.exe -exe DayZ_x64.exe -noPause -noBenchmark -dologs -adminlog -netlog -scriptDebug=true -name=Jacob_Mango -freezecheck -mod=RPCFramework;%modName% -mission=.\Missions\%missionName%