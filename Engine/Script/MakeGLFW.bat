@echo off

set GLFW_PATH=%THIRD_PARTY_PATH%/glfw

echo Generating glfw...
echo [ glfw ] path : %GLFW_PATH%

cd %GLFW_PATH%
if not exist build mkdir build

rem https://www.glfw.org/docs/latest/compile.html
cmake -S %GLFW_PATH% -B %GLFW_PATH%/build
cmake -S . -B build

echo.
