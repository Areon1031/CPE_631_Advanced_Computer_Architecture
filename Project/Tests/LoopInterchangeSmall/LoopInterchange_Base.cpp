#include <iostream>
#include <iomanip>
#include <sys/time.h>
using namespace std;

static const int FIRST_DIM = 5000;
static const int SECOND_DIM = 1000;

/* copied from mpbench */
#define TIMER_CLEAR     (tv1.tv_sec = tv1.tv_usec = tv2.tv_sec = tv2.tv_usec = 0)
#define TIMER_START     gettimeofday(&tv1, (struct timezone*)0)
#define TIMER_ELAPSED   ((tv2.tv_usec-tv1.tv_usec)+((tv2.tv_sec-tv1.tv_sec)*1000000))
#define TIMER_STOP      gettimeofday(&tv2, (struct timezone*)0)
struct timeval tv1,tv2;


static int x[FIRST_DIM][SECOND_DIM];

void init()
{
	for (int j = 0; j < SECOND_DIM; j = j + 1)
	{
		for (int i = 0; i < FIRST_DIM; i = i + 1)
		{
			x[i][j] = 0;
		}
	}
}

int main(int argc, char* argv[])
{
	init();

	TIMER_CLEAR;
	TIMER_START;

	for (int j = 0; j < SECOND_DIM; j = j + 1)
	{
		for (int i = 0; i < FIRST_DIM; i = i + 1)
		{
			x[i][j] = 2 * x[i][j];
		}
	}

	TIMER_STOP;

	cout << "time=" << setprecision(8) <<  TIMER_ELAPSED/1000000.0 
        << " seconds" << endl;

	return 0;
}
