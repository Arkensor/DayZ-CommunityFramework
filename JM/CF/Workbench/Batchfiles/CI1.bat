@echo off
setlocal enableextensions enabledelayedexpansion

REM Call this as CI1.bat [rebuildAll] [skipPboCleanup] [noIgnore]
REM If rebuildAll is given, will rebuild all PBOs, not only changed ones
REM If skipPboCleanup is given when not using rebuildAll, will not remove orphaned PBOs that are no longer part of the build (debug option, don't use in production!)
REM If noIgnore is given, build all PBOs. Presence of IGNORE file will not skip PBO (debug option, don't use in production!)

REM DO NOT CHANGE THESE!
set skipUnchanged=1
set skipPboCleanup=0
set noIgnore=0
set skipEnumSpecialPaths=0

:OPTIONS
REM parse command line options
if "%~1"=="" goto MAIN
if /I "%~1"=="rebuildAll" (
	echo Command line option rebuildAll found - rebuilding all PBOs
	set skipUnchanged=0
)
if /I "%~1"=="skipPboCleanup" (
	echo Command line option skipPboCleanup found - not removing orphaned PBOs
	set skipPboCleanup=1
)
if /I "%~1"=="noIgnore" (
	echo Command line option noIgnore found - building all PBOs without exceptions
	set noIgnore=1
)
shift /1
goto OPTIONS

:MAIN
if exist "%~dp0..\Logs\Build.failure" del "%~dp0..\Logs\Build.failure"
if exist "%~dp0..\Logs\Build.success" del "%~dp0..\Logs\Build.success"

cd /D "%~dp0"

echo %time% > %~dp0..\Logs\Build.tmp

set /a failed=0

if exist ../project.cfg (
	echo Found the project.cfg
) else (
	echo Failed to find the project.cfg file, exitting.
	set /a failed=1
)

if exist ../user.cfg (
	echo Found the user.cfg
) else (
	echo Failed to find the user.cfg file, exitting.
	set /a failed=1
)

if %failed%==1 goto ABORT

set githubDirectory=%cd%\
set workbenchDataDirectory=%githubDirectory%Workbench\
set toolsDirectory=%workbenchDataDirectory%Tools\

set workDrive=
set modName=
set clientModName=
set modBuildDirectory=
set prefixLinkRoot=
set keyDirectory=
set keyName=

if exist "..\project.cfg.bat" del "..\project.cfg.bat"

for /f "usebackq delims=" %%a in ( ../project.cfg ) do (
	echo set %%a>>"..\project.cfg.bat"
)

call "..\project.cfg.bat"

if exist "..\user.cfg.bat" del "..\user.cfg.bat"

for /f "usebackq delims=" %%a in ( ../user.cfg ) do (
	echo set %%a>>"..\user.cfg.bat"
)

call "..\user.cfg.bat"

set modName=%modName%
set clientModName=%modName%

echo KeyDirectory is: "%keyDirectory%"
if "%keyDirectory%"=="" (
	set /a failed=1
	echo KeyDirectory parameter was not set in the project.cfg
)

echo KeyName is: "%keyName%"
if "%keyName%"=="" (
	set /a failed=1
	echo KeyName parameter was not set in the project.cfg
)

echo ModName is: "%modName%"
if "%modName%"=="" (
	set /a failed=1
	echo %modName% parameter was not set in the project.cfg
)

echo WorkDrive is: "%workDrive%"
if "%workDrive%"=="" (
	set /a failed=1
	echo WorkDrive parameter was not set in the project.cfg
)

echo ModBuildDirectory is: "%modBuildDirectory%"
if "%modBuildDirectory%"=="" (
	set /a failed=1
	echo ModBuildDirectory parameter was not set in the project.cfg
)

echo PrefixLinkRoot is: "%prefixLinkRoot%"
if "%prefixLinkRoot%"=="" (
	set /a failed=1
	echo PrefixLinkRoot parameter was not set in the project.cfg
)

if %failed%==1 goto ABORT
echo Searching for DayZ Tools...
for /F "Tokens=2* skip=2" %%A In ('REG QUERY "HKLM\Software\Bohemia Interactive\DayZ\Tools" /v "Path" 2^>nul') do (set "_DAYZTOOLSPATH=%%~B")
if not defined _DAYZTOOLSPATH (
	for /F "Tokens=2* skip=2" %%A In ('REG QUERY "HKCU\Software\Bohemia Interactive\Dayz Tools" /v "Path" 2^>nul') do (set "_DAYZTOOLSPATH=%%~B\Bin")
)
if not defined _DAYZTOOLSPATH (
	echo DayZ Tools was not set in the registry path, trying default.
	set "_DAYZTOOLSPATH=C:\Program Files (x86)\Steam\steamapps\common\DayZ Tools"
) else (
	echo Found. "%_DAYZTOOLSPATH%"
)

IF NOT EXIST "%_DAYZTOOLSPATH%\CfgConvert\CfgConvert.exe" (
	echo "%_DAYZTOOLSPATH%\CfgConvert\CfgConvert.exe" not found
	goto ABORT
)

IF NOT EXIST "%_DAYZTOOLSPATH%\binarize\binarize.exe" (
	echo "%_DAYZTOOLSPATH%\binarize\binarize.exe" not found
	goto ABORT
)

IF NOT EXIST "%_DAYZTOOLSPATH%\DsUtils\DSSignFile.exe" (
	echo "%_DAYZTOOLSPATH%\DsUtils\DSSignFile.exe" not found
	goto ABORT
)


if %skipUnchanged%==1 GOTO SETUPFOLDERS

REM CLEANING UP JUST IN CASE

REM CLIENT PBOS

IF exist "%modBuildDirectory%%modName%\addons" (
	echo Removing folder "%modBuildDirectory%%modName%\addons\"
	del /f /s /q "%modBuildDirectory%%modName%\addons\" > nul
	rmdir /s /q "%modBuildDirectory%%modName%\addons\"
)

IF exist "%modBuildDirectory%%modName%\" (
	echo Removing folder "%modBuildDirectory%%modName%\"
	rmdir /S /Q "%modBuildDirectory%%modName%\"
)

:SETUPFOLDERS

REM CLIENT PBOS
call "%~dp0CI0_SetupFolders.bat" "%modName%"
if errorlevel 1 goto ABORT

echo Packaging %modName% PBOS

cd /D "%workDrive%%prefixLinkRoot%\"

set /a configcpps=0

IF EXIST "%workDrive%Temp\%modName%-configpaths-unfiltered.list" (
	move /Y "%workDrive%Temp\%modName%-configpaths-unfiltered.list" "%workDrive%Temp\%modName%-configpaths-unfiltered-previous.list"
)

echo %date% %time% Getting config paths...
dir /B /S config.cpp > "%workDrive%Temp\%modName%-configpaths-unfiltered.list"
echo %date% %time% ...got config paths

REM Check if config paths changed from previous run
IF EXIST "%workDrive%Temp\%modName%-configpaths-unfiltered-previous.list" (
	fc "%workDrive%Temp\%modName%-configpaths-unfiltered.list" "%workDrive%Temp\%modName%-configpaths-unfiltered-previous.list" > NUL && (
		REM config paths unchanged from previous run, check "special" file paths

		IF EXIST "%workDrive%Temp\%modName%-specialpaths.list" (
			move /Y "%workDrive%Temp\%modName%-specialpaths.list" "%workDrive%Temp\%modName%-specialpaths-previous.list"
		)

		if !skipEnumSpecialPaths!==0 (
			call "%~dp0CI0_EnumSpecialPaths.bat" "%modName%"
		) else (
			copy /Y "%workDrive%Temp\%PrefixLinkRoot%-ALL-specialpaths.list" "%workDrive%Temp\%modName%-specialpaths.list"
		)

		fc "%workDrive%Temp\%modName%-specialpaths.list" "%workDrive%Temp\%modName%-specialpaths-previous.list" > NUL && (
			IF EXIST "%workDrive%Temp\%modName%-configpaths.list" (
				echo !date! !time! Config and "special" file paths unchanged, skipping check
				GOTO build
			)
		)
	)
)

IF EXIST "%workDrive%Temp\%modName%-configpaths.list" del /F "%workDrive%Temp\%modName%-configpaths.list"

echo %date% %time% Checking config paths...
for /F "usebackq delims=" %%D in ( "%workDrive%Temp\%modName%-configpaths-unfiltered.list" ) do (
	call :CHECKCONFIGPATH "%%~D"
)
echo %date% %time% ...checked config paths

IF !configcpps!==0 (
	echo /////////////////////////////////////////////////////////////
	echo %date% %time% ERROR: Found no config.cpp files for %modName% in "%workDrive%%prefixLinkRoot%"
	echo /////////////////////////////////////////////////////////////
	GOTO ABORT
)

echo %date% %time% Found !configcpps! config.cpp files for %modName% in "%workDrive%%prefixLinkRoot%"

GOTO BUILD

:CHECKCONFIGPATH path
REM Build if a FILE with the name <modName> exists next to config.cpp, but NOT if a FOLDER with that name exists
IF EXIST "%~dp1IGNORE" IF %noIgnore%==0 (
	echo PBO set to ignore, skipping %1
	exit /B
)

echo "%~dp1..\..\..\config.cpp"
echo "%~dp1..\..\config.cpp"
echo "%~dp1..\config.cpp"
echo "%date% %time% ERROR: dp1 %~dp1"
echo "%~1">>"%workDrive%Temp\%modName%-configpaths.list"

IF NOT EXIST "%~dp1..\config.cpp" (
	IF NOT EXIST "%~dp1..\..\config.cpp" (
		IF NOT EXIST "%~dp1..\..\..\config.cpp" (
			IF NOT EXIST "%~dp1..\..\..\..\config.cpp" (
				IF NOT EXIST "%~dp1..\..\..\..\..\config.cpp" (
					IF NOT EXIST "%~dp1..\..\..\..\..\..\config.cpp" (
						IF NOT EXIST "%~dp1..\..\..\..\..\..\..\config.cpp" (
							IF NOT EXIST "%~dp1..\..\..\..\..\..\..\..\config.cpp" (
								rem echo No parent config.cpp found, building pbo %1
								set /a configcpps+=1
								echo "%~1">>"%workDrive%Temp\%modName%-configpaths.list"
							)
						)
					)
				)
			)
		)
	)
)
exit /B

:BUILD

IF NOT EXIST "%workDrive%Temp\%modName%-configpaths.list" (
	echo /////////////////////////////////////////////////////////////
	echo %date% %time% ERROR: "%workDrive%Temp\%modName%-configpaths.list" could not be created or was deleted behind our back
	echo /////////////////////////////////////////////////////////////
	GOTO ABORT
)

if not exist "%workDrive%DZ\vehicles\proxies" mkdir "%workDrive%DZ\vehicles\proxies"
if not exist "%workDrive%DZ\vehicles\proxies\bus_cargo.p3d" echo.>"%workDrive%DZ\vehicles\proxies\bus_cargo.p3d"
if not exist "%workDrive%DZ\vehicles\proxies\bus_driver.p3d" echo.>"%workDrive%DZ\vehicles\proxies\bus_driver.p3d"

for /F "usebackq delims=" %%D in ("%workDrive%Temp\%modName%-configpaths.list") do (

	set folderToBuild=%%~pD
	
	set pboName=%%~pD
	IF !pboName:~-1!==\ SET pboName=!pboName:~0,-1!
	set pboName=!pboName:\%prefixLinkRoot%\=!
	set pboName=!pboName:\=_!

	set prefixName=%%~pD
	IF !prefixName:~-1!==\ SET prefixName=!prefixName:~0,-1!
	set prefixName=!prefixName:\%prefixLinkRoot%\=!
	set prefixName=%prefixLinkRoot%\!prefixName!

	set currentFolder=
	for %%I in ( !folderToBuild!\config.cpp\.. ) do (
		set "currentFolder=%%~nxI"
	)

	set filesChanged=0
	CALL :BINARIZE "!prefixName!" %modName%
	IF ERRORLEVEL 2 GOTO ABORT
	IF ERRORLEVEL 1 set filesChanged=1

	CALL :PACK !currentFolder! "!pboName!" "!prefixName!" %modName% !filesChanged!
	IF ERRORLEVEL 1 GOTO ABORT

	REM Check if other build process failed
	IF EXIST "%~dp0*.failure" (
		echo !date! !time! Aborting because other build^(s^) failed before:
		dir /B "%~dp0*.failure"
		goto EXIT
	)

	REM Check if other build process failed
	IF EXIST "%~dp0*.failure" (
		echo !date! !time! Aborting because other build^(s^) failed before:
		dir /B "%~dp0*.failure"
		goto EXIT
	)

	REM Create dummy file so we can later remove orphaned PBOs that are no longer part of the build (if any)
	echo.>"%workDrive%Temp\PboNames\%modName%\!pboName!.pbo"

	if exist "%%~dpD..\CHANGES" copy /Y "%%~dpD..\CHANGES" "%modBuildDirectory%%modName%\CHANGES"
	if exist "%%~dpD..\LICENSE" copy /Y "%%~dpD..\LICENSE" "%modBuildDirectory%%modName%\LICENSE"
	if exist "%%~dpD..\NOTICE.txt" copy /Y "%%~dpD..\NOTICE.txt" "%modBuildDirectory%%modName%\NOTICE.txt"

)

if %skipPboCleanup% NEQ 1 (
	call "%~dp0CI0_DeleteOrphaned.bat" "%modName%" "%modName%"
	IF ERRORLEVEL 1 GOTO ABORT
)

:END
call "%~dp0CI_MakeLowercase.bat" "%modBuildDirectory%%modName%"

echo %time% > "%~dp0..\Logs\Build.success"
echo %date% %time% Successfully packaged %modName%.
goto EXIT

:BINARIZE prefixName modName

setlocal enableextensions enabledelayedexpansion

set "prefixName=%~1"
set modName=%2
set toUpdate=0

IF "%prefixName%"=="%prefixLinkRoot%\languagecore\Core" (
	REM languagecore\Core changed from a filename to a dirname, need to check if we need to do some cleanup
	IF EXIST "%workDrive%Temp\%prefixName%" IF NOT EXIST "%workDrive%Temp\%prefixName%\*" (
		echo Removing file "%workDrive%Temp\%prefixName%"
		del "%workDrive%Temp\%prefixName%"
	)
)

set changes=0
echo %date% %time% Mirroring "%workDrive%%prefixName%" to "%workDrive%Temp\%prefixName%"...
robocopy "%workDrive%%prefixName%" "%workDrive%Temp\%prefixName%" /MIR /XF *.bak /XF *.png /XF *.psd /XF *.tif /XF *.log /XD source /XF *.tga /XF *.bat /XF *.cmd /XF *.pbo /XF *.bisign /XF *.blend? /NDL /NP /NJH /NJS
IF ERRORLEVEL 8 (
	REM Copy error

	echo /////////////////////////////////////////////////////////////
	echo %date% %time% RoboCopy could not mirror "%workDrive%%prefixName%" to "%workDrive%Temp\%prefixName%"
	echo /////////////////////////////////////////////////////////////

	endlocal
	exit /B 2
)
IF ERRORLEVEL 1 set changes=1
REM When (re-)creating a missing PBO, we need to create config.bin
IF NOT EXIST "%modBuildDirectory%%modName%\addons\%pboName%.pbo" set changes=1
if %changes%==1 (
	REM Files changed/copied
	echo %date% %time% Changes in "%workDrive%Temp\%prefixName%"

	set toUpdate=%clientModName%
)
IF "%toUpdate%"=="0" (
	robocopy "%workDrive%Temp\%prefixName%" "%workDrive%Temp\BinarizeCache\%clientModName%\%prefixName%" *.p3d *.wrp /L /S /XC /XN /XO > nul 2>&1 || (
		echo %date% %time% Binarized client files missing, will regenerate them

		set toUpdate=%clientModName%
	)
)
IF "%toUpdate%" NEQ "0" (
	set failed=0
	REM Rapify
	echo !date! !time! Binarizing "%workDrive%Temp\%prefixName%\config.cpp"
	pushd %workDrive%
	for /R "%workDrive%Temp\%prefixName%" %%a in (*.cpp) do (
		"%_DAYZTOOLSPATH%\CfgConvert\CfgConvert.exe" -bin -dst "%%~dpna.bin" "%%~a" 2>&1
	)
	IF ERRORLEVEL 1 set failed=1
	IF NOT EXIST "%workDrive%Temp\%prefixName%\config.bin" set failed=1
	REM Delete config.cpp so Binarize doesn't choke on it (it'll use config.bin just fine)
	REM This is also necessary to make skipUnchanged work correctly
	echo !date! !time! Deleting temp "%workDrive%Temp\%prefixName%\config.cpp"
	del "%workDrive%Temp\%prefixName%\config.cpp"
	popd
	IF !failed!==1 (
		echo /////////////////////////////////////////////////////////////
		echo !date! !time! Rapify failed on "%workDrive%Temp\%prefixName%\config.cpp"
		echo /////////////////////////////////////////////////////////////

		endlocal
		exit /B 2
	)
	for %%a in (%toUpdate%) do (
		IF EXIST "%workDrive%Temp\BinarizeCache\%%a\%prefixName%" (
			echo !date! !time! Deleting outdated *.p3d and *.wrp in "%workDrive%Temp\BinarizeCache\%%a\%prefixName%"...
			del /f /s /q "%workDrive%Temp\BinarizeCache\%%a\%prefixName%\*.p3d"
			del /f /s /q "%workDrive%Temp\BinarizeCache\%%a\%prefixName%\*.wrp"
		) else (
			mkdir "%workDrive%Temp\BinarizeCache\%%a\%prefixName%"
		)
		REM Create directory structure only
		robocopy "%workDrive%Temp\%prefixName%" "%workDrive%Temp\BinarizeCache\%%a\%prefixName%" *.p3d *.wrp /MIR /XF * > nul 2>&1
		REM Binarize p3d and wrp
		pushd %workDrive%
		if %%a==%clientModName% (
			echo !date! !time! Binarizing *.p3d and *.wrp from "%workDrive%Temp\%prefixName%" to "%workDrive%Temp\BinarizeCache\%clientModName%\%prefixName%"...

			"%_DAYZTOOLSPATH%\binarize\binarize.exe" -targetBonesInterval=56 -textures=%workDrive%Temp -binPath=%workDrive% "%workDrive%Temp\%prefixName%" "%workDrive%Temp\BinarizeCache\%clientModName%\%prefixName%"
			IF ERRORLEVEL 1 set failed=1
		)
		popd
		IF !failed!==1 (
			echo /////////////////////////////////////////////////////////////
			echo !date! !time! Something went wrong with %prefixName% during binarizing
			echo /////////////////////////////////////////////////////////////

			endlocal
			exit /B 2
		)
	)
	REM Restore config.cpp
	echo !date! !time! Restoring "%workDrive%Temp\%prefixName%\config.cpp"
	copy "%workDrive%%prefixName%\config.cpp" "%workDrive%Temp\%prefixName%\config.cpp"
	endlocal
	exit /B 1
)
endlocal
exit /B 0
REM End :BINARIZE

