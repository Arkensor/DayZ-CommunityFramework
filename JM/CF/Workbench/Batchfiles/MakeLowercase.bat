@echo off

REM Make folder names lowercase
rename "%~1\Addons" "addons"
rename "%~1\Keys" "keys"

REM Make PBO names lowercase
if exist "%~1\addons\*.pbo" for /f "Tokens=*" %%f in ('dir /l/b/a-d "%~1\addons"') do (
	rename "%~1\addons\%%f" "%%f"
)
