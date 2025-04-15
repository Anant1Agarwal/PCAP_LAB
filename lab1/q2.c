#include <stdio.h>
#include <mpi.h>

// odd prints hello. even prints world
int main(int argc, char** argv){

    MPI_Init(&argc, &argv);

    int rank;

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank%2){
        printf("we are in rank %d---------> we say 'world!' \n",rank);
    }else{
        printf("we are in rank %d--> we say'Hello' \n",rank);
    }

    MPI_Finalize();
    return 0;
}