:PACK currentFolder pboName prefixName modName filesChanged

setlocal enableextensions enabledelayedexpansion

set "currentFolder=%~1"
set "pboName=%~2"
set "prefixName=%~3"
set modName=%4
set filesChanged=%5

IF %filesChanged%==0 IF %skipUnchanged%==1 (
	REM Recover from earlier move failures
	IF EXIST "%workDrive%Temp\%modName%\addons\%pboName%.pbo" (
		set filesChanged=1
		GOTO MOVEPACKED
	)

	REM Check if PBO already exists
	IF EXIST "%modBuildDirectory%%modName%\addons\%pboName%.pbo" (
		IF EXIST "%modBuildDirectory%%modName%\addons\%pboName%.pbo.%keyName%.bisign" (
			REM Nothing to do
			echo !date! !time! No change in "%workDrive%Temp\%prefixName%", nothing to do for "%modBuildDirectory%%modName%\addons\%pboName%.pbo"
		) else (
			set filesChanged=1
			CALL :SIGN %modName% "%pboName%"
		)
		goto ENDPACK
	)
	set filesChanged=1
)

set binarizeCache=0
dir /S "%workDrive%Temp\BinarizeCache\%modName%\%prefixName%\*.p3d" > nul 2>&1 && set binarizeCache=1
IF %binarizeCache%==0 (
	dir /S "%workDrive%Temp\BinarizeCache\%modName%\%prefixName%\*.wrp" > nul 2>&1 && set binarizeCache=1
)
IF %binarizeCache%==1 (
	echo !date! !time! Copying any cached binarized *.p3d and *.wrp from "%workDrive%Temp\BinarizeCache\%modName%\%prefixName%" to "%workDrive%Temp\%prefixName%"...
	robocopy "%workDrive%Temp\BinarizeCache\%modName%\%prefixName%" "%workDrive%Temp\%prefixName%" *.p3d *.wrp /S /NDL /NP /NJH /NJS
	IF ERRORLEVEL 8 (
		REM Copy error

		echo /////////////////////////////////////////////////////////////
		echo !date! !time! RoboCopy could not copy *.p3d or *.wrp from "%workDrive%Temp\BinarizeCache\%modName%\%prefixName%" to "%workDrive%Temp\%prefixName%"
		echo /////////////////////////////////////////////////////////////

		endlocal
		exit /B 1
	)
)

