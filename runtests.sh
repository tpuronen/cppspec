#!/bin/bash
# Builds CppSpec and runs test measuring coverage
pushd build
make -j3
lcov -d test/ -z
./bin/CppSpecTest
lcov -d test/ -c -o coverage/CppSpecTest.info
pushd coverage
genhtml CppSpecTest.info
popd
popd
