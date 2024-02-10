@echo off
setlocal enabledelayedexpansion

CALL SetupLaunch.bat

set mods=%ModName%

if "%AdditionalMPMods%"=="" (
    echo AdditionalMPMods parameter was not set in the project.cfg, ignoring.
) else (
    set mods=%AdditionalMPMods%;%mods%
)

CALL SetupModList.bat

@echo on
start /D "%serverDirectory%" %serverEXE% %serverLaunchParams% "-config=%serverConfig%" "%port%" "-profiles=%serverProfileDirectory%" "-mission=%MPMission%" "-mod=%modList%"
@echo off

TIMEOUT /T 1 /NOBREAK

@echo on
start /D "%gameDirectory%" %clientEXE% %clientLaunchParams% "-connect=127.0.0.1" "%port%" "-name=%playerName%" "%password%" "-mod=%modList%"
