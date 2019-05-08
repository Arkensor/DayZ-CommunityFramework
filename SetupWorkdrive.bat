@echo off

cd /D "%~dp0"

IF NOT exist "P:\JM\" (
	echo Creating folder P:\JM\
	mkdir "P:\JM"
)

IF exist "P:\JM\CF\" (
	echo Removing existing link P:\JM\CF
	rmdir "P:\JM\CF\"
)

echo Creating link P:\JM\CF
mklink /J "P:\JM\CF\" "%cd%\JM\CF\"

echo Done