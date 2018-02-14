// Kyle Ray
// CPE 631 Advanced Computer Architecture
// Homework 4
// Problem 2 (Daxpy Loop)
// February 14, 2018

// Daxpy Loop aX + Y = Z
// X(i) = i
// Y(i) = i/2
// a = 3

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
using namespace std;

#define TIMING_ANALYSIS 0
#define CONST_A 3.0

// Method to fill matrix with random values
void fill_matrix(double* matrixX, double* matrixY, const int dim)
{
  // Error Check
  if (matrixX == NULL || matrixY == NULL) return;

  // Fill the matrices
  for (int i = 0; i < dim; i++)
  {
    matrixX[i] = i + 1;
    matrixY[i] = (double)(i + 1) / 2;
  }
  
}

// Method to easily print matrix
void print_matrix(double* matrix, const int dim)
{
  for (int m = 0; m < dim; ++m)
  {
    cout << matrix[m] << " ";
  }
  cout << endl;
}

void daxpy(double* matrixX, double* matrixY, double* matrixZ, const int dim)
{
  for (int i = 0; i < dim; i++)
  {
    matrixZ[i] = CONST_A*matrixX[i] + matrixY[i];
  }
}

int main(int argc, char* argv[])
{
  // Error Check
  if (argc < 2)
  {
    cerr << "Usage: programName matrixSize" << endl;
    exit(EXIT_FAILURE);
  }

  // Get the matrix size
  int m_dim = atoi(argv[1]);

  // Create the matrix
  double* matrixX = new double[m_dim];
  double* matrixY = new double[m_dim];
  double* matrixZ = new double[m_dim];

  // Fill the matrix with random values
  fill_matrix(matrixX, matrixY,  m_dim);

#if !TIMING_ANALYSIS
  // Print the matrix
  cout << "First Matrix : \n"; print_matrix(matrixX, m_dim);  cout << endl;
  cout << "Second Matrix: \n"; print_matrix(matrixY, m_dim);  cout << endl;
#endif

#if TIMING_ANALYSIS 
  // Setup Clock
  clock_t start_time, finish_time;
  start_time = clock();
  finish_time = clock();
  double delay_time = (double)(finish_time - start_time);
  start_time = clock();
#endif

  // Critical Loop
  daxpy(matrixX, matrixY, matrixZ, m_dim);

#if TIMING_ANALYSIS
  finish_time = clock();
  double elapsed_time = finish_time - start_time - delay_time;
  double elapsed_time_sec = elapsed_time / CLOCKS_PER_SEC;
  cout << "Time for the critical loop is " << elapsed_time_sec << " seconds." << endl;
#endif

#if !TIMING_ANALYSIS
  // Present the results to the user
  cout << "Final Matrix : \n"; print_matrix(matrixZ, m_dim); cout << endl;
#endif

  cin.ignore();

  // Clean Up
  delete[] matrixX;
  delete[] matrixY;
  delete[] matrixZ;

  return 0;
}
