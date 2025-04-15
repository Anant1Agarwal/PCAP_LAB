#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>

// Buffered send
// master process reads N array elements and sends 1 element to each process where it is squared or cubed
int main(int argc, char** argv){

    MPI_Init(&argc, &argv);
    
    int rank,size;
    MPI_Status stat;

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    // before everything attach buffer
    // buffer size
    int bsize=100;
    int *buffer=(int *)malloc(bsize* sizeof(int));
    MPI_Buffer_attach(buffer,bsize*sizeof(int));

    int ans;
    
    if(rank==0){
        fprintf(stdout,"Enter %d elements: ",size);
        fflush(stdout);

        for (int i=0;i<size;i++){
            scanf("%d", &buffer[i]);
            MPI_Bsend(&buffer[i],1,MPI_INT,i,999, MPI_COMM_WORLD);
        }

        int ans=buffer[0];
        fprintf(stdout,"In rank %d, square of %d is: %.2f\n",rank, ans, pow(ans,2));      
        fflush(stdout);
    }
    else{
        MPI_Recv(&ans, 1, MPI_INT, 0, 999, MPI_COMM_WORLD,&stat);

        if(rank%2){
            fprintf(stdout,"In rank %d, cube of %d is: %.2f\n",rank, ans, pow(ans,3));
        }else{
            fprintf(stdout,"In rank %d, square of %d is: %.2f\n",rank, ans, pow(ans,2));
        }
        fflush(stdout);
    }
    MPI_Buffer_detach(&buffer, &bsize);


    MPI_Finalize();
    return 0;
}
