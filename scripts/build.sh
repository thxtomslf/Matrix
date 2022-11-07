#!/usr/bin/bash

set -e

cd ../

mkdir -p build
cd build
cmake ..
cmake --build .