#!/usr/bin/sh

if [ -z "$VCPKG_HOME" ]; then
  VCPKG_HOME="$HOME/vcpkg"
fi

# rm -rf build
# cmake -DCMAKE_BUILD_TYPE=Release -B build
# make -C build


rm -rf build
cmake -B build -S . \
  -DCMAKE_BUILD_TYPE=MinSizeRel \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_HOME/scripts/buildsystems/vcpkg.cmake"

cmake --build build
