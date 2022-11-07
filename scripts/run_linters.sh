#!/usr/bin/bash


cd ../

echo -e "\n==============cppcheck================"
cppcheck matrix --enable=all --inconclusive --error-exitcode=1 \
-I matrix/include --suppress=missingIncludeSystem


echo -e "\n==============clang-tidy================"
clang-tidy matrix/src/* matrix/include/* -warnings-as-errors=* -extra-arg=-std=c++17 -- -Iclient/include


echo -e "\n==============cpplint===================="
cpplint --extensions=cpp client/include/* matrix/src/*