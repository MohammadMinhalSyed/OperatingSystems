#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define MASTER 0

#define DATA_SIZE 1000000
#define CHUNK_SIZE 5000

int main (int argc, char* argv[])
{
    int proc_id, n_proc;
    double *data = malloc(DATA_SIZE*sizeof(double));
    double chunk_master[CHUNK_SIZE] = { 0 };
    double results_master[DATA_SIZE] = { 0 };
    double chunk_slave[CHUNK_SIZE] = { 0 };
    double result_slave[CHUNK_SIZE] = { 0 };
    double total = 0;
    double t1, t2;
    int total_chunks = DATA_SIZE / CHUNK_SIZE;
    int proc = 0, n_sent = 0, n_recv_master = 0, n_recv_slave=0;
    MPI_Status status_master, status_slave;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

    if (proc_id == MASTER)
    {
        for (int i = 0; i < DATA_SIZE; ++i)
        {
            data[i] = i;
        }
        t1 = MPI_Wtime();
        for (int i = 1; i < n_proc; ++i)
        {
            MPI_Send(&data[n_sent*CHUNK_SIZE], CHUNK_SIZE, MPI_DOUBLE, i, n_sent, MPI_COMM_WORLD);
            n_sent++;
        }


        for (int i = 0; i < total_chunks; ++i)
        {

            MPI_Recv(chunk_master, CHUNK_SIZE, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status_master);

            proc = status_master.MPI_SOURCE;
            n_recv_master = status_master.MPI_TAG;

            for (int i = 0; i < CHUNK_SIZE; ++i)
            {
                results_master[n_recv_master*CHUNK_SIZE + i] = chunk_master[i];
            }

            if (n_sent < total_chunks)
            {
                MPI_Send(&data[n_sent*CHUNK_SIZE], CHUNK_SIZE, MPI_DOUBLE, proc, n_sent, MPI_COMM_WORLD);
                n_sent++;
            }
        }


        for (int i = 1; i < n_proc; ++i)
        {
            MPI_Send(chunk_master, CHUNK_SIZE, MPI_DOUBLE, i, CHUNK_SIZE, MPI_COMM_WORLD);
        }
        t2 = MPI_Wtime();

        printf("Elapsed time betweeb master and slave is: %f seconds\n", t2-t1);
        for (int i = 1; i < DATA_SIZE; ++i)
        {
            if (data[i] < 1)
            {
                printf("ERROR, DATA ZERO AT INDEX %d\n", i);
            }
        }

        for (int i = 0; i < DATA_SIZE; ++i)
        {
            total += results_master[i]-data[i];
        }

        printf("ping pong error: %f\n", total);
    }
    else
    {

        MPI_Recv(chunk_slave, CHUNK_SIZE, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status_slave);
        n_recv_slave = status_slave.MPI_TAG;


        while (n_recv_slave < CHUNK_SIZE)
        {

            for (int i = 0; i < CHUNK_SIZE; ++i)
            {
                result_slave[i] = chunk_slave[i];
            }

            MPI_Send(result_slave, CHUNK_SIZE, MPI_DOUBLE, MASTER, n_recv_slave, MPI_COMM_WORLD);

            MPI_Recv(chunk_slave, CHUNK_SIZE, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status_slave);
            n_recv_slave = status_slave.MPI_TAG;
        }
    }
    MPI_Finalize();
}


