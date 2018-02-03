/**
Square Matrix Multiplication

Simple program to accept a matrix dimension from the user
and create and multiple two square matrices filled with
pseudo random numbers.

Edit: Added OpenMP functionality to parallelize the main loop

CPE 631 Advanced Computer Architecture
Kyle Ray
Homework #2
January 31, 2018
*/

#include <iostream>
#include <cstdlib>
using namespace std;

#define TIMING_ANALYSIS 0
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

// Method to multiply Square matrices
void square_matrix_mult(double* first_matrix, double* second_matrix, double* out_matrix, const int dim)
{
  // Critical Loop
  #pragma omp parallel for
  for (int m = 0; m < dim; ++m)
  {
    #pragma omp parallel for
    for (int n = 0; n < dim; ++n)
    {
      double sum = 0.;
      #pragma omp parallel for shared(sum)
      for (int k = 0; k < dim; ++k)
      {
        sum += first_matrix[m*dim + k] * second_matrix[k*dim + n];
      }

      out_matrix[m*dim + n] = sum;
    }
  }
}

// Method to write the contents of a matrix to a binary file
void write_matrix_to_file(double* matrix, const int dim)
{
  // Open the binary file
  FILE* out_file;
  out_file = fopen("MatrixMult.bin", "wb");
  if (!out_file)
  {
    cerr << "Unable to open the file" << endl;
    return;
  }

  // Write the matrix contents to the binary file
  for (int m = 0; m < dim; ++m)
  {
    for (int n = 0; n < dim; ++n)
      fwrite(&matrix[m*dim + n], sizeof(double), 1, out_file);
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

  // Write the result to a binary file
  write_matrix_to_file(final_matrix, m_dim);

  // Clean Up
  delete[] first_matrix;
  delete[] second_matrix;
  delete[] final_matrix;

  cin.ignore();
  return 0;
}