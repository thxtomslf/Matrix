#!/usr/bin/env bash


cd ../

mkdir -p $HOME/.local/bin
cp $(which ls) $HOME/.local/bin/lets-see
echo ::add-path::$HOME/.local/bin
lets-see -a
cpplint --extensions=cpp,h --filter=-whitespace,-readability/casting --linelength=80 matrix/include/* matrix/src/*