#!/usr/bin/env bash


cd ../
cd ../../..
ls -a
python3 cpplint.py --extensions=cpp,h --filter=-whitespace,-readability/casting --linelength=80 matrix/include/* matrix/src/*