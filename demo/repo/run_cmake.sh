#!/bin/bash
# For debug ONLY!/bin/bash -x

set -e

boost_root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/../../libs32/Boost/"
if [ ! -d "$boost_root" ]; then
  echo "Downloading Boost 1.65.1"
  mkdir "$boost_root"
  curl -s -L https://boostorg.jfrog.io/artifactory/main/release/1.65.1/source/boost_1_65_1.tar.gz | \
  tar xzf - -C "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"/../../libs32/Boost/
fi

mkdir -p bin

cd bin

rm -f ./Makefile
rm -f ./cmake_install.cmake
rm -f ./CMakeCache.txt

rm -rf ./CMakeFiles

echo "Start to configure Debugs!"

cmake -G "Unix Makefiles" .. -DCMAKE_BUILD_TYPE="Debug" -DBUILD_SHARED_LIBS=ON -DPLATFORM_TO_BUILD="-m32" 

read -p "Debugs configured! Press Enter to build Debugs..."

cmake --build . --config Debug --target install

read -p "Debugs built! Press Enter to configure Releases..."


rm -f ./Makefile
rm -f ./cmake_install.cmake
rm -f ./CMakeCache.txt

rm -rf ./CMakeFiles/*

cmake -G "Unix Makefiles" .. -DCMAKE_BUILD_TYPE="Release" -DBUILD_SHARED_LIBS=ON -DPLATFORM_TO_BUILD="-m32" 

read -p "Releases configured! Press Enter to build Releases..."

cmake --build . --config Release --target install

read -p "Releases built! Press Enter to clean up the mess..."

rm -r ./install_manifest.txt
rm -r ./cmake_install.cmake
rm -r ./CMakeCache.txt

rm -rf ./CMakeFiles
rm -rf ./Debug
rm -rf ./Release

cd ..

