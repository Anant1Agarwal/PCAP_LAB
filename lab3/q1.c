#include <stdio.h>
#include <mpi.h>
#include<stdlib.h>

int factorial(int n){
    int res=1;

    for(int i=2;i<=n;i++)
    res*=i;

    return res;
}


int main(int argc, char** argv){
    MPI_Init(&argc,&argv);

    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    int N=size;

    int *arr=(int *)malloc(N*sizeof(int));
    int ans;
    int fact;
    int recv;
    if(rank==0){
        fprintf(stdout,"Enter %d number of elements in the Master Process: ",N);
        fflush(stdout);
        for(int i=0;i<N;i++){
            scanf("%d",&arr[i]);
        }
    }

    MPI_Scatter(arr,1,MPI_INT,&recv,1,MPI_INT,0,MPI_COMM_WORLD);

    fact=factorial(recv);
    fprintf(stdout,"factorial of recv(%d) is %d from rank %d \n",recv,fact, rank);
    fflush(stdout);

    MPI_Reduce(&fact, &ans,1,MPI_INT, MPI_SUM,0,MPI_COMM_WORLD);
    
    if(rank==0){
        fprintf(stdout,"Final Reduced ans in master procees : %d\n",ans);
        fflush(stdout);
    }
    
    MPI_Finalize();
    return 0;
}