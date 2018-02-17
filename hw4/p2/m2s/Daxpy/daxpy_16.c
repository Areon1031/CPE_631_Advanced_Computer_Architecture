// Kyle Ray
// CPE 631 Advanced Computer Architecture
// Homework 4
// Problem 2 (Daxpy Loop)
// February 14, 2018

// Daxpy Loop aX + Y = Z
// X(i) = i
// Y(i) = i/2
// a = 3

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TIMING_ANALYSIS 1
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
    printf("%f ", *(matrix + m));
  }
  printf("\n");
}

void daxpy(double* matrixX, double* matrixY, double* matrixZ, const int dim)
{
  for (int i = 0; i < dim; i=i+16)
  {
    matrixZ[i] = CONST_A*matrixX[i] + matrixY[i];
    matrixZ[i+1] = CONST_A*matrixX[i+1] + matrixY[i+1];
    matrixZ[i+2] = CONST_A*matrixX[i+2] + matrixY[i+2];
    matrixZ[i+3] = CONST_A*matrixX[i+3] + matrixY[i+3];
    matrixZ[i+4] = CONST_A*matrixX[i+4] + matrixY[i+4];
    matrixZ[i+5] = CONST_A*matrixX[i+5] + matrixY[i+5];
    matrixZ[i+6] = CONST_A*matrixX[i+6] + matrixY[i+6];
    matrixZ[i+7] = CONST_A*matrixX[i+7] + matrixY[i+7];
    matrixZ[i+8] = CONST_A*matrixX[i+8] + matrixY[i+8];
    matrixZ[i+9] = CONST_A*matrixX[i+9] + matrixY[i+9];
    matrixZ[i+10] = CONST_A*matrixX[i+10] + matrixY[i+10];
    matrixZ[i+11] = CONST_A*matrixX[i+11] + matrixY[i+11];
    matrixZ[i+12] = CONST_A*matrixX[i+12] + matrixY[i+12];
    matrixZ[i+13] = CONST_A*matrixX[i+13] + matrixY[i+13];
    matrixZ[i+14] = CONST_A*matrixX[i+14] + matrixY[i+14];
    matrixZ[i+15] = CONST_A*matrixX[i+15] + matrixY[i+15];
  }
}

int main(int argc, char* argv[])
{
  // Error Check
  if (argc < 2)
  {
    printf("Usage: programName matrixSize\n");
    exit(1);
  }

  // Get the matrix size
  int m_dim = atoi(argv[1]);

  // Create the matrix
  double* matrixX = (double*)malloc(m_dim * sizeof(double));
  double* matrixY = (double*)malloc(m_dim * sizeof(double));
  double* matrixZ = (double*)malloc(m_dim * sizeof(double));

  // Fill the matrix with random values
  fill_matrix(matrixX, matrixY, m_dim);

#if !TIMING_ANALYSIS
  // Print the matrix
  printf("First Matrix : \n"); print_matrix(matrixX, m_dim);  printf("\n");
  printf("Second Matrix: \n"); print_matrix(matrixY, m_dim);  printf("\n");
#endif

  // Critical Loop
  daxpy(matrixX, matrixY, matrixZ, m_dim);

#if !TIMING_ANALYSIS
  // Present the results to the user
  printf("Final Matrix : \n"); print_matrix(matrixZ, m_dim); printf("\n");
#endif

  // Clean Up
  free(matrixX);
  free(matrixY);
  free(matrixZ);

  return 0;
}
