#!/bin/bash

set -e
set -x

rm -rf build
mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release -G Ninja
cmake --build .