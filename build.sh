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
  -DCMAKE_INTERPROCEDURAL_OPTIMIZATION=TRUE \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_HOME/scripts/buildsystems/vcpkg.cmake"

cmake --build build

if [ -f "build/CppUserAPI" ]; then
  if [ "$(uname)" = "Darwin" ]; then
    strip build/CppUserAPI
  else
    strip -s --strip-unneeded build/CppUserAPI
  fi
  echo "CppUserAPI is reduced down to tightie whities. Size: $(du -sh build/CppUserAPI | cut -f1)"
fi
