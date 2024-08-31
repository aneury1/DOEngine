#!/usr/bin/bash

# cd build ; make
cmake --build build --parallel $(nproc --ignore=1)