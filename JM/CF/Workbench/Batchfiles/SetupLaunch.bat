if exist "%~dp0..\project.cfg" (
	echo Found the project.cfg
) else (
	echo Failed to find the project.cfg file, exitting.
	exit /b 1
)

if exist "%~dp0..\user.cfg" (
	echo Found the user.cfg
) else (
	echo Failed to find the user.cfg file, exitting.
	exit /b 1
)

set failed=0

if exist "%~dp0..\project.cfg.%~n0.bat" del "%~dp0..\project.cfg.%~n0.bat"

for /f "usebackq delims=" %%a in ( "%~dp0..\project.cfg" ) do (
	echo set %%a>>"%~dp0..\project.cfg.%~n0.bat"
)

call "%~dp0..\project.cfg.%~n0.bat"

if exist "%~dp0..\user.cfg.%~n0.bat" del "%~dp0..\user.cfg.%~n0.bat"

for /f "usebackq delims=" %%a in ( "%~dp0..\user.cfg" ) do (
	echo set %%a>>"%~dp0..\user.cfg.%~n0.bat"
)

call "%~dp0..\user.cfg.%~n0.bat"

echo ClientLaunchParams is: "%clientLaunchParams%"

echo ServerLaunchParams is: "%serverLaunchParams%"

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

echo SPMission is: "%SPMission%"
if "%SPMission%"=="" (
    set /a failed=1
    echo SPMission parameter was not set in the project.cfg
)

echo MPMission is: "%MPMission%"
if "%MPMission%"=="" (
    set /a failed=1
    echo SPMission parameter was not set in the project.cfg
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

echo AdditionalSPMods is: "%AdditionalSPMods%"

echo AdditionalMPMods is: "%AdditionalMPMods%"

echo PlayerName is: "%playerName%"

if %failed%==1 exit /b 1

CALL Exit.bat
