#!/usr/bin/bash
if [ -d "./build" ]; then
    rm -rf "./build"
fi
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S . -B build
