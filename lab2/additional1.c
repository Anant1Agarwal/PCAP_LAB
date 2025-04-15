#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int isPrime(int n){

    if(n<2){
        return 0;
    }
    if(n==2){
        return 1;
    }
    for(int i=2;i<n/2;i++){
        if(n%i==0){
            return 0;
        }

    }
    return 1;
}

// each number is checked for prime in each process
int main(int argc, char** argv){

    MPI_Init(&argc, &argv);
    
    int rank,size;
    MPI_Status stat;

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int x;

    if (rank==0){
        int arr_size=size;
        int *arr=(int*)malloc(arr_size*sizeof(int));

        fprintf(stdout,"Enter %d number of elements in root process: ",size);
        fflush(stdout);

        for(int i=0;i<size;i++){
            scanf("%d",&arr[i]);
        }

        for(int i=1;i<size;i++){
            MPI_Ssend(&arr[i],1,MPI_INT,i,999,MPI_COMM_WORLD);   
        }

        if (isPrime(arr[rank])){
            fprintf(stdout,"Number %d is Prime.\n",arr[rank]);
            fflush(stdout);
        }else{
            fprintf(stdout,"Number %d is not Prime.\n",arr[rank]);
            fflush(stdout);  
        }
    }
    else{
        MPI_Recv(&x,1,MPI_INT,0,999,MPI_COMM_WORLD,&stat);

        if (isPrime(x)){
            fprintf(stdout,"Number %d is Prime.\n",x);
            fflush(stdout);
        }else{
            fprintf(stdout,"Number %d is not Prime.\n",x);
            fflush(stdout);  
        }
    }

    MPI_Finalize();
    return 0;
}