set "pboPrefix=!prefixName!"

if exist "%workDrive%%prefixName%\PREFIX.txt" (
	set /p pboPrefix=<"%workDrive%%prefixName%\PREFIX.txt"
) else (
	REM Special case for PBOs that should be loaded before all other mods
	IF "!pboName:~0,2!"=="0_" set "pboPrefix=!pboPrefix:%prefixLinkRoot%\0_=0_%prefixLinkRoot%_!"
)

echo %date% %time% PREFIX: %pboPrefix%

echo %date% %time% Creating "%workDrive%Temp\%modName%\addons\%pboName%.pbo"...
set failed=0

"%_DAYZTOOLSPATH%\PboUtils\FileBank.exe" -exclude "%~dp0..\excludes.lst" -property prefix=%pboPrefix% -dst "%workDrive%Temp\%modName%\addons" "%workDrive%Temp\%prefixName%" 2>&1
IF NOT ERRORLEVEL 1 move /Y "%workDrive%Temp\%modName%\addons\%currentFolder%.pbo" "%workDrive%Temp\%modName%\addons\%pboName%.pbo"

IF ERRORLEVEL 1 (
	set failed=1

	echo /////////////////////////////////////////////////////////////
	echo %date% %time% Something went wrong with packing %pboName%.pbo for %modName%
	echo /////////////////////////////////////////////////////////////

	IF EXIST "%workDrive%Temp\%prefixName%\config.cpp" (
		REM So we detect changes again on next build attempt
		echo %date% %time% Deleting temp "%workDrive%Temp\%prefixName%\config.cpp"
		del "%workDrive%Temp\%prefixName%\config.cpp"
	)
)

