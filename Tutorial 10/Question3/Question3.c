#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <time.h>
#define MASTER 0

int A[100][100], B[100][100], C[100][100], c[100][100];

int main(int argc, char *argv[])
{
  int proc_id, n_proc;
  int startsection, endsection, i, j, k, total;
  time_t t;

  srand((unsigned) time(&t));

  for (i=0; i<100; i++)
    {
            for (j=0; j<100; j++)
            {
                A[i][j]=rand() % 10;
                B[i][j]=rand() % 10;
                C[i][j]=0;
                c[i][j]=0;
            }
    }
  for (int i = 0; i < 100; i++)
    {
        for (j=0; j < 100; j++)
        {
            for (k=0; k < 100; k++)
            {
                c[i][j] += A[i][k] * B[k][j];
            }
        }
    }
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
  MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

  startsection = proc_id * 100/n_proc;
  endsection = (proc_id+1) * 100/n_proc;


  MPI_Bcast (B, 100*100, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter (A, 100*100/n_proc, MPI_INT, A[startsection], 100*100/n_proc, MPI_INT, 0, MPI_COMM_WORLD);


  for (i=startsection; i<endsection; i++)
    for (j=0; j<100; j++) {
      C[i][j]=0;
      for (k=0; k<100; k++)
        C[i][j] += A[i][k]*B[k][j];
    }

  MPI_Gather (C[startsection], 100*100/n_proc, MPI_INT, C, 100*100/n_proc, MPI_INT, 0, MPI_COMM_WORLD);

  MPI_Finalize();
  if (proc_id == MASTER)
  {
    for (i=0; i<100; i++)
        {
                for (j=0; j<100; j++)
                {
                    total += c[i][j]-C[i][j];
                }
        }

    printf("Error between MPI and serial calc: %d\n", total);
   }
  return 0;
}


