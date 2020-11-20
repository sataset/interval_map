#!/bin/bash

g++-9 $1.cpp -std=c++17 -o $1.o
./$1.o