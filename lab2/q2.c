#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv){

    MPI_Init(&argc, &argv);
    
    int rank,size;
    MPI_Status stat;

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int x;

    if (rank==0){
        fprintf(stdout,"Enter number in the master Proces to be sent :");
        fflush(stdout);
        scanf("%d", &x);

        fprintf(stdout,"\nSending number %d to each of the slave processes\n\n",x);
        fflush(stdout);
        
        for (int i=1;i<size;i++)
        MPI_Ssend(&x, 1, MPI_INT,i,999,MPI_COMM_WORLD);
    }
    else{
        int y;
        MPI_Recv(&y, 1, MPI_INT,0,999,MPI_COMM_WORLD,&stat);
        fprintf(stdout,"Process %d received %d \n", rank, y);
        fflush(stdout);
    }



    MPI_Finalize();
    return 0;
}


// Enter number in the master Proces to be sent :84

// Sending number 84 to each of the slave processes

// Process 1 received 84 
// Process 2 received 84 
// Process 3 received 84 
// Process 4 received 84 
// Process 5 received 84 
// Process 6 received 84 