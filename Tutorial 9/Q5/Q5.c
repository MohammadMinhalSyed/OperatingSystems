#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include <omp.h>

int main(int argc, char *argv[]) {
    int n = 100000000;
    double dx = 1/(n+1);
    double y[n], x;


    if (argc <= 1) {
        printf("Execute with a argument! (The number of threads)\n");
        exit(1);
    }

    int nthreads = atoi(argv[1]); // String to int
    omp_set_num_threads(nthreads);

    FILE*fp = fopen("calculation.txt", "w");

    #pragma omp parallel for private (x,y)
    
    for (int i = 0; i < n; i++){
        x = (double)i * dx;
        y[i] = exp(x) * cos (x) * sin (x) * sqrt (5 * x + 6.0);
        if ((i+1) % 1000000 == 0) { // For every 1 millionth calculation
            #pragma omp critical
            fprintf(fp, "i = %d | x = %f | y = %f\n", i, x, y[i]);
        }
    }

    fclose(fp);
}