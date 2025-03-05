#!/bin/bash

if [ -z "$1" ]; then
  exit 1
fi



# Compile the C++ file
g++-14 -std=c++23 "$1"

# Check if the compilation was successful
if [ $? -eq 0 ]; then
  ./a.out > output.txt < input.txt
  diff correct_output.txt output.txt
else
  echo "Compilation failed."
  exit 1
fi
