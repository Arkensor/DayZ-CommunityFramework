@echo off
setlocal enableextensions enabledelayedexpansion
set file=%~1
set key=%~2
for /F "usebackq eol=: tokens=1,2* delims==" %%i in ("!file!") do (
    set currkey=%%i
    set currval=%%j
    if "!key!"=="!currkey!" (
        echo !currval!
    )
)
endlocal