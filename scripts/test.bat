@echo off

cmake . -B.build -Ax64 -Ddubu_pack_BUILD_TESTS=ON
cmake --build .build/
cd .build/
ctest .
cd ..