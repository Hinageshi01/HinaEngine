@echo off

set GLFW_PATH=%THIRD_PARTY_PATH%/glfw

echo Generating gltf...
echo [ glfw ] path : %GLFW_PATH%

cd %GLFW_PATH%
if not exist build mkdir build

:: Use /MT and /MTd
cmake -S %GLFW_PATH% -B %GLFW_PATH%/build -D USE_MSVC_RUNTIME_LIBRARY_DLL=OFF
cmake -S . -B build

:: Generate .sln but not compile codes.
::cd build
::cmake -D USE_MSVC_RUNTIME_LIBRARY_DLL=OFF -D CMAKE_CONFIGURATION_TYPES="Debug;Release"
::cmake --build . --config Debug
::cmake --build . --config Release

echo.