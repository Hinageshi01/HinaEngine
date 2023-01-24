@echo off

set GLFW_PATH=%THIRD_PARTY_PATH%/glfw

echo Generating gltf...
echo [ glfw ] path : %GLFW_PATH%

cd %GLFW_PATH%
if not exist build mkdir build

:: https://www.glfw.org/docs/latest/compile.html
cmake -S %GLFW_PATH% -B %GLFW_PATH%/build -D USE_MSVC_RUNTIME_LIBRARY_DLL=OFF
cmake -S . -B build

echo.