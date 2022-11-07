#!/usr/bin/env bash

set -e

cd ../

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./build/matrix/tests/matrix_tests

