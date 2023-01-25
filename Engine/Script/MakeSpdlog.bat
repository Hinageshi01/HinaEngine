@echo off

set SPDLOG_PATH=%THIRD_PARTY_PATH%/spdlog

echo Generating spdlog...
echo [ spdlog ] path : %SPDLOG_PATH%

cd %SPDLOG_PATH%
if not exist build mkdir build

rem https://github.com/gabime/spdlog
cmake -S %SPDLOG_PATH% -B %SPDLOG_PATH%/build
cmake -S . -B build

echo.
