#!/bin/bash

echo Compiling Source
g++ -I/apps/arch/papi-5.4.3/include -lpapi -O3 -o main_cpp Main_papi.cpp
icpc -fast -o main_icc Main_papi.cpp -I/apps/arch/papi-5.4.3/include -lpapi

echo Running g++ version
time ./main_cpp 512  >> g_plus_plus_papi_results.txt
time ./main_cpp 1024 >> g_plus_plus_papi_results.txt
time ./main_cpp 1536 >> g_plus_plus_papi_results.txt
time ./main_cpp 2048 >> g_plus_plus_papi_results.txt

echo Running icc version
time ./main_icc 512  >> icc_papi_results.txt
time ./main_icc 1024 >> icc_papi_results.txt
time ./main_icc 1536 >> icc_papi_results.txt
time ./main_icc 2048 >> icc_papi_results.txt

echo Cleaning Up Binary Files
rm ./*.bin
