#include <stdio.h>
#include <mpi.h>
#include<stdlib.h>
#include <math.h>

int main(int argc, char** argv){
    MPI_Init(&argc,&argv);

    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int N=size;
    int M;
    int *arr;
    float ans;

    if (rank==0){
        fprintf(stdout,"\nEnter M ie Number of elements for each process in Master Process: ");
        fflush(stdout);
        scanf("%d",&M);

        fprintf(stdout,"\nenter %d Number of elements: ",M*N);
        fflush(stdout);
        arr=(int *)malloc(M*N*sizeof(int));
        for (int i=0;i<M*N;i++)
        {
            scanf("%d",&arr[i]);
        }}
        
        MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
        int *store=(int*)malloc(M*sizeof(int));

        MPI_Scatter(arr,M,MPI_INT,store,M,MPI_INT,0,MPI_COMM_WORLD);

        fprintf(stdout,"\nElements in process %d (raised by power of %d )are: ",rank,rank+2);
        

        for (int i=0;i<M;i++){
            fprintf(stdout,"%d  ",store[i]);
            store[i]=pow(store[i],rank+2);
        }

        fprintf(stdout,"\nNew Elements in process %d are: ",rank);
        

        for (int i=0;i<M;i++){
            fprintf(stdout,"%d  ",store[i]);
        }
        fprintf(stdout,"\n");
        fflush(stdout);

        MPI_Gather(store,M,MPI_INT, arr,M,MPI_INT,0,MPI_COMM_WORLD);

        if (rank==0){
            
            fprintf(stdout,"\nNew Elements in Master process are: ");
            for (int i=0;i<M*N;i++){
                fprintf(stdout,"%d  ",arr[i]);
            }
            fprintf(stdout,"\n");
            fflush(stdout);
        }
    
    MPI_Finalize();
    return 0;
}


// root@807604e088ff:/workspaces/PCAB_LAB/lab3# mpirun-root -np 5 ./output

// Enter M ie Number of elements for each process in Master Process: 3

// enter 15 Number of elements: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

// Elements in process 4 (raised by power of 6 )are: 13  14  15  
// New Elements in process 4 are: 4826809  7529536  11390625  

// Elements in process 0 (raised by power of 2 )are: 1  2  3  
// New Elements in process 0 are: 1  4  9  

// Elements in process 1 (raised by power of 3 )are: 4  5  6  
// New Elements in process 1 are: 64  125  216  

// Elements in process 2 (raised by power of 4 )are: 7  8  9  
// New Elements in process 2 are: 2401  4096  6561  

// Elements in process 3 (raised by power of 5 )are: 10  11  12  
// New Elements in process 3 are: 100000  161051  248832  

// New Elements in Master process are: 1  4  9  64  125  216  2401  4096  6561  100000  161051  248832  4826809  7529536  11390625 