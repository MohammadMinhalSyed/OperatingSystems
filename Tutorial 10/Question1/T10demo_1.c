/*
 * Tutorial 10 MPI Demo for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Author: Jonathan Gillett
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

// Define process 0 as MASTER
#define MASTER 0

int main (int argc, char* argv[])
{
    int proc_id;            // Process rank
    int n_proc;             // Number of processes

    // Initialize MPI
    /* Create child processes, each of which has its own variables.
    From this point on, every process executes a separate copy
    of this program.  Each process has a different process ID,
    ranging from 1 (MASTER is 0) to n_procs minus 1, and COPIES of all
    variables defined in the program. No variables are shared.
    */
    MPI_Init(&argc, &argv);

    /* find out process ID, and how many processes were started. */
    // Get the current process id
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

    // Get the current number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

    // Display a "Hello world" message from each child/parent
    if (proc_id == MASTER)
    {
        printf( "Hello world from MATER, process %d of %d\n", proc_id, n_proc);
    }
    else
    {
        printf( "Hello world from SLAVE, process %d of %d\n", proc_id, n_proc);
    }

    /* Stop this process */
    // Required to terminate all MPI processes
    MPI_Finalize();
}
