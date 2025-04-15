#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv){
    MPI_Init(&argc,&argv);

    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int fact=1;
    int factsum;

    for(int i=1;i<=rank+1;i++){
        fact*=i;
    }
    fprintf(stdout,"factorial in process %d is %d\n",rank, fact);
    fflush(stdout);


    MPI_Reduce(&fact,&factsum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank==0){
        fprintf(stdout,"Sum of factorials Final ans : %d\n", factsum);
        fflush(stdout);

    }
    MPI_Finalize();
    return 0;
}