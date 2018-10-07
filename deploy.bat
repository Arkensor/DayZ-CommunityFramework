@echo off

set workspaceDir=%~1
set gameDir=%~2
set serverDir=%~3
set modName=%~4

set makePBO="C:\Program Files (x86)\Mikero\DePboTools\bin\MakePbo.exe"

echo "Copying to DayZ Client"

RD /s /q "%gameDir%\%modName%" > NUL

echo "Packaging PBO's for DayZ Client"
xcopy /s/e /y /i "%workspaceDir%\%modName%" "%gameDir%\%modName%" > NUL
for /D %%s in ("%gameDir%\%modName%\Addons\*") do (
    %makePBO% -U -P -D -N "%%s" "%%s.pbo" > NUL
    RD /s /q "%%s" > NUL
)

echo "Finished copying to DayZ Client"

echo "Copying to DayZ Server"

RD /s /q "%serverDir%\%modName%" > NUL

echo "Packaging PBO's for DayZ Server"
xcopy /s/e /y /i "%workspaceDir%\%modName%" "%serverDir%\%modName%" > NUL
for /D %%s in ("%serverDir%\%modName%\Addons\*") do (
    %makePBO% -U -P -D -N "%%s" "%%s.pbo" > NUL
    RD /s /q "%%s" > NUL
)

echo "Finished copying to DayZ Server"