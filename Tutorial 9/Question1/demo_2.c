#include <stdio.h>
#include <omp.h>
int main (int argc, char *argv[])
{
    int num = 0; // Watch out for race conditions!
    int thread_num, nthreads = 16;
    //Only run this section between "ifdef" and "endif", (omp_set_num), if the OPENMP is available
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
    printf("Testing OpenMP, you should see each thread print...\n");
    //Parallel region with default number of threads
    #pragma omp parallel
    {
        thread_num = omp_get_thread_num();
        //Threads wait their turn – only one at a time to call ifdef

        #pragma omp critical
        {
            //Only run this section between "ifdef" and "endif" if the OPENMP is available
            #ifdef _OPENMP
            num += 1; // THREAD SAFE INCREMENT
            printf("This thread = %d, num = %d\n", thread_num, num);
            #endif
        }
    }
    return 0;
}
