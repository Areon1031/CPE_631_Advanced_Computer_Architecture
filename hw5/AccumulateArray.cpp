
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <string.h>
#include <time.h>
using namespace std;

// Defines so that I can compile the code in visual studio
//#define srand48(s) srand(s
//#define drand48() (((double)rand())/((double)RAND_MAX)

#define MX_SZ 320
#define SEED 2397           /* random number seed */
#define MAX_VALUE  100.0    /* maximum size of array elements A, and B */

#define TIMING_ANALYSIS 1   // Don't use I/O!

/*
Routine to retrieve the data size of the numbers array from the
command line or by prompting the user for the information
*/
void get_index_size(int argc, char *argv[], int *dim_l) {
  if (argc != 2 && argc != 4) {
    cout << "usage:  mm_mult_serial [l_dimension]"
      << endl;
    exit(1);
  }
  else {
    if (argc == 2) {
      *dim_l = atoi(argv[1]);
    }
  }
  if (*dim_l <= 0) {
    cout << "Error: number of elements must be greater than 0"
      << endl;
    exit(1);
  }
}

/*
Routine that fills the number matrix with Random Data with values
between 0 and MAX_VALUE
This simulates in some way what might happen if there was a
single sequential data acquisition source such as a single file
*/
void fill_matrix(float *array, int dim_l)
{
  int i, j;
  for (i = 0; i < dim_l; i++) 
  {
    array[i] = drand48()*MAX_VALUE;
  }
}

/*
Routine that outputs the matrices to the screen
*/
void print_matrix(float *array, int dim_l)
{
  int i, j;
  for (i = 0; i < dim_l; i++) {
    cout << array[i] << " ";
  }
  cout << endl;
}

int main(int argc, char* argv[]) {
  float *a;
  int dim_l;
  int i, j, k;

  /*
  get matrix sizes
  */
  get_index_size(argc, argv, &dim_l);

  // dynamically allocate from heap the numbers in the memory space
  // for the a,b, and c matrices 
  a = new (nothrow) float[dim_l];
  if (a == 0) {
    cout << "ERROR:  Insufficient Memory" << endl;
    exit(1);
  }

  /*
  initialize numbers matrix with random data
  */
  srand48(SEED);
  fill_matrix(a, dim_l);

  /*
  output numbers matrix
  */
#if !TIMING_ANALYSIS
  cout << "A matrix =" << endl;
  print_matrix(a, dim_l);
  cout << endl;
#endif

  float sum = 0.0;
  for (int i = 0; i < dim_l; ++i)
    sum += a[i];

  cout << "Sum of " << dim_l << " elements in A is " << sum << endl;
  return 0;
}
