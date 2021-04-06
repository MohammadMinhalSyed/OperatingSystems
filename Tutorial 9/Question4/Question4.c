#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>



int main(int argc, char *argv[]) {
    int i = 0;
    int j = 0;
    int k = 0;
    int a[100][100];
    int b[100][100];
    int c[100][100];
    time_t t;

    srand((unsigned) time(&t));

    for (i=0; i<100; i++)
    {
            for (j=0; j<100; j++)
            {
                a[i][j]=rand() % 10;
                b[i][j]=rand() % 10;
                c[i][j]=0;
            }
    }

    if (argc != 2) {
        printf("Execute with a argument! (The number of threads)\n");
        exit(1);
    }
    int nthreads = atoi(argv[1]); // String to int
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    #pragma omp parallel for shared(a, b, c) private(i,j,k)
    for (int i = 0; i < 100; i++)
    {
        for (j=0; j < 100; j++)
        {
            for (k=0; k < 100; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

   return 0;
}
