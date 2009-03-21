#!/bin/bash
pushd build
make
lcov -d test/ -z
./bin/CppSpecTest
lcov -d test/ -c -o coverage/CppSpecTest.info
pushd coverage
genhtml CppSpecTest.info
popd
popd