IF EXIST "%workDrive%Temp\%prefixName%\config.bin" (
	REM This is necessary to make skipping binarization in case of no changes work
	set delcfgbin=1
	if !delcfgbin!==1 (
		echo %date% %time% Deleting temp "%workDrive%Temp\%prefixName%\config.bin"
		del "%workDrive%Temp\%prefixName%\config.bin"
	)
)

if %binarizeCache%==1 (
	REM This is necessary to make skipping binarization in case of no changes work
	echo %date% %time% Restoring any original *.p3d and *.wrp from "%workDrive%%prefixName%" to "%workDrive%Temp\%prefixName%"...
	robocopy "%workDrive%%prefixName%" "%workDrive%Temp\%prefixName%" *.p3d *.wrp /S /NDL /NP /NJH /NJS
)

IF EXIST "%workDrive%%prefixName%\stringtable.csv" (
	REM This is necessary to make skipping packing in case of no changes work
	echo %date% %time% Restoring original stringtable.csv from "%workDrive%%prefixName%" to "%workDrive%Temp\%prefixName%"...
	copy /Y "%workDrive%%prefixName%\stringtable.csv" "%workDrive%Temp\%prefixName%\stringtable.csv"
)

IF %failed%==1 (
	endlocal
	exit /B 1
)

