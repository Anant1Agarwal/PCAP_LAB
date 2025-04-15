#include <stdio.h>
#include <mpi.h>
#include<stdlib.h>


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
        }
    }
        
        MPI_Bcast(&M,1,MPI_INT,0,MPI_COMM_WORLD);
        int *store=(int*)malloc(M*sizeof(int));

        MPI_Scatter(arr,M,MPI_INT,store,M,MPI_INT,0,MPI_COMM_WORLD);

        float avg=0;
        fprintf(stdout,"\nElements in process %d are: ",rank);
        

        for (int i=0;i<M;i++){
            fprintf(stdout,"%d  ",store[i]);
            avg+=store[i];
        }

        avg/=M;
        fprintf(stdout,"\naverage from process %d : %.2f\n",rank, avg );
        fflush(stdout);
        MPI_Reduce(&avg, &ans,1, MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);

        if (rank==0){
            ans=ans/size;
            fprintf(stdout,"\nAverage from all process is %.2f\n", ans);
            fflush(stdout);
        }
    
    MPI_Finalize();
    return 0;
}

// root@807604e088ff:/workspaces/PCAB_LAB/lab3# mpirun-root -np 5 ./output

// Enter M ie Number of elements for each process in Master Process: 3

// enter 15 Number of elements: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

// Elements in process 0 are: 1  2  3  
// average from process 0 : 2.00

// Average from all process is 8.00

// Elements in process 1 are: 4  5  6  
// average from process 1 : 5.00

// Elements in process 2 are: 7  8  9  
// average from process 2 : 8.00

// Elements in process 3 are: 10  11  12  
// average from process 3 : 11.00

// Elements in process 4 are: 13  14  15  
// average from process 4 : 14.00