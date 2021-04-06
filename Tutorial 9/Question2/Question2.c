#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#define n 100000000


int main(int argc, char *argv[]) {

    double y[n];
    double dx = 1/(n+1);
    double x=0;
    int i = 0;

    if (argc != 2) {
        printf("Execute with a argument! (The number of threads)\n");
        exit(1);
    }
    int nthreads = atoi(argv[1]); // String to int
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
    #pragma omp parallel for shared(x, y) private(i)
    for (i = 0; i < n; i++)
    {
        x = i * dx;
        y[i] = exp(x) * cos (x) * sin (x) * sqrt (5 * x + 6.0);

    }
   return 0;
}
