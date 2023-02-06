@echo off

echo Generating thirdparty...

rem Generate .sln but not compile codes.

rem Set projects as a static lib.
rem Set projects msvc runtime library as /MT and /MTd.

call %SCRIPT_PATH%/MakeGLFW.bat
call %SCRIPT_PATH%/MakeAssimp.bat

rem Use spdlog as a header only lib.
rem call %SCRIPT_PATH%/MakeSpdlog.bat
