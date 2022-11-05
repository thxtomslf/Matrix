#!/usr/bin/env bash


cd ../

export PATH=$PATH:/home/runner/.local/lib
python3 cpplint.py --extensions=cpp,h --filter=-whitespace,-readability/casting --linelength=80 matrix/include/* matrix/src/*