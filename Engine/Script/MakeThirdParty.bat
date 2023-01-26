@echo off

echo Generating thirdparty...

rem Generate .sln but not compile codes.
rem Set projects as static lib.

call %SCRIPT_PATH%/MakeGLFW.bat
call %SCRIPT_PATH%/MakeAssimp.bat

rem Use spdlog as header only lib.
rem call %SCRIPT_PATH%/MakeSpdlog.bat
