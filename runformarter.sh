
#!/usr/bin/bash
find . -iname '*.h' -o '*.cpp' | xargs --no-run-if-empty clang-format -verbose -i -style=file -fallback-style=none