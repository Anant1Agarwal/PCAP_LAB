#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int factorial(int n){
    int res=1;

    for (int i=2;i<=n;i++){
        res*=i;
    }
    return res;
}

int summ(int n){
    int sum=0;

    for (int i=1;i<=n;i++){
        sum+=i;
    }

    return sum;
}


int main(int argc, char** argv){

    MPI_Init(&argc, &argv);
    
    int rank,size;
    MPI_Status stat;

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int ans=0;
    int x;
    if(rank==0){
        x=factorial(1);
        fprintf(stdout,"rank %d , x= %d\n",rank, x);
        fflush(stdout);
        ans+=x;

        for(int i=1;i<size;i++)
        {
            MPI_Recv(&x,1,MPI_INT,i,999,MPI_COMM_WORLD,&stat);
            ans+=x;
        }

        fprintf(stdout,"The required ans is %d \n",ans);
        fflush(stdout);
    }
    
    else if(rank%2==0){
        x=factorial(rank+1);
        fprintf(stdout,"rank %d , x= %d\n",rank, x);
        fflush(stdout);
        MPI_Ssend(&x,1,MPI_INT,0,999,MPI_COMM_WORLD);
        
    }
    else{
        x=summ(rank+1);
        fprintf(stdout,"rank %d , x= %d\n",rank, x);
        fflush(stdout);
        MPI_Ssend(&x,1,MPI_INT,0,999,MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
