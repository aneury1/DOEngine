#!/usr/bin/bash

tests_project_name=Doengine_tests
project_name=DOENGINE

cmake -DDOENGINE_COVERAGE=TRUE -DDOENGINE_TESTS=TRUE -DCMAKE_BUILD_TYPE=Debug -S . -B build
# cmake --build build/ --config Debug --target $project_name
cmake --build build/ --config Debug --parallel $(nproc --ignore=1) --target $tests_project_name
pushd build/src/test
ctest -j3
popd
cmake --build build/ --config Debug --parallel $(nproc --ignore=1) --target "${tests_project_name}_cov"