#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);

    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int N=size;

    int *arr=(int *)malloc(N*sizeof(int));
    int *final_arr=(int *)malloc(N*sizeof(int));
    int recv;

    if(rank==0){
        fprintf(stdout,"Enter %d number of elements in the Master Process: ",N);
        fflush(stdout);
        for(int i=0;i<N;i++){
            scanf("%d",&arr[i]);
        }
    }

    // fprintf(stdout,"------Scattering-----");
    // fflush(stdout);
    MPI_Scatter(arr,1,MPI_INT,&recv,1,MPI_INT,0,MPI_COMM_WORLD);
    fprintf(stdout,"I have recieved %d in rank %d\n" ,recv,rank);
    fflush(stdout);

    recv=recv*recv;
    MPI_Gather(&recv,1,MPI_INT, final_arr,1,MPI_INT,0,MPI_COMM_WORLD);

    if (rank==0){
        fprintf(stdout,"\nFinal Array after squaring is: ");
        for (int i=0;i<N;i++){
            fprintf(stdout,"%d\t",final_arr[i]);
        }
        fprintf(stdout,"\n");
        fflush(stdout);
    }



    MPI_Finalize();
    return 0;
}

// Enter 5 number of elements in the Master Process: 3 5 7 8 9
// I have recieved 5 in rank 1
// I have recieved 7 in rank 2
// I have recieved 8 in rank 3
// I have recieved 9 in rank 4
// I have recieved 3 in rank 0

// Final Array after squaring is: 9        25      49      64      81
