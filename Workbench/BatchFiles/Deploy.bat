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

set workDrive=
set workbenchDirectory=
set gameDirectory=
set serverDirectory=
set modName=
set modSymlinkDirectory=
set prefixLinkRoot=
set privateKey=
set publicKey=
set modCPP=

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg WorkDrive') do (
	set workDrive=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg GameDirectory') do (
	set gameDirectory=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg ServerDirectory') do (
	set serverDirectory=%%a
)

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg WorkbenchDirectory') do (
    set workbenchDirectory=%%a
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

for /f "delims=" %%a in ('call %batchFileDirectory%ExtractData.bat project.cfg user.cfg ModCPP') do (
	set modCPP=%%a
)

REM @echo on

setlocal enableextensions enabledelayedexpansion

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

echo ModName is: "%modName%"
if "%modName%"=="" (
	set /a failed=1
	echo ModName parameter was not set in the project.cfg
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

echo WorkbenchDirectory is: "%workbenchDirectory%"
if "%workbenchDirectory%"=="" (
    set /a failed=1
    echo WorkbenchDirectory parameter was not set in the project.cfg
)

echo PrefixLinkRoot is: "%prefixLinkRoot%"
if "%prefixLinkRoot%"=="" (
	set /a failed=1
	echo PrefixLinkRoot parameter was not set in the project.cfg
)

echo ModCPP is: "%modCPP%"
if "%modCPP%"=="" (
	set /a failed=1
	echo ModCPP parameter was not set in the project.cfg
)

if %failed%==1 (
	endlocal

	echo Failed to package the mod.

	cd %batchFileDirectory%
	pause
	goto:eof
)

set makePBO=%toolsDirectory%MakePbo.exe
set signFile=%toolsDirectory%DSSignFile.exe

echo "Packaging Addons"

rmdir /S /Q "%modSymlinkDirectory%%modName%\Addons\"

mkdir "%modSymlinkDirectory%%modName%\"
mkdir "%modSymlinkDirectory%%modName%\Addons\"
mkdir "%modSymlinkDirectory%%modName%\Keys\"

copy "%publicKey%" "%modSymlinkDirectory%%modName%\Keys\" > nul
copy "%publicKey%" "%modSymlinkDirectory%%modName%\Keys\" > nul

mklink /J "%workDrive%%prefixLinkRoot%\" "%githubDirectory%%prefixLinkRoot%\"

mklink /J "%gameDirectory%%modName%\" "%modSymlinkDirectory%%modName%\"
mklink /J "%serverDirectory%%modName%\" "%modSymlinkDirectory%%modName%\"
mklink /J "%workbenchDirectory%%modName%\" "%modSymlinkDirectory%%modName%\"

copy "%workDrive%%prefixLinkRoot%\%modCPP%" "%modSymlinkDirectory%%modName%" > nul

@echo off

for /f "tokens=*" %%D in ('dir /b /s "%workDrive%%prefixLinkRoot%\*"') do (
	IF EXIST "%%~fD\config.cpp" (
		IF NOT EXIST "%%~fD\..\config.cpp" (
			IF NOT EXIST "%%~fD\..\..\config.cpp" (
				IF NOT EXIST "%%~fD\..\..\..\config.cpp" (
					IF NOT EXIST "%%~fD\..\..\..\..\config.cpp" (
						IF NOT EXIST "%%~fD\..\..\..\..\..\config.cpp" (
							IF NOT EXIST "%%~fD\..\..\..\..\..\..\config.cpp" (
								set pboName=%%~pnD
								set pboName=!pboName:\%prefixLinkRoot%\=!
								set pboName=!pboName:\=_!

								%makePBO% -U -P -D -N "%%~dpnxD" "%modSymlinkDirectory%%modName%\Addons\!pboName!.pbo"
								%signFile% "%privateKey%" "%modSymlinkDirectory%%modName%\Addons\!pboName!.pbo"
							)
						)
					)
				)
			)
		)
	)
)

endlocal

cd %batchFileDirectory%