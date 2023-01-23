@echo off

set GLFW_PATH=%THIRD_PARTY_PATH%/glfw

echo Generating gltf...
echo [ glfw ] path : %GLFW_PATH%

cd %GLFW_PATH%
if not exist build mkdir build
cd build
cmake .. -D CMAKE_CONFIGURATION_TYPES="Debug;Release"
cmake --build . --config Debug
cmake --build . --config Release
echo.