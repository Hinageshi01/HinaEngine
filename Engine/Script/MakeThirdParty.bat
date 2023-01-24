@echo off

:: Generate .sln but not compile codes.
:: Set project to static lib.
:: Set project msvc runtime library as /MT or /MTd.

call %SCRIPT_PATH%/MakeGLFW.bat
call %SCRIPT_PATH%/MakeAssimp.bat