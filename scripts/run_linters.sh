#!/usr/bin/env bash


cd ../

echo -e "\n==============cppcheck================"
cppcheck matrix/src --enable=all --inconclusive --error-exitcode=1 \
-I matrix/include --suppress=missingIncludeSystem


echo -e "\n==============cpplint===================="
cpplint --extensions=cpp matrix/include/* matrix/src/*