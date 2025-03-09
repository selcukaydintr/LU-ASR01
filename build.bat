@echo off
setlocal

:: Build dizini oluştur
if not exist build mkdir build
cd build

:: CMake yapılandırması
cmake -G "Visual Studio 17 2022" -A x64 ^
    -DASRPRO_BUILD_TESTS=ON ^
    -DASRPRO_ENABLE_LOGGING=ON ^
    ..

:: Build işlemi
cmake --build . --config Release

:: Testleri çalıştır
ctest -C Release --output-on-failure

cd ..
endlocal