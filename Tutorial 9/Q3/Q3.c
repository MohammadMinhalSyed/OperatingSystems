#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include <omp.h>
#include <time.h> 

static int x[100000000];

int main(void) {
	int i;
	int norm = 0;

	srand (time(NULL));
	for (i = 0; i < 100000000; i++) {
		x[i] = rand() % 100;
		norm += fabs(x[i]); 
	}


	double start = omp_get_wtime();
    for(int k = 0; k < 100000000; k++){
        x[k] = rand() % 100;
        norm += fabs(x[k]);
    }

    double end = omp_get_wtime();
    double dif = end - start;
    printf("The time without using omp: %f\n", dif);

    double start2 = omp_get_wtime();
    #pragma omp parallel for reduction(+: norm)
    for(int i = 0; i <100000000; i++){
    	norm += fabs(x[i]);
    }
    
    double end2 = omp_get_wtime();
    double dif2 = end2 - start2;
    printf("The time without using omp: %f\n", dif2);
} 