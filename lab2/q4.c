#include <stdio.h>
#include <mpi.h>

// process 0 reads a number
//  process 1 sends to process 2 , 3 sends to 4 and last process sends to first again
int main(int argc, char** argv){

    MPI_Init(&argc, &argv);
    
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    MPI_Status stat;
    int x;
    if(rank==0){
        fprintf(stdout,"Enter Number in master Process: ");
        fflush(stdout);

        scanf("%d",&x);
        // this if condiiton is important if number of processes issued is small
        if (rank + 1 < size)
        {
            MPI_Ssend(&x, 1, MPI_INT, 1, 999, MPI_COMM_WORLD);
        }
        MPI_Recv(&x,1,MPI_INT,size-1,88,MPI_COMM_WORLD,&stat);
        fprintf(stdout,"%d recieved from rank %d in root process \n",x,size-1);
        fflush(stdout);

    }
    else if (rank==size-1){
        MPI_Recv(&x,1,MPI_INT,rank-1,999,MPI_COMM_WORLD,&stat);
        fprintf(stdout,"%d recieved from rank %d \n",x,rank-1);

        fprintf(stdout,"Incrementing number and sending it to root Process \n");
        x+=1;
        fflush(stdout);
        MPI_Ssend(&x, 1,MPI_INT,0,88,MPI_COMM_WORLD);
    }
    else{
        MPI_Recv(&x,1,MPI_INT,rank-1,999,MPI_COMM_WORLD,&stat);
        fprintf(stdout,"%d recieved from rank %d \n",x,rank-1);

        x+=1;
        fprintf(stdout,"Incrementing number and sending it to next Process %d\n",rank+1);
        fflush(stdout);
        MPI_Ssend(&x, 1,MPI_INT,rank+1,999,MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}