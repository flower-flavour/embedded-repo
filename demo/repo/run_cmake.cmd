:: hard-coded exact PATH to exclude sh-path from it. sh.exe is in the PATH of my PC and 'cmake' hates sh.exe in its PATH!

@echo off

@mkdir bin
cd bin

del /Q src\Makefile >> nul 2>&1
del /Q src\cmake_install.cmake >> nul 2>&1
del /Q src\CMakeCache.txt >> nul 2>&1

del /Q /S Makefile >> nul 2>&1
del /Q /S cmake_install.cmake >> nul 2>&1
del /Q /S CMakeCache.txt >> nul 2>&1
del /Q /S install_manifest.txt >> nul 2>&1

rd /S /Q CMakeFiles >> nul 2>&1

:: cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE="Release"
:: generate Makefile for ./CMakeList.txt as Debug and use the path to current directory as CMAKE_INSTALL_PREFIX!
:: CMAKE_INSTALL_PREFIX="." does not force make to install build inside "."!
:: seems make ignores CMAKE_INSTALL_PREFIX!
:: -DBUILD_STATIC_LIBS=ON
cmake -G "MinGW Makefiles" .. -DCMAKE_BUILD_TYPE="Debug" -DBUILD_SHARED_LIBS=ON -DPLATFORM_TO_BUILD="-m32"
:: DON'T SPECIFY CURRENT DIR AS INSTALL LOCATION: -DCMAKE_INSTALL_PREFIX="." <-- BULD WILL BE IN CURRENT DIR!

:: -DCMAKE_SOURCE_DIR="."
:: -DCMAKE_BINARY_DIR="./bin" 
:: build project as as Debug and install it according to CMAKE_INSTALL_PREFIX="."!
cmake --build . --config Debug --target install

echo "Debug built!"

pause

:: goto CLEAN_AND_END


 cmake -G "MinGW Makefiles" .. -DCMAKE_BUILD_TYPE="Release" -DBUILD_SHARED_LIBS=ON -DPLATFORM_TO_BUILD="-m32"

:: DON'T SPECIFY CURRENT DIR AS INSTALL LOCATION: -DCMAKE_INSTALL_PREFIX="." <-- BULD WILL BE IN CURRENT DIR!

 cmake --build . --config Release --target install

echo "Release built!"

::pause

:CLEAN_AND_END

:: delete import library
del /Q *.a                     >> nul 2>&1
del /Q *.lib                   >> nul 2>&1
:: delete dynamic link library
del /Q lib*.dll                >> nul 2>&1
del /Q *.dll                   >> nul 2>&1
:: delete tmp exe 
del /Q *.exe                   >> nul 2>&1

del /Q /S Makefile             >> nul 2>&1
del /Q /S cmake_install.cmake  >> nul 2>&1
del /Q /S CMakeCache.txt       >> nul 2>&1
del /Q /S install_manifest.txt >> nul 2>&1
del /Q /S *.dll.a              >> nul 2>&1

rd /S /Q CMakeFiles            >> nul 2>&1

cd ..

pause
