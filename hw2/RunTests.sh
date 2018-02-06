#!/bin/bash

echo Compiling Source
g++ -O3 -o main_cpp Main.cpp
icc -fast -o main_icc Main.cpp

echo Running g++ version
time ./main_cpp 512  >> g_plus_plus_results.txt
time ./main_cpp 1024 >> g_plus_plus_results.txt
time ./main_cpp 1536 >> g_plus_plus_results.txt
time ./main_cpp 2048 >> g_plus_plus_results.txt

echo Running icc version
time ./main_icc 512  >> icc_results.txt
time ./main_icc 1024 >> icc_results.txt
time ./main_icc 1536 >> icc_results.txt
time ./main_icc 2048 >> icc_results.txt

echo Cleaning Up Binary Files
rm ./*.bin
