#include <stdio.h>
#include <mpi.h>

int isPrime(int n){
    if (n<2){
        return 0;
    }

    if(n==2){
        return 1;
    }

    for (int i=2;i<n/2;i++){
        if (n%i==0){
            return 0;
        }
    }

    return 1;
}

int main(int argc, char** argv){

    MPI_Init(&argc,&argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank==0){
        for (int i=0;i<=50;i++){
            if(isPrime(i)){
                printf("rank is %d and prime is %d\n", rank, i);
            }
        }
    }
    else{
        for (int i=51;i<=100;i++){
            if(isPrime(i)){
                printf("rank is %d and prime is %d\n", rank, i);
            }
        }
    }

    fflush(stdout);

    MPI_Finalize();
    return 0;

}