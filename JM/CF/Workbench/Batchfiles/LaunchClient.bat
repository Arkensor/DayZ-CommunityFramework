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
start /D "%gameDirectory%" %clientEXE% %clientLaunchParams% "-mod=%modList%" "-name=%playerName%"
