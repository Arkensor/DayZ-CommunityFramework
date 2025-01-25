@echo off
setlocal enabledelayedexpansion

CALL SetupLaunch.bat

set mods=%ModName%

if "%AdditionalSPMods%"=="" (
    echo AdditionalSPMods parameter was not set in the project.cfg, ignoring.
) else (
    set mods=%AdditionalSPMods%;%mods%
)

CALL SetupModList.bat

@echo on
start /D "%gameDirectory%" %clientEXE% %clientLaunchParams% "-mod=%modList%" "-name=%playerName%" "-mission=%SPMission%"
