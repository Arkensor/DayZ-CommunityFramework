@echo off
setlocal enabledelayedexpansion

REM Usage: CI0_SetupFolders <modName>
REM Creates/clears pboNames\<modName> folder, creates Mod\<modName> and Temp\<modName> subfolders, and copies key.

echo CI0_SetupFolders %* running...

set "modName=%~1"

IF "%modName%"=="" (
	echo CI0_SetupFolders - ERROR: modName not given
	exit /B 1
)

IF "%workDrive%"=="" (
	echo CI0_SetupFolders - ERROR: workDrive not set
	exit /B 1
)
IF "%modBuildDirectory%"=="" (
	echo CI0_SetupFolders - ERROR: modBuildDirectory not set
	exit /B 1
)
IF "%keyDirectory%"=="" (
	echo CI0_SetupFolders - ERROR: keyDirectory not set
	exit /B 1
)
IF "%keyName%"=="" (
	echo CI0_SetupFolders - ERROR: keyName not set
	exit /B 1
)

IF NOT exist "%workDrive%Temp\PboNames\%modName%" (
	mkdir "%workDrive%Temp\PboNames\%modName%"
)

IF NOT exist "%modBuildDirectory%%modName%\addons\" (
	echo Creating folder "%modBuildDirectory%%modName%\addons\"
	mkdir "%modBuildDirectory%%modName%\addons\"
)

IF NOT exist "%modBuildDirectory%%modName%\keys\" (
	echo Creating folder "%modBuildDirectory%%modName%\keys\"
	mkdir "%modBuildDirectory%%modName%\keys\"
)

IF NOT exist "%modBuildDirectory%%modName%\addons\" (
	echo CI0_SetupFolders - ERROR: %modBuildDirectory%%modName%\addons\ does not exist
	exit /B 1
)

IF NOT exist "%workDrive%Temp\%modName%\" (
	echo Creating folder "%workDrive%Temp\%modName%\"
	mkdir "%workDrive%Temp\%modName%\"
)

IF NOT exist "%workDrive%Temp\%modName%\addons\" (
	echo Creating folder "%workDrive%Temp\%modName%\addons\"
	mkdir "%workDrive%Temp\%modName%\addons\"
)

echo Copying over "%keyDirectory%%keyName%.bikey" to "%modBuildDirectory%%modName%\keys\"
copy "%keyDirectory%%keyName%.bikey" "%modBuildDirectory%%modName%\keys\"

echo CI0_SetupFolders done

exit /B 0
