@echo off

set /a failed=0

if exist ../../project.cfg (
    echo Found the project.cfg
    cd ../../
) else (
    if exist project.cfg (
        echo Found the project.cfg
    ) else (
        echo Failed to find the project.cfg file, exitting.
        set /a failed=1
    )
)

if exist ../../user.cfg (
    echo Found the user.cfg
    cd ../../
) else (
    if exist user.cfg (
        echo Found the user.cfg
    ) else (
        echo Failed to find the user.cfg file, exitting.
        set /a failed=1
    )
)

if %failed%==1 (
    endlocal

    echo Failed to package the mod.

    cd %batchFileDirectory%
    goto:eof
)

set githubDirectory=%cd%\
set workbenchDataDirectory=%githubDirectory%Workbench\
set toolsDirectory=%workbenchDataDirectory%Tools\
set batchFileDirectory=%workbenchDataDirectory%BatchFiles\

set /a port=0
set workDrive=
set gameDirectory=
set serverDirectory=
set serverProfileDirectory=
set modName=
set modSymlinkDirectory=
set prefixLinkRoot=
set privateKey=
set publicKey=
set mods=
set mission=
set clientEXE=
set serverEXE=
set clientLaunchParams=
set serverLaunchParams=
set scriptsPrefix=
set guiPrefix=
set password=

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg Port') do (
    set /a port=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg ServerPassword') do (
    set password=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg ScriptsPrefix') do (
    set scriptsPrefix=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg GUIPrefix') do (
    set guiPrefix=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg AdditionalMPMods') do (
    set mods=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg ServerProfileDirectory') do (
    set serverProfileDirectory=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg MPMission') do (
    set mission=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg ClientEXE') do (
    set clientEXE=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg ServerEXE') do (
    set serverEXE=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg ClientLaunchParams') do (
    set clientLaunchParams=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg WorkDrive') do (
    set workDrive=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg GameDirectory') do (
    set gameDirectory=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg ServerDirectory') do (
    set serverDirectory=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg ModName') do (
    set modName=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg ModSymlinkDirectory') do (
    set modSymlinkDirectory=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg PrefixLinkRoot') do (
    set prefixLinkRoot=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg PrivateKey') do (
    set privateKey=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg PublicKey') do (
    set publicKey=%%a
)

setlocal enableextensions enabledelayedexpansion

echo ScriptsPrefix is: "%scriptsPrefix%"
if "%scriptsPrefix%"=="" (
    set /a failed=1
    echo ScriptsPrefix parameter was not set in the project.cfg
)

echo MPMission is: "%mission%"
if "%mission%"=="" (
    set /a failed=1
    echo MPMission parameter was not set in the project.cfg
)

echo GUIPrefix is: "%guiPrefix%"
if "%guiPrefix%"=="" (
    set /a failed=1
    echo GUIPrefix parameter was not set in the project.cfg
)

echo PrivateKey is: "%privateKey%"
if "%privateKey%"=="" (
    set /a failed=1
    echo PrivateKey parameter was not set in the project.cfg
)

echo PublicKey is: "%publicKey%"
if "%publicKey%"=="" (
    set /a failed=1
    echo PublicKey parameter was not set in the project.cfg
)

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

echo ServerProfileDirectory is: "%serverProfileDirectory%"
if "%serverProfileDirectory%"=="" (
    set /a failed=1
    echo ServerProfileDirectory parameter was not set in the project.cfg
)

echo ClientLaunchParams is: "%clientLaunchParams%"
if "%clientLaunchParams%"=="" (
    set /a failed=1
    echo ClientLaunchParams parameter was not set in the project.cfg
)

echo ModName is: "%modName%"
if "%modName%"=="" (
    set /a failed=1
    echo ModName parameter was not set in the project.cfg
)

echo AdditionalMPMods is: "%mods%"
if "%mods%"=="" (
    echo AdditionalMPMods parameter was not set in the project.cfg, ignoring.
    
    set mods=%modName%
) else (
    set mods=%mods%;%modName%
)

echo WorkDrive is: "%workDrive%"
if "%workDrive%"=="" (
    set /a failed=1
    echo WorkDrive parameter was not set in the project.cfg
)

echo ModSymlinkDirectory is: "%modSymlinkDirectory%"
if "%modSymlinkDirectory%"=="" (
    set /a failed=1
    echo ModSymlinkDirectory parameter was not set in the project.cfg
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

echo PrefixLinkRoot is: "%prefixLinkRoot%"
if "%prefixLinkRoot%"=="" (
    set /a failed=1
    echo PrefixLinkRoot parameter was not set in the project.cfg
)

echo Port is: "%port%"
if "%port%"==0 (
    set /a failed=1
    echo Port parameter was not set in the project.cfg
)

echo ServerPassword is: "%password%"
if "%password%"=="" (
    set /a failed=1
    echo ServerPassword parameter was not set in the project.cfg
)

if %failed%==1 (
    endlocal

    echo Failed to package the mod.

    cd %batchFileDirectory%
    pause
    goto:eof
)

CALL %batchFileDirectory%Exit.bat
CALL %batchFileDirectory%UpdateVersion.bat

set makePBO=%toolsDirectory%MakePbo.exe
set signFile=%toolsDirectory%DSSignFile.exe

echo "Packaging Addons"

%makePBO% -B -U -P -D -N "%workDrive%%prefixLinkRoot%\%guiPrefix%" "%modSymlinkDirectory%%modName%\Addons\%guiPrefix%.pbo" 
%signFile% "%privateKey%" "%modSymlinkDirectory%%modName%\Addons\%guiPrefix%.pbo"

%makePBO% -B -U -P -D -N "%workDrive%%prefixLinkRoot%\%scriptsPrefix%" "%modSymlinkDirectory%%modName%\Addons\%scriptsPrefix%.pbo" 
%signFile% "%privateKey%" "%modSymlinkDirectory%%modName%\Addons\%scriptsPrefix%.pbo"

chdir /d "%serverDirectory%"
echo start %serverEXE% %serverLaunchParams% -scrAllowFileWrite -config=serverDZ.cfg -port=%port% "-profiles=%serverProfileDirectory%" "-password=%password%" -dologs -adminlog -freezecheck -scriptDebug=true -cpuCount=4 "-mission=%mission%" "-mod=%mods%"
start %serverEXE% %serverLaunchParams% -scrAllowFileWrite -config=serverDZ.cfg -port=%port% "-profiles=%serverProfileDirectory%" "-password=%password%" -dologs -adminlog -freezecheck -scriptDebug=true -cpuCount=4 "-mission=%mission%" "-mod=%mods%"

TIMEOUT /T 5 /NOBREAK

chdir /d "%gameDirectory%"
echo start %clientEXE% %clientLaunchParams% "-connect=127.0.0.1" "-port=%port%" "-password=%password%" "-mod=%mods%" -dologs -adminlog -freezecheck -scriptDebug=true
start %clientEXE% %clientLaunchParams% "-connect=127.0.0.1" "-port=%port%" "-password=%password%" "-mod=%mods%" -dologs -adminlog -freezecheck -scriptDebug=true