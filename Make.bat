@echo off

Set ROOT_PATH=%~dp0

call %ROOT_PATH%/Engine/Script/Path.bat
call %ROOT_PATH%/Engine/Script/MakeThirdParty.bat
call %ROOT_PATH%/Engine/Script/MakeEngine.bat

pause
