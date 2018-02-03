/**
Square Matrix Multiplication

Simple program to accept a matrix dimension from the user
and create and multiple two square matrices filled with
pseudo random numbers.

CPE 631 Advanced Computer Architecture
Kyle Ray
Homework #2
January 31, 2018
*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define TIMING_ANALYSIS 0
//#define MAX_VALUE 100
//#define srand48(s) srand(s)
//#define drand48() (((double)rand())/((double)RAND_MAX))

// Method to fill matrix with random values
void fill_matrix(double* matrix, const int dim)
{
  // Error Check
  if (matrix == NULL) return;

  for (int m = 0; m < dim; ++m)
    for (int n = 0; n < dim; ++n)
    {
      srand(n*m);
      int test = rand();
      printf("%d", test);
      matrix[m*dim + n] = rand();
    }
}

// Method to easily print matrix
void print_matrix(double* matrix, const int dim_m, const int dim_n)
{
  for (int m = 0; m < dim_m; ++m)
  {
    for (int n = 0; n < dim_n; ++n)
      printf("%d ", matrix[m*dim_n + n]);

    printf("\n");
  }
}

// Method to multiple Square matrices
void square_matrix_mult(double* first_matrix, double* second_matrix, double* out_matrix, const int dim)
{
  for (int m = 0; m < dim; ++m)
  {
    for (int n = 0; n < dim; ++n)
    {
      double sum = 0.;
      for (int k = 0; k < dim; ++k)
      {
        sum += first_matrix[m*dim + k] * second_matrix[k*dim + n];
      }

      out_matrix[m*dim + n] = sum;
    }
  }
}

int main(int argc, char* argv[])
{
  // Error Check
  if (argc < 2)
  {
    printf("Usage: programName matrixSize\n");
    return 1;
  }

  // Seed the random number generator
  srand(time(NULL));

  // Get the matrix size
  int m_dim = atoi(argv[1]);

  // Create the matrix 
  double* first_matrix  = malloc((m_dim*m_dim) * sizeof(double));
  double* second_matrix = malloc((m_dim*m_dim) * sizeof(double));
  double* final_matrix  = malloc((m_dim*m_dim) * sizeof(double));

  // Fill the matrix with random values
  fill_matrix(first_matrix, m_dim);
  fill_matrix(second_matrix, m_dim);

#if !TIMING_ANALYSIS
  // Print the matrix
  printf("First Matrix : \n"); print_matrix(first_matrix, m_dim, m_dim);  printf("\n");
  printf("Second Matrix: \n"); print_matrix(second_matrix, m_dim, m_dim); printf("\n");
#endif

  // Critical Loop
  square_matrix_mult(first_matrix, second_matrix, final_matrix, m_dim);

#if !TIMING_ANALYSIS
  // Present the results to the user
  printf("Final Matrix : \n"); print_matrix(final_matrix, m_dim, m_dim); printf("\n");
#endif

  // Clean Up
  free(first_matrix);
  free(second_matrix);
  free(final_matrix);

  printf("Press Enter");
  int dummy;
  scanf_s("%d", &dummy);

  return 0;
}