#!/bin/bash

cmake -E make_directory build
cmake -E chdir build cmake ..
cmake --build build
cmake -E chdir build ctest
# build/psd-convert
