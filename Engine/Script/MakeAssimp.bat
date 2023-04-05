@echo off

set ASSIMP_PATH=%THIRD_PARTY_PATH%/assimp

echo Generating assimp...
echo [ assimp ] path: %ASSIMP_PATH%

cd %ASSIMP_PATH%
if not exist build mkdir build

rem https://github.com/assimp/assimp/blob/master/Build.md#cmake-build-options
cmake -S %ASSIMP_PATH% -B %ASSIMP_PATH%/build -D ASSIMP_BUILD_TESTS=OFF -D BUILD_SHARED_LIBS=OFF -D USE_STATIC_CRT=ON -D ASSIMP_NO_EXPORT=ON
cmake -S . -B build

echo.
