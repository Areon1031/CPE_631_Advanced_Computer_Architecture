#!/bin/bash

echo Compiling Source
g++ -O3 -o main_omp_cpp Main_omp.cpp -fopenmp
icpc -qopenmp -fast -o main_omp_icc Main_omp.cpp

echo Running g++ version
time ./main_omp_cpp 512  >> g_plus_plus_omp_results.txt
time ./main_omp_cpp 1024 >> g_plus_plus_omp_results.txt
time ./main_omp_cpp 1536 >> g_plus_plus_omp_results.txt
time ./main_omp_cpp 2048 >> g_plus_plus_omp_results.txt

echo Running icc version
time ./main_omp_icc 512  >> icc_omp_results.txt
time ./main_omp_icc 1024 >> icc_omp_results.txt
time ./main_omp_icc 1536 >> icc_omp_results.txt
time ./main_omp_icc 2048 >> icc_omp_results.txt

echo Cleaning Up Binary Files
rm ./*.bin
