#!/usr/bin/bash

# cd build ; make
cmake --build build --parallel $(nproc --ignore=1)

read -rp "Install? [y/N] " ans

if [[ "$ans" =~ ^[Yy]$ ]]; then
    cd build 
    sudo make install
fi