#!/usr/bin/bash

set -e

cd ../
ls -a
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./build/matrix/tests/matrix_test

