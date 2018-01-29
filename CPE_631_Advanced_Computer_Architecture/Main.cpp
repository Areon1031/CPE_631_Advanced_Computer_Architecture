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

#include <iostream>
#include <cstdlib>
using namespace std;

#define TIMING_ANALYSIS 1
#define MAX_VALUE 100.0
#define srand48(s) srand(s)
#define drand48() (((double)rand())/((double)RAND_MAX))

// Method to fill matrix with random values
void fill_matrix(double* matrix, const int dim)
{
  // Error Check
  if (matrix == NULL) return;

  for (int m = 0; m < dim; ++m)
    for (int n = 0; n < dim; ++n)
      matrix[m*dim + n] = drand48()*MAX_VALUE;
}

// Method to easily print matrix
void print_matrix(double* matrix, const int dim_m, const int dim_n)
{
  for (int m = 0; m < dim_m; ++m)
  {
    for (int n = 0; n < dim_n; ++n)
      cout << matrix[m*dim_n + n] << " ";

    cout << endl;
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
    cerr << "Usage: programName matrixSize" << endl;
    exit(EXIT_FAILURE);
  }

  // Get the matrix size
  int m_dim = atoi(argv[1]);

  // Create the matrix
  double* first_matrix = new double[m_dim*m_dim];
  double* second_matrix = new double[m_dim*m_dim];
  double* final_matrix = new double[m_dim*m_dim];

  // Fill the matrix with random values
  fill_matrix(first_matrix, m_dim);
  fill_matrix(second_matrix, m_dim);

#if !TIMING_ANALYSIS
  // Print the matrix
  cout << "First Matrix : \n"; print_matrix(first_matrix, m_dim, m_dim);  cout << endl;
  cout << "Second Matrix: \n"; print_matrix(second_matrix, m_dim, m_dim); cout << endl;
#endif

  // Critical Loop
  square_matrix_mult(first_matrix, second_matrix, final_matrix, m_dim);

#if !TIMING_ANALYSIS
  // Present the results to the user
  cout << "Final Matrix : \n"; print_matrix(final_matrix, m_dim, m_dim); cout << endl;
#endif

  // Clean Up
  delete[] first_matrix;
  delete[] second_matrix;
  delete[] final_matrix;

  cin.ignore();
  return 0;
}