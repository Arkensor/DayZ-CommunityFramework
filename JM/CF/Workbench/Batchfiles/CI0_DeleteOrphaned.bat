@echo off
setlocal enabledelayedexpansion

REM Usage: CI0_DeleteOrphaned <pboNamesFoldername> <modName>
REM Deletes all PBOs in <Modfoldername> that are not in <PboNamesFoldername>

set "pboNamesFoldername=%~1"
IF "%pboNamesFoldername%"=="" exit /B 1
set "modName=%~2"
IF "%modName%"=="" exit /B 1

IF "%workDrive%"=="" exit /B 1
IF "%modBuildDirectory%"=="" exit /B 1
IF "%keyName%"=="" exit /B 1

for %%F in ("%modBuildDirectory%%modName%\addons\*.pbo") do (
	IF NOT exist "%workDrive%Temp\PboNames\%pboNamesFoldername%\%%~nxF" (
		echo !date! !time! Deleting orphaned "%%~F"
		del "%%~F"
		IF exist "%%~F.%keyName%.bisign" (
			echo !date! !time! Deleting orphaned "%%~F.%keyName%.bisign"
			del "%%~F.%keyName%.bisign"
		)
	)
)