IF NOT EXIST "%workDrive%Temp\%modName%\addons\%pboName%.pbo" (
	echo /////////////////////////////////////////////////////////////
	echo %date% %time% Something went wrong with %pboName%.pbo for %modName%, "%workDrive%Temp\%modName%\addons\%pboName%.pbo" doesn't exist
	echo /////////////////////////////////////////////////////////////

	endlocal
	exit /B 1
)

:MOVEPACKED
echo Moving "%workDrive%Temp\%modName%\addons\%pboName%.pbo" to "%modBuildDirectory%%modName%\addons\"
move /Y "%workDrive%Temp\%modName%\addons\%pboName%.pbo" "%modBuildDirectory%%modName%\addons\"
IF ERRORLEVEL 1 (
	echo /////////////////////////////////////////////////////////////
	echo %date% %time% Something went wrong with %pboName%.pbo for %modName%, it could not be moved to "%modBuildDirectory%%modName%\addons\"
	echo /////////////////////////////////////////////////////////////

	endlocal
	exit /B 1
)

CALL :SIGN %modName% "%pboName%"

:ENDPACK
set deploy=!filesChanged!
if "%modName%" NEQ "%clientModName%" goto EXITPACK
if !deploy! NEQ 0 (
	echo !date! !time! > "%~dp0..\Logs\Build.deploy"
)
:EXITPACK
endlocal
exit /B 0
REM End :PACK

:LINKERROR fileName modName destFolder
setlocal enableextensions enabledelayedexpansion
set "fileName=%~1"
set modName=%2
set "destFolder=%~3"
echo /////////////////////////////////////////////////////////////
echo %date% %time% Something went wrong with %fileName% for %modName%, it could not be hardlinked to "%destFolder%%fileName%"
echo /////////////////////////////////////////////////////////////
endlocal
exit /B 1

:SIGN

setlocal enableextensions enabledelayedexpansion

set modName=%1
set "pboName=%~2"

if "%modName%"=="%clientModName%" (
	echo %date% %time% Signing "%modBuildDirectory%%modName%\addons\%pboName%.pbo"
	"%_DAYZTOOLSPATH%\DsUtils\DSSignFile.exe" "%keyDirectory%%keyName%.biprivatekey" "%modBuildDirectory%%modName%\addons\%pboName%.pbo"
)
exit /B
REM End :SIGN

:EXIT
del "%~dp0..\Logs\Build.tmp"
endlocal
exit /B 0

:ABORT
echo %time% > "%~dp0..\Logs\Build.failure"
del "%~dp0..\Logs\Build.tmp"
echo %date% %time% Failed to package %modName%.
endlocal
exit /B 1