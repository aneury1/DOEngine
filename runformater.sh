#!/usr/bin/bash
find . -iname '*.h' -o -iname '*.cpp' | xargs --no-run-if-empty clang-format-14 -verbose -i -style=file