#!/usr/bin/env bash


cd ../

echo -e "\n==============cppcheck================"
cppcheck matrix/include --enable=all --inconclusive --error-exitcode=1 \
-I matrix/include --suppress=missingIncludeSystem


echo -e "\n==============clang-tidy================"
clang-tidy matrix/src/* matrix/include/* -warnings-as-errors=* -extra-arg=-std=c++17 -- -I matrix/include


echo -e "\n==============cpplint===================="
cpplint --extensions=cpp matrix/include/* matrix/src/*