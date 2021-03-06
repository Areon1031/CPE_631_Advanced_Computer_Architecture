// Kyle Ray
// CPE 631 Advanced Computer Architecture
// Homework 4
// Problem 2 (Daxpy Loop)
// February 14, 2018

// Daxpy Loop aX + Y = Z
// X(i) = i
// Y(i) = i/2
// a = 3

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

  char key[1];
  puts("Press any key to continue...");
  getchar();

  return 0;
}
