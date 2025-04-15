#include <mpi.h>
#include <stdio.h>
#include <math.h>

// program to find pow(x,rank) for each process
int main(int argc, char** argv){

    MPI_Init(&argc, &argv);

    int rank;

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int x=7;
    int req=pow(x,rank);

    printf("we are in process %d, so pow(%d,%d) is %d\n", rank,x,rank,req);

    MPI_Finalize();
    return 0;
}

// mpicc q1.c -o output -lm