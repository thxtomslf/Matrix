#!/usr/bin/env bash


cd ../

cpplint --extensions=cpp,h --filter=-whitespace,-readability/casting --linelength=80 matrix/include/* matrix/src/*