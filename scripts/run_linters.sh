#!/usr/bin/env bash


cd ../

export PATH=$PATH:~/.local/bin/
cpplint --extensions=cpp,h --filter=-whitespace,-readability/casting --linelength=80 matrix/include/* matrix/src/